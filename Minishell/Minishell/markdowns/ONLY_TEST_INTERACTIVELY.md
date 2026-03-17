# Interactive-Only Tests

These cannot be automated because they require keyboard signals, live `> ` prompts,
or observable shell-exit behavior. Run each command **inside `./minishell`** and
compare with **bash**.

---

## 1. Heredoc — Interactive Prompt

The automated suite tests heredoc output in non-interactive mode.
Here you verify that the `> ` prompt appears for each line and the shell behaves
correctly while you type.

### 1a. Basic cat heredoc

```
cat << EOF
line1
line2
EOF
```

Expected output:

```
line1
line2
```

### 1b. grep heredoc

```
grep "a" << END
apple
banana
cherry
diff
END
```

Expected output:

```
apple
banana
```

### 1c. wc heredoc

```
wc -l << TERMINATOR
line 1
line 2
line 3
TERMINATOR
```

Expected output:

```
3
```

### 1d. Multiple heredocs on one command (only last wins)

```
cat << EOF << OEF << FEO > /tmp/hd_test.txt
```

When bash processes this, it prompts you for **three** heredoc bodies in sequence.
Only the content of `FEO` ends up in the file. Type:

- First prompt → `first body`, then `EOF`
- Second prompt → `second body`, then `OEF`
- Third prompt → `this is saved`, then `FEO`

Then:

```
cat /tmp/hd_test.txt
```

Expected output:

```
this is saved
```

> Note: no output appears after the three heredocs — everything was redirected to the file.

### Current output

```bash
==69560== Command: /usr/bin/cat /tmp/hd_test.txt
==69560==
1st body
EOF
2nd body
OEF
saved
```



---

## 2. Signal Handling

### 2a. Ctrl+C on empty prompt

Press `Ctrl+C` with nothing typed.

Expected: a new prompt appears on the next line. The shell does **not** exit.

```
minishell$ ^C
minishell$
```

`echo $?` → `130`

minishell -> 0

### 2b. Ctrl+C mid-line

Type `echo hel` and press `Ctrl+C` without pressing Enter.

Expected: the line is cancelled, new prompt, shell continues.

```
minishell$ echo hel^C
minishell$
```

### 2c. Ctrl+C during heredoc input

```
cat << EOF
line one
```

While at the heredoc `> ` prompt, press `Ctrl+C`.

Expected: heredoc is cancelled, shell prints a new prompt. Nothing is output.

```
> line one
> ^C
minishell$
```

`echo $?` → `130`

### 2d. Ctrl+D on empty prompt (EOF)

Press `Ctrl+D` with nothing typed.

Expected: shell exits (same as typing `exit`). In bash this also prints `exit` to stderr.

```
minishell$ (press Ctrl+D)
exit
$
```

### 2e. Ctrl+\ should be ignored

Press `Ctrl+\` (SIGQUIT). Shell must **not** quit or print a core dump message.

Expected: nothing happens, prompt stays.

### 2f. Ctrl+C interrupts a running command

```
sleep 10
```

Press `Ctrl+C` while `sleep` is running.

Expected: sleep is killed, new prompt.

```
^C
minishell$
```

Then:

```
echo $?
```

Expected:

```
130
```

but:

```bash
==70525== LEAK SUMMARY:
==70525==    definitely lost: 0 bytes in 0 blocks
==70525==    indirectly lost: 0 bytes in 0 blocks
==70525==      possibly lost: 0 bytes in 0 blocks
==70525==    still reachable: 14,413 bytes in 81 blocks
==70525==         suppressed: 0 bytes in 0 blocks
==70525==
==70525== For lists of detected and suppressed errors, rerun with: -s
==70525== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```



---

## 3. `exit` — Interactive Behavior

### 3a. Plain exit

```
exit
```

Expected: shell prints `exit` to stderr and returns to the parent shell. Exit code = 0.

```
exit
$
```

### 3b. exit with code

```
exit 42
```

Expected: shell prints `exit` to stderr and returns with code 42.

```
exit
$ echo $?
42
```

### 3c. exit inside a pipeline (shell does NOT exit)

```
exit | exit
```

Expected: both sides run in subshells; the main shell continues. No output.

```
minishell$
```

`echo $?` → `0`

### 3d. exit codes in pipeline

```
exit 4 | exit 3
echo $?
```

Expected: rightmost exit code wins.

```
3
```

---

## 4. Variable as Command

```
export TEST="echo hola"
$TEST
```

Expected:

```
hola
```

---

## 5. `cat` Waiting for Keyboard Input

```
cat
```

Type `hello`, press Enter, type `world`, press Enter, then press `Ctrl+D`.

Expected (cat echoes each line immediately as you type it):

```
hello
hello
world
world
```

(Each line appears twice: once from your input echo, once from cat's output.)

---

## 6. Subshells — Bonus Feature

> Only relevant if subshells `(...)` are implemented.

### 6a. Subshell success short-circuits `||`

```
(echo hola && echo adios) || echo uuh
```

Expected:

```
hola
adios
```

### 6b. Subshell fully fails — `||` runs

```
(ecro hola && echy adios) || echo uuh
```

Expected (stderr for each command-not-found, then uuh from `||`):

```
bash: ecro: command not found
uuh
```

### 6c. Subshell partially fails — `||` runs, first output stays

```
(echo hola && echy adios) || echo uuh
```

Expected:

```
hola
bash: echy: command not found
uuh
```

---

## 7. Readline Features (Quality of Life)

These are not graded but expected to work.

| Action           | Expected                                         |
| ---------------- | ------------------------------------------------ |
| Up/Down arrow    | Navigate command history                         |
| Left/Right arrow | Move cursor within line                          |
| Home / End       | Jump to start/end of line                        |
| Ctrl+L           | Clear screen                                     |
| Ctrl+W           | Delete word before cursor                        |
| Tab              | (completion not required by subject, but try it) |
