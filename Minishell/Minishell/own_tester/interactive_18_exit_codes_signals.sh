#!/bin/bash
# ==============================================================================
# 19_exit_codes_signals.sh — Signal-based exit code tests
#
# Run this script DIRECTLY (not through the test runner):
#   bash own_tester/19_exit_codes_signals.sh
#
# It spawns minishell as a subprocess and uses `kill` to deliver signals,
# then checks that $? is set correctly afterward.
#
# Tests covered:
#   - SIGINT  to a child process  → $? = 130
#   - SIGQUIT to a child process  → $? = 131
#   - SIGINT  to minishell itself → shell exits with 130
#
# Manual tests (cannot be automated) are documented at the bottom.
# ==============================================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MINISHELL="$SCRIPT_DIR/../minishell"

RED="\033[31m"; GREEN="\033[32m"; YELLOW="\033[33m"; RESET="\033[0m"
PASS=0; FAIL=0

pass() { echo -e "${GREEN}[PASS]${RESET} $1"; ((PASS++)); }
fail() { echo -e "${RED}[FAIL]${RESET} $1 — expected: $2  got: $3"; ((FAIL++)); }
info() { echo -e "${YELLOW}[INFO]${RESET} $1"; }

if [ ! -x "$MINISHELL" ]; then
    echo "ERROR: minishell binary not found at $MINISHELL"
    exit 1
fi

# ==============================================================================
# Helper: run a two-command session in minishell (non-interactive) via a FIFO.
# We send "cmd_to_signal" first, then "echo \$?" after signalling the child.
# Returns the value printed by "echo $?" in $RESULT_CODE.
# ==============================================================================
run_signal_test()
{
    local signal="$1"
    local child_cmd="$2"     # command that runs as a child (e.g. sleep 30)
    local fifo
    fifo=$(mktemp -u /tmp/ms_sig_test_XXXXXX)
    mkfifo "$fifo"

    # Writer: send the child command, wait for the signal to arrive, then ask $?
    (
        echo "$child_cmd"
        sleep 0.6          # give the child time to start and receive the signal
        echo 'echo $?'
        sleep 0.2
    ) > "$fifo" &
    WRITER_PID=$!

    # Start minishell reading from the FIFO; redirect stderr to /dev/null
    "$MINISHELL" < "$fifo" > /tmp/ms_sig_out 2>/dev/null &
    MINI_PID=$!

    # Wait briefly for the child process to spawn inside minishell
    sleep 0.3

    # Find direct child processes of minishell (the command we asked it to run)
    CHILD_PIDS=$(pgrep -P "$MINI_PID" 2>/dev/null)

    if [ -n "$CHILD_PIDS" ]; then
        for cpid in $CHILD_PIDS; do
            kill "-$signal" "$cpid" 2>/dev/null
        done
    else
        # Fallback: signal minishell itself (tests interactive Ctrl+C path)
        kill "-$signal" "$MINI_PID" 2>/dev/null
    fi

    wait "$MINI_PID" 2>/dev/null
    wait "$WRITER_PID" 2>/dev/null
    rm -f "$fifo"

    RESULT_CODE=$(grep -oE '^[0-9]+$' /tmp/ms_sig_out | tail -1)
    rm -f /tmp/ms_sig_out
}

# ==============================================================================
# Automated signal tests
# ==============================================================================

echo ""
echo "========================================"
echo " Automated signal exit-code tests"
echo "========================================"
echo ""

# --- Test 1: SIGINT to child process → $? = 130 ---
info "Sending SIGINT to child (sleep 30) inside minishell ..."
run_signal_test "SIGINT" "sleep 30"
if [ "$RESULT_CODE" = "130" ]; then
    pass "SIGINT in child process → \$? = 130 (got: $RESULT_CODE)"
else
    fail "SIGINT in child process → \$? = 130" "130" "${RESULT_CODE:-<no output>}"
fi

# --- Test 2: SIGQUIT to child process → $? = 131 ---
info "Sending SIGQUIT to child (sleep 30) inside minishell ..."
run_signal_test "SIGQUIT" "sleep 30"
if [ "$RESULT_CODE" = "131" ]; then
    pass "SIGQUIT in child process → \$? = 131 (got: $RESULT_CODE)"
else
    fail "SIGQUIT in child process → \$? = 131" "131" "${RESULT_CODE:-<no output>}"
fi

# --- Test 3: SIGINT to minishell itself (no child) → shell exits with 130 ---
info "Sending SIGINT to minishell (interactive mode, no child) ..."
fifo3=$(mktemp -u /tmp/ms_sigself_XXXXXX)
mkfifo "$fifo3"
sleep 10 > "$fifo3" &          # open write end so minishell's open() doesn't block
WRITER3_PID=$!
"$MINISHELL" < "$fifo3" > /dev/null 2>&1 &
MINI_PID=$!
sleep 0.2
kill -SIGINT "$MINI_PID" 2>/dev/null
wait "$MINI_PID" 2>/dev/null
EXIT_STATUS=$?
kill "$WRITER3_PID" 2>/dev/null
wait "$WRITER3_PID" 2>/dev/null
rm -f "$fifo3"
if [ "$EXIT_STATUS" = "130" ]; then
    pass "SIGINT to minishell → exit status 130 (got: $EXIT_STATUS)"
