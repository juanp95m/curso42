#!/bin/bash
# =============================================================================
# Minishell Test Runner v2 - per-command output alignment
#
# Each command in a test script is run with output markers so comparison.txt
# shows every command aligned with its own bash / minishell output, with a
# visual blank row between commands.
#
# Usage:
#   ./run_tests_v2.sh                  quiet mode
#   VERBOSE=1     ./run_tests_v2.sh    show per-command diffs on failures
#   FILTER=pipes  ./run_tests_v2.sh    run only tests whose name matches "pipes"
#   TIMEOUT=10    ./run_tests_v2.sh    per-test timeout in seconds (default: 5)
#
# Output:
#   comparison.txt   three-column view: COMMAND | BASH | MINISHELL
#
# Run from: intento_de_tester/   OR any working directory
# =============================================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

if   [ -x "$SCRIPT_DIR/../minishell" ]; then MINISHELL="$SCRIPT_DIR/../minishell"
elif [ -x "$SCRIPT_DIR/minishell" ];    then MINISHELL="$SCRIPT_DIR/minishell"
else
    echo "ERROR: minishell binary not found (looked next to intento_de_tester/)"
    exit 1
fi

python3 - "$SCRIPT_DIR" "$MINISHELL" "${TIMEOUT:-5}" "${VERBOSE:-0}" "${FILTER:-}" << 'PYEOF'
import sys, os, re, subprocess

script_dir = sys.argv[1]
minishell  = sys.argv[2]
timeout_s  = int(sys.argv[3])
verbose    = sys.argv[4] == "1"
filter_str = sys.argv[5]

GREEN = "\033[32m"; RED = "\033[31m"; RESET = "\033[0m"
PASS = FAIL = SKIP = 0

# ---------------------------------------------------------------------------
# Normalise output  (same rules as the bash normalize() in run_tests.sh)
# ---------------------------------------------------------------------------
def normalize(lines):
    out = []
    for ln in lines:
        ln = re.sub(r'^bash: ',                   'shell: ', ln)
        ln = re.sub(r'^minishell: ', 'shell: ', ln)
        ln = re.sub(r'^shell: line \d+: ', 'shell: ', ln)
        ln = re.sub(r'^shell: command not found: (.+)', r'shell: \1: command not found', ln)
        ln = re.sub('/usr/bin/python3', '/usr/bin/env', ln)
        if ln.strip():
            out.append(ln)
    return out

# ---------------------------------------------------------------------------
# Parse a .sh file into a list of logical commands.
# Handles:
#   - heredocs  (<<DELIM ... DELIM)
#   - backslash line-continuations
#   - blank lines and comments are skipped
# ---------------------------------------------------------------------------
def parse_commands(path):
    commands   = []
    current    = []
    in_heredoc = False
    hd_delim   = None

    with open(path, errors='replace') as f:
        for raw in f:
            raw      = raw.rstrip('\n')
            stripped = raw.strip()

            if in_heredoc:
                current.append(raw)
                if stripped == hd_delim:
                    in_heredoc = False
                    commands.append('\n'.join(current))
                    current = []
                continue

            if not stripped or stripped.startswith('#'):
                continue

            current.append(raw)

            m = re.search(r'<<-?\s*[\'"]?(\w+)[\'"]?', raw)
            if m:
                in_heredoc = True
                hd_delim   = m.group(1)
                continue

            if raw.rstrip().endswith('\\'):
                continue

            commands.append('\n'.join(current))
            current = []

    if current:
        commands.append('\n'.join(current))
    return commands

# ---------------------------------------------------------------------------
# Build a marker-wrapped script.
#
# We bracket each command with:
#   echo  ___CMD_N___       <- always on its own line (echo adds \n)
#   <command>
#   /usr/bin/printf '\n___END_N___\n'
#                           <- \n prefix guarantees a new line even after
#                              "echo -n" (no trailing newline), and printf
#                              is an external binary so it works in minishell.
# ---------------------------------------------------------------------------
def build_marked_script(commands):
    parts = []
    for i, cmd in enumerate(commands):
        parts.append(f'echo ___CMD_{i}___')
        parts.append(cmd)
        parts.append(f"/usr/bin/printf '\\n___END_{i}___\\n'")
    parts.append(f'echo ___CMD_{len(commands)}___')   # final sentinel
    return '\n'.join(parts)

# ---------------------------------------------------------------------------
# Run script_content through shell_path; return (stdout+stderr, exitcode, timedout).
# ---------------------------------------------------------------------------
def run_shell(shell, script, timeout):
    try:
        p = subprocess.run(
            [shell],
            input=script.encode(),
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            timeout=timeout,
        )
        return p.stdout.decode(errors='replace'), p.returncode, False
    except subprocess.TimeoutExpired:
        return '', 124, True

# ---------------------------------------------------------------------------
# Split the combined stdout of a marked script into per-command output lists.
#
# State machine:
#   ___CMD_N___  -> start collecting into bucket N
#   ___END_N___  -> stop  collecting  (go back to "between" state)
# ---------------------------------------------------------------------------
def split_by_markers(raw, num_cmds):
    buckets    = [[] for _ in range(num_cmds)]
    cur        = -1
    collecting = False

    for line in raw.splitlines():
        m_cmd = re.fullmatch(r'___CMD_(\d+)___', line)
        m_end = re.fullmatch(r'___END_(\d+)___', line)

        if m_cmd:
            cur        = int(m_cmd.group(1))
            collecting = (cur < num_cmds)
        elif m_end:
            collecting = False
            cur        = -1
        elif collecting and 0 <= cur < num_cmds:
            buckets[cur].append(line)

    return [normalize(b) for b in buckets]

