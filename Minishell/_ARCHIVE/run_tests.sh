#!/bin/bash
# =============================================================================
# Minishell Test Runner - with timeout and side-by-side comparison
# (test_master.sh is left untouched; this is the recommended runner)
#
# Usage:
#   ./run_tests.sh                  quiet mode
#   VERBOSE=1     ./run_tests.sh    show diffs on failures
#   FILTER=pipes  ./run_tests.sh    run only tests whose name matches "pipes"
#   TIMEOUT=10    ./run_tests.sh    per-test timeout in seconds (default: 5)
#
# Outputs (in intento_de_tester/):
#   bash_out.txt       normalised bash output, one section per test
#   minishell_out.txt  normalised minishell output, one section per test
#   comparison.txt     side-by-side view: bash | minishell, differences marked
#
# Run from: intento_de_tester/   OR any working directory
# =============================================================================

PASS=0
FAIL=0
SKIP=0

TIMEOUT_SECS=${TIMEOUT:-5}

COLORPASS=$(tput setaf 2)   # green
COLORFAIL=$(tput setaf 1)   # red
COLORSKIP=$(tput setaf 3)   # yellow
COLORRESET=$(tput sgr0)

# ---- Locate the minishell binary ----------------------------------------
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

if   [ -x "$SCRIPT_DIR/../minishell" ]; then
    MINISHELL="$SCRIPT_DIR/../minishell"
elif [ -x "$SCRIPT_DIR/minishell" ]; then
    MINISHELL="$SCRIPT_DIR/minishell"
else
    echo "ERROR: minishell binary not found (looked next to intento_de_tester/)"
    exit 1
fi

# ---- Output normalizer --------------------------------------------------
# Strips cosmetic / implementation-specific differences:
#   bash: / minishell:        → shell:
#   shell: line N: …          → shell: …
#   shell: command not found: foo  → shell: foo: command not found
#   blank lines removed
normalize() {
    sed \
        -e 's/^bash: /shell: /g' \
        -e 's/^minishell: /shell: /g' \
        -e 's/^shell: line [0-9]*: /shell: /g' \
        -e 's/^shell: command not found: \(.*\)/shell: \1: command not found/g' \
        -e '/^[[:space:]]*$/d'
}

