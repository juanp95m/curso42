#!/bin/bash
# =============================================================================
# Minishell Test Suite - Evaluation Coverage
# Usage: ./test_master.sh           (quiet: show PASS/FAIL per test)
#        VERBOSE=1 ./test_master.sh  (show diffs on failures)
#        FILTER=pattern ./test_master.sh  (run only matching tests)
# Run from: intento_de_tester/ directory
# =============================================================================

PASS=0
FAIL=0
SKIP=0

COLORPASS=$(tput setaf 2)  # green
COLORFAIL=$(tput setaf 1)  # red
COLORSKIP=$(tput setaf 3)  # yellow
COLORRESET=$(tput sgr0)

# ---- Locate the minishell binary ----------------------------------------
if [ -x "../minishell" ]; then
    MINISHELL="../minishell"
elif [ -x "./minishell" ]; then
    MINISHELL="./minishell"
else
    echo "ERROR: minishell binary not found (looked for ../minishell and ./minishell)"
    exit 1
fi

# ---- Output normalizer --------------------------------------------------
# Strips differences that are cosmetic / implementation-specific:
#   - Replaces "bash:" / "minishell:" prefixes in error lines with "shell:"
#     so "bash: foo: command not found" == "minishell: foo: command not found"
#   - Strips "line N:" that bash adds in non-interactive mode
#     e.g. "shell: line 3: foo: ..." -> "shell: foo: ..."
#   - Normalises command-not-found word order:
#     minishell: "shell: command not found: foo"
#     bash:      "shell: foo: command not found"
#     -> both become: "shell: foo: command not found"
#   - Removes blank lines to tolerate trailing-newline discrepancies
normalize() {
    sed \
        -e 's/^bash: /shell: /g' \
        -e 's/^minishell: /shell: /g' \
        -e 's/^shell: line [0-9]*: /shell: /g' \
        -e 's/^shell: command not found: \(.*\)/shell: \1: command not found/g' \
        -e '/^[[:space:]]*$/d'
}

# ---- run one test -------------------------------------------------------
run_test() {
    local script="$1"
    local name
    name=$(basename "$script" .sh)

    # Apply FILTER if set
    if [ -n "${FILTER:-}" ] && [[ "$name" != *"$FILTER"* ]]; then
        ((SKIP++))
        return
    fi

    local bash_out minishell_out diff_out
    bash_out=$(cat "$script" | bash 2>&1 | normalize)
    minishell_out=$(cat "$script" | "$MINISHELL" 2>&1 | normalize)

    # Save normalized output to files
    echo "=== $name ===" >> bash_out.txt
    echo "$bash_out" >> bash_out.txt
    echo "" >> bash_out.txt
    echo "=== $name ===" >> minishell_out.txt
    echo "$minishell_out" >> minishell_out.txt
    echo "" >> minishell_out.txt

    diff_out=$(diff <(echo "$bash_out") <(echo "$minishell_out"))

    if [ -z "$diff_out" ]; then
        echo "${COLORPASS}[PASS] $name${COLORRESET}"
        ((PASS++))
    else
        echo "${COLORFAIL}[FAIL] $name${COLORRESET}"
        if [ "${VERBOSE:-0}" = "1" ]; then
            echo "  --- bash output ---"
            echo "$bash_out" | head -20 | sed 's/^/  /'
            echo "  --- minishell output ---"
            echo "$minishell_out" | head -20 | sed 's/^/  /'
            echo "  --- diff (- bash  + minishell) ---"
            echo "$diff_out" | head -30 | sed 's/^/  /'
            echo ""
        fi
        ((FAIL++))
    fi
}

# ---- special: also compare exit codes -----------------------------------
run_test_with_exitcode() {
    local script="$1"
    local name
    name=$(basename "$script" .sh)

    if [ -n "${FILTER:-}" ] && [[ "$name" != *"$FILTER"* ]]; then
        ((SKIP++))
        return
    fi

    local bash_out minishell_out bash_ec minishell_ec diff_out

    bash_out=$(cat "$script" | bash 2>&1 | normalize)
    bash_ec=$?
    minishell_out=$(cat "$script" | "$MINISHELL" 2>&1 | normalize)
    minishell_ec=$?

    # Save normalized output to files
    echo "=== $name (exit: bash=$bash_ec minishell=$minishell_ec) ===" >> bash_out.txt
    echo "$bash_out" >> bash_out.txt
    echo "" >> bash_out.txt
    echo "=== $name (exit: bash=$bash_ec minishell=$minishell_ec) ===" >> minishell_out.txt
    echo "$minishell_out" >> minishell_out.txt
    echo "" >> minishell_out.txt

    diff_out=$(diff <(echo "$bash_out") <(echo "$minishell_out"))
    local ec_match=true
    [ "$bash_ec" != "$minishell_ec" ] && ec_match=false

    if [ -z "$diff_out" ] && $ec_match; then
        echo "${COLORPASS}[PASS] $name (exit=$bash_ec)${COLORRESET}"
        ((PASS++))
    elif [ -z "$diff_out" ] && ! $ec_match; then
        echo "${COLORFAIL}[FAIL] $name  -- output ok but exit code: bash=$bash_ec minishell=$minishell_ec${COLORRESET}"
        ((FAIL++))
    else
        echo "${COLORFAIL}[FAIL] $name${COLORRESET}"
        if [ "${VERBOSE:-0}" = "1" ]; then
            echo "  exit codes: bash=$bash_ec  minishell=$minishell_ec"
            echo "  --- diff (- bash  + minishell) ---"
            echo "$diff_out" | head -30 | sed 's/^/  /'
            echo ""
        fi
        ((FAIL++))
    fi
}

# ---- main ---------------------------------------------------------------
cd "$(dirname "$0")"

# Clear output files at the start of each run
> bash_out.txt
> minishell_out.txt

echo "============================================================"
echo " Minishell Test Suite"
echo " Binary : $MINISHELL"
echo " Tests  : $(ls [0-9][0-9]_*.sh 2>/dev/null | wc -l) files"
echo " Output : bash_out.txt / minishell_out.txt"
echo "============================================================"
echo ""

for script in [0-9][0-9]_*.sh; do
    [ -f "$script" ] || continue
    if [[ "$script" == *exit* ]]; then
        run_test_with_exitcode "$script"
    else
        run_test "$script"
    fi
done

echo ""
echo "============================================================"
total=$((PASS + FAIL))
echo " Results: $PASS/$total passed  |  $FAIL failed  |  $SKIP skipped"
if [ "$FAIL" -eq 0 ] && [ "$total" -gt 0 ]; then
    echo "${COLORPASS} All tests passed!${COLORRESET}"
elif [ "$FAIL" -gt 0 ]; then
    echo " Tip: run with VERBOSE=1 ./test_master.sh to see diffs"
fi
echo "============================================================"