# ---------------------------------------------------------------------------
# Discover and run all test scripts
# ---------------------------------------------------------------------------
scripts = sorted(f for f in os.listdir(script_dir) if re.match(r'\d\d_.*\.sh$', f))

print("=" * 62)
print(f" Minishell Test Runner v2   (timeout: {timeout_s}s per test)")
print(f" Binary  : {minishell}")
print(f" Tests   : {len(scripts)} files")
print(f" Output  : comparison.txt")
print("=" * 62)
print()

sections = []   # (name, commands, bash_buckets, ms_buckets, bash_ec, ms_ec, status)

for script_name in scripts:
    name = script_name[:-3]

    if filter_str and filter_str not in name:
        SKIP += 1
        continue

    path     = os.path.join(script_dir, script_name)
    commands = parse_commands(path)
    if not commands:
        continue

    use_ec = 'exit' in name
    marked = build_marked_script(commands)

    bash_raw, bash_ec, bash_to = run_shell('bash',    marked, timeout_s)
    ms_raw,   ms_ec,   ms_to   = run_shell(minishell, marked, timeout_s)

    if ms_to:
        print(f"{RED}[FAIL] {name}  -- TIMEOUT (>{timeout_s}s){RESET}")
        FAIL += 1
        continue

    bash_bkts = split_by_markers(bash_raw, len(commands))
    ms_bkts   = split_by_markers(ms_raw,   len(commands))

    out_ok = (bash_bkts == ms_bkts)
    ec_ok  = (not use_ec) or (bash_ec == ms_ec)

    if out_ok and ec_ok:
        suffix = f" (exit={bash_ec})" if use_ec else ""
        print(f"{GREEN}[PASS] {name}{suffix}{RESET}")
        PASS += 1
        status = "PASS"
    elif out_ok and not ec_ok:
        print(f"{RED}[FAIL] {name}  -- output ok, exit: bash={bash_ec} mini={ms_ec}{RESET}")
        FAIL += 1
        status = "FAIL-EC"
    else:
        print(f"{RED}[FAIL] {name}{RESET}")
        if verbose:
            for i, (cmd, b, m) in enumerate(zip(commands, bash_bkts, ms_bkts)):
                if b != m:
                    print(f"  cmd [{i}] : {cmd[:70]}")
                    print(f"  bash     : {b}")
                    print(f"  mini     : {m}")
                    print()
        FAIL += 1
        status = "FAIL"

    sections.append((name, commands, bash_bkts, ms_bkts, bash_ec, ms_ec, status))

print()
print("=" * 62)
total = PASS + FAIL
print(f" Results: {PASS}/{total} passed  |  {FAIL} failed  |  {SKIP} skipped")
if FAIL == 0 and total > 0:
    print(f"{GREEN} All tests passed!{RESET}")
elif FAIL > 0:
    print(" Tip: VERBOSE=1 ./run_tests_v2.sh   to see per-command diffs")
    print(" Tip: TIMEOUT=N ./run_tests_v2.sh   to change per-test timeout")
    print(" Tip: FILTER=x  ./run_tests_v2.sh   to run only tests matching 'x'")
print("=" * 62)
print()

# ---------------------------------------------------------------------------
# Generate comparison.txt
#
# Three columns:
#   COMMAND (CMD_W chars)  |  BASH OUTPUT (COL_W chars)  |  MINISHELL OUTPUT
#
# Within each test section:
#   === name === [STATUS]
#   heavy bar
#   cmd text        |  bash line 0     |  [!] minishell line 0
#   (continuation)  |  bash line 1     |      minishell line 1
#   blank separator row between every command
#   light bar + blank line between test sections
# ---------------------------------------------------------------------------
CMD_W = 65
COL_W = 70
SEP   = "  |  "
DIFF  = "!"    # marker in minishell column when line differs

total_w = CMD_W + len(SEP) + COL_W + len(SEP) + 1 + COL_W
HEAVY   = "=" * total_w
LIGHT   = "-" * total_w

def clip(s, w):
    return (s[:w - 1] + "~") if len(s) > w else s

def pad(s, w):
    return clip(s, w).ljust(w)

lines_out = []
lines_out.append(pad("COMMAND", CMD_W) + SEP + pad("BASH", COL_W) + SEP + " MINISHELL")
lines_out.append(HEAVY)

for name, commands, bash_bkts, ms_bkts, bash_ec, ms_ec, status in sections:
    ec_note = f"  (bash_exit={bash_ec}  mini_exit={ms_ec})" if bash_ec != ms_ec else ""
    lines_out.append(f"  {name}  [{status}]{ec_note}")
    lines_out.append(HEAVY)

    for i, cmd in enumerate(commands):
        bout     = bash_bkts[i] if i < len(bash_bkts) else []
        mout     = ms_bkts[i]   if i < len(ms_bkts)   else []
        cmd_rows = cmd.splitlines()   # multi-line for heredocs

        n = max(len(cmd_rows), len(bout), len(mout), 1)
        for j in range(n):
            c    = cmd_rows[j] if j < len(cmd_rows) else ""
            b    = bout[j]     if j < len(bout)     else ""
            m    = mout[j]     if j < len(mout)     else ""
            mark = DIFF if b != m else " "
            lines_out.append(pad(c, CMD_W) + SEP + pad(b, COL_W) + SEP + mark + m)

        lines_out.append("")   # blank row between commands

    lines_out.append(LIGHT)
    lines_out.append("")

out_path = os.path.join(script_dir, "comparison.txt")
with open(out_path, "w") as f:
    f.write("\n".join(lines_out) + "\n")

n_fail = sum(1 for s in sections if "FAIL" in s[6])
print(f"  >>> comparison.txt written  ({len(sections)} sections, {n_fail} with failures)")
PYEOF