else
    fail "SIGINT to minishell → exit status 130" "130" "$EXIT_STATUS"
fi

# ==============================================================================
# Summary
# ==============================================================================

echo ""
echo "========================================"
echo " Results: $PASS passed, $FAIL failed"
echo "========================================"

# ==============================================================================
# Manual tests (require a real TTY — run inside ./minishell)
# ==============================================================================

cat << 'MANUAL'

========================================
 Manual tests (run inside ./minishell)
========================================

These require keyboard input and a real terminal; they cannot be automated.

--- Ctrl+C in interactive prompt → $? = 130 ---
  Start:  ./minishell
  Type:   (press Ctrl+C without any command)
  Then:   echo $?
  Expect: 130

--- Ctrl+C during a running command → child killed, $? = 130 ---
  Start:  ./minishell
  Type:   sleep 30    (press Enter, then immediately Ctrl+C)
  Then:   echo $?
  Expect: 130

--- Ctrl+\ during a running command → child killed, $? = 131 ---
  Start:  ./minishell
  Type:   sleep 30    (press Enter, then immediately Ctrl+\)
  Then:   echo $?
  Expect: 131

--- Ctrl+\ in interactive prompt → ignored, no change to $? ---
  Start:  ./minishell
  Type:   echo $?     (note the value)
  Type:   (press Ctrl+\ with no command)
  Then:   echo $?
  Expect: same value as before (Ctrl+\ is ignored in the prompt)

--- Ctrl+C during heredoc → $? = 130, returns to prompt ---
  Start:  ./minishell
  Type:   cat << EOF
  Type:   (press Ctrl+C)
  Then:   echo $?
  Expect: 130

--- Ctrl+D on empty line → shell exits with 0 ---
  Start:  ./minishell
  Type:   (press Ctrl+D on an empty prompt)
  Expect: shell exits; check with: echo $? in the outer shell → 0

=========================================
Additional tests
=========================================
--- Command 1, it should show ls output and wait for input, then Ctrl+D to end it ---
  Start:  ./minishell
  Type:   cat | cat | ls
  Then:   (press Enter, then Ctrl+D)
  Expect: output of ls, then back to prompt

--- Command 2, it should print "hello" 20 times, then back to prompt ---
  Start:  ./minishell
  Type:   yes | head -n 20
  Then:   (press Enter)
  Expect: "y" printed 20 times, then back to prompt

--- Command 3, it should print "hello" once, then back to prompt ---
  Start:  ./minishell
  Type:   cat | cat | echo hello
  Then:   (press Enter)
  Expect: "hello" printed once, then back to prompt

--- Command 4, it should print the contents of d (which is empty), then back to prompt ---
  Start:  ./minishell
  Type:   ls > a > b > c > d | cat d
  Then:   (press Enter)
  Expect: no output (d is empty), then back to prompt
  Check: ls should show files a, b, c, d created