# ---- run one test -------------------------------------------------------
# $1 = script path
# $2 = "true" to also compare exit codes
run_test() {
    local script="$1"
    local use_exitcode="${2:-false}"
    local name
    name=$(basename "$script" .sh)

    if [ -n "${FILTER:-}" ] && [[ "$name" != *"$FILTER"* ]]; then
        ((SKIP++))
        return
    fi

    local bash_out minishell_out bash_ec minishell_ec diff_out

    bash_out=$(cat "$script" | timeout "$TIMEOUT_SECS" bash 2>&1 | normalize)
    bash_ec=$?

    minishell_out=$(cat "$script" | timeout "$TIMEOUT_SECS" "$MINISHELL" 2>&1 | normalize)
    minishell_ec=$?

    # timeout exits with code 124; record as FAIL Timeout
    if [ "$minishell_ec" -eq 124 ]; then
        echo "${COLORFAIL}[FAIL] $name  -- TIMEOUT (>${TIMEOUT_SECS}s)${COLORRESET}"
        ((FAIL++))
        {   echo "=== $name ==="
            echo "$bash_out"
            echo ""
        } >> bash_out.txt
        {   echo "=== $name ==="
            echo "[TIMEOUT - no output after ${TIMEOUT_SECS}s]"
            echo ""
        } >> minishell_out.txt
        return
    fi

    {   echo "=== $name ==="
        echo "$bash_out"
        echo ""
    } >> bash_out.txt
    {   echo "=== $name ==="
        echo "$minishell_out"
        echo ""
    } >> minishell_out.txt

    diff_out=$(diff <(echo "$bash_out") <(echo "$minishell_out"))

    local ec_ok=true
    if $use_exitcode && [ "$bash_ec" != "$minishell_ec" ]; then
        ec_ok=false
    fi

    if [ -z "$diff_out" ] && $ec_ok; then
        if $use_exitcode; then
            echo "${COLORPASS}[PASS] $name (exit=$bash_ec)${COLORRESET}"
        else
            echo "${COLORPASS}[PASS] $name${COLORRESET}"
        fi
        ((PASS++))
    elif [ -z "$diff_out" ] && ! $ec_ok; then
        echo "${COLORFAIL}[FAIL] $name  -- output ok but exit code: bash=$bash_ec minishell=$minishell_ec${COLORRESET}"
        ((FAIL++))
    else
        echo "${COLORFAIL}[FAIL] $name${COLORRESET}"
        if $use_exitcode && ! $ec_ok; then
            echo "  exit codes: bash=$bash_ec  minishell=$minishell_ec"
        fi
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

# ---- generate side-by-side comparison -----------------------------------
generate_side_by_side() {
    python3 - bash_out.txt minishell_out.txt comparison.txt "$SCRIPT_DIR" << 'PYEOF'
import sys, os, re

def read_sections(path):
    """Parse a file into [(header_line, [content_lines]), …]."""
    sections = []
    header   = None
    body     = []
    with open(path, "r", errors="replace") as fh:
        for raw in fh:
            line = raw.rstrip("\n")
            if line.startswith("=== ") and line.endswith(" ==="):
                if header is not None:
                    sections.append((header, body))
                header = line
                body   = []
            else:
                body.append(line)
    if header is not None:
        sections.append((header, body))
    return sections

def read_script_cmds(script_dir, section_header):
    """Return non-blank, non-comment lines from the matching .sh file."""
    # header looks like:  === 05_pipes ===
    m = re.match(r"=== (.+) ===$", section_header)
    if not m:
        return []
    name = m.group(1)
    path = os.path.join(script_dir, name + ".sh")
    if not os.path.isfile(path):
        return []
    cmds = []
    with open(path, "r", errors="replace") as fh:
        for raw in fh:
            line = raw.rstrip("\n")
            stripped = line.strip()
            if stripped and not stripped.startswith("#"):
                cmds.append(line)
    return cmds

bash_file, ms_file, out_file, script_dir = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
bash_secs = read_sections(bash_file)
ms_secs   = read_sections(ms_file)

CMD_W = 46          # width of the commands column
COL_W = 46          # max width of bash / minishell columns
SEP   = "  |  "    # column separator
MARK  = " !"       # prefix added to minishell column when line differs

def clip(s, w):
    """Clip string to width w, appending … if truncated."""
    return s[:w - 1] + "…" if len(s) > w else s

def pad(s, w):
    return clip(s, w).ljust(w)

out_lines = []
total_w   = CMD_W + len(SEP) + COL_W + len(SEP) + len(MARK) + COL_W
bar       = "=" * total_w

out_lines.append(pad("COMMANDS", CMD_W) + SEP + pad("BASH OUTPUT", COL_W) + SEP + "   MINISHELL OUTPUT")
out_lines.append(bar)

for i in range(max(len(bash_secs), len(ms_secs))):
    bh, bl = bash_secs[i] if i < len(bash_secs) else ("(missing section)", [])
    mh, ml = ms_secs[i]   if i < len(ms_secs)   else ("(missing section)", [])

    cmds = read_script_cmds(script_dir, bh)

    # Section header
    out_lines.append(pad(bh, CMD_W) + SEP + pad(bh, COL_W) + SEP + "   " + mh)
    out_lines.append("-" * total_w)

    n = max(len(cmds), len(bl), len(ml))
    for j in range(n):
        c = cmds[j] if j < len(cmds) else ""
        b = bl[j]   if j < len(bl)   else ""
        m = ml[j]   if j < len(ml)   else ""
        mark = MARK if b != m else "  "
        out_lines.append(pad(c, CMD_W) + SEP + pad(b, COL_W) + SEP + mark + m)

    out_lines.append("")

with open(out_file, "w") as fh:
    fh.write("\n".join(out_lines) + "\n")

print(f"  >>> comparison.txt written ({len(bash_secs)} bash sections / {len(ms_secs)} minishell sections)")
PYEOF
}

# ---- main ---------------------------------------------------------------
cd "$SCRIPT_DIR"

> bash_out.txt
> minishell_out.txt

echo "============================================================"
echo " Minishell Test Runner   (timeout: ${TIMEOUT_SECS}s per test)"
echo " Binary  : $MINISHELL"
echo " Tests   : $(ls [0-9][0-9]_*.sh 2>/dev/null | wc -l) files"
echo " Outputs : bash_out.txt  minishell_out.txt  comparison.txt"
echo "============================================================"
echo ""

for script in [0-9][0-9]_*.sh; do
    [ -f "$script" ] || continue
    if [[ "$script" == *exit* ]]; then
        run_test "$script" true
    else
        run_test "$script" false
    fi
done

echo ""
echo "============================================================"
total=$((PASS + FAIL))
echo " Results: $PASS/$total passed  |  $FAIL failed  |  $SKIP skipped"
if [ "$FAIL" -eq 0 ] && [ "$total" -gt 0 ]; then
    echo "${COLORPASS} All tests passed!${COLORRESET}"
elif [ "$FAIL" -gt 0 ]; then
    echo " Tip: VERBOSE=1 ./run_tests.sh   to see diffs"
    echo " Tip: TIMEOUT=N ./run_tests.sh   to change per-test timeout (default 5s)"
    echo " Tip: FILTER=x  ./run_tests.sh   to run only tests matching 'x'"
fi
echo "============================================================"
echo ""

generate_side_by_side

rm bash_out.txt minishell_out.txt
rm .heredoc_tmp_*