--- Command 5, it should print "hello world" once, then back to prompt ---
  Start:  ./minishell
  Type:   cat << EOF
  Hello world
  EOF
  Type:   (press Enter)
  Expect: "Hello world" printed once, then back to prompt
  Check: .heredoc_tmp_0 should not be created (since we didn't redirect it)

--- Command 6, it should print "hello world" once, then back to prompt ---
  Start:  ./minishell
  Type:   cat << EOF | echo hello world > .heredoc_tmp_0
  Type:   (press Enter)
  Expect: "hello world" printed once, then back to prompt
  Check: .heredoc_tmp_0 should be created and empty

--- Command 7, pipe followed by a leading redirect operator → syntax error ---
  Start:  ./minishell
  Type:   ls | > wc
  Expect: syntax error near unexpected token `>'
  Note:   also test with >>, <, << after the pipe

--- Command 8, empty input → nothing happens, back to prompt ---
  Start:  ./minishell
  Type:   (press Enter on empty line)
  Expect: prompt reappears, no error, $? unchanged

--- Command 9, only spaces → nothing happens, back to prompt ---
  Start:  ./minishell
  Type:   (press Space a few times, then Enter)
  Expect: prompt reappears, no error, $? unchanged

--- Command 10, unclosed quote → syntax error ---
  Start:  ./minishell
  Type:   echo "hello
  Expect: minishell: syntax error: unclosed quote; $? = 2

--- Command 11, unset PATH then run ls → uses full path ---
  Start:  ./minishell
  Type:   unset PATH
  Type:   ls
  Expect: command not found
  Type:   /bin/ls
  Expect: directory listing

--- Command 12, unset HOME then cd → error ---
  Start:  ./minishell
  Type:   unset HOME
  Type:   cd
  Expect: minishell: cd: HOME not set; $? = 1

--- Command 13, redir followed by redir → syntax error ---
  Start:  ./minishell
  Type:   echo hola < < file
  Expect: syntax error near unexpected token `<'
  Note:   also test all combinations: </<</>/>> followed by </<</>/>>

--- Command 14, redir followed by pipe → syntax error ---
  Start:  ./minishell
  Type:   echo hola < | file
  Expect: syntax error near unexpected token `|'

--- Command 15, trailing redir → syntax error newline ---
  Start:  ./minishell
  Type:   echo hola > file <
  Expect: syntax error near unexpected token `newline'

--- Command 16, heredoc then output redirect → file gets heredoc content ---
  Start:  ./minishell
  Type:   echo hola > file << EOF
  Type:   (heredoc content)
  Type:   EOF
  Expect: file created with heredoc content (>> runs after << in left-to-right order)

--- Command 17, heredoc with output redirect → writes heredoc content to file ---
  Start:  ./minishell
  Type:   cat << EOF > file
  Type:   hello
  Type:   EOF
  Expect: file created containing "hello"; no output on stdout

--- Command 18, bare heredoc without command → reads and discards input ---
  Start:  ./minishell
  Type:   << EOF
  Type:   anything
  Type:   EOF
  Expect: no output, back to prompt, $? = 0

--- Command 19, multiple heredocs on same command → all delimiters prompted ---
  Start:  ./minishell
  Type:   cat << hola << que << tal
  Type:   (enter content for each delimiter: hola, que, tal)
  Expect: input prompted until each delimiter; last heredoc content printed by cat

--- Command 20, heredoc piped to ls ---
  Start:  ./minishell
  Type:   cat << EOF | ls
  Type:   anything
  Type:   EOF
  Expect: ls output printed (heredoc content goes to cat stdin, ignored by ls)

--- Command 21, long pipe chain → prints "hola" ---
  Start:  ./minishell
  Type:   echo hola | cat | cat | cat | cat | cat | cat | cat
  Expect: hola

--- Command 22, many > redirects → syntax error at >> ---
  Start:  ./minishell
  Type:   echo hola >>>>>>> file
  Expect: syntax error near unexpected token `>>'

--- Command 23, many < redirects → syntax error at << ---
  Start:  ./minishell
  Type:   echo hola <<<<<<< file
  Expect: syntax error near unexpected token `<<'

--- Command 24, redirect without spaces → creates file with content ---
  Start:  ./minishell
  Type:   echo hola>file
  Expect: file created containing "hola"; no output on stdout

--- Command 25, redirect to single file ---
  Start:  ./minishell
  Type:   echo hola > file
  Expect: file created containing "hola"; no stdout output

--- Command 26, multiple output redirects → only last file gets content ---
  Start:  ./minishell
  Type:   echo hola > file > file2 > file3
  Expect: file and file2 created empty; file3 contains "hola"

--- Command 27, multiple output redirects piped to ls ---
  Start:  ./minishell
  Type:   echo hola > file > file2 > file3 | ls
  Expect: ls output printed; file, file2 empty; file3 contains "hola"

--- Command 28, input redirect with missing file → error ---
  Start:  ./minishell
  Type:   wc < colors.txt
  Expect: minishell: colors.txt: No such file or directory; $? = 1

--- Command 29, input and output redirect with missing input file → error ---
  Start:  ./minishell
  Type:   wc < colors.txt > file
  Expect: minishell: colors.txt: No such file or directory; $? = 1; output file NOT created

--- Command 30, pipe with missing file → cat errors, wc counts 0 ---
  Start:  ./minishell
  Type:   cat colors.txt | wc
  Expect: cat: colors.txt: No such file or directory; wc prints "0 0 0"



ls |   >/>>/</<< wc

enter en input -> vacio
solo espacios
comillas sin cerrar
echo $?
unset $PATH -> ls -> /bin/ls
unset $HOME -> cd
echo hola </<</>/>>   </<</>/>> file
echo hola </<</>/>>   | file
echo hola > file </<</>/>>
echo hola > file << EOF
cat << EOF > file
<< EOF
cat << hola << que << tal
cat << hola << que << tal
cat << EOF | ls
echo hola | cat | cat | cat | cat | cat | cat | cat
echo hola >>>>>>> file
echo hola <<<<<<< file
echo hola>file
echo hola > file
echo hola > file > file2 > file3
echo hola > file > file2 > file3 | ls
wc < colors.txt
wc < colors.txt > file
cat colors.txt | wc
MANUAL

exit $((FAIL > 0 ? 1 : 0))
