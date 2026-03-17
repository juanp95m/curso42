# Executor Steps: Understanding Command Execution in Minishell

The executor is the heart of any shell, responsible for taking the parsed commands and bringing them to life. This document breaks down the intricate process of command execution, focusing on external commands, built-ins, I/O redirection, and the crucial role of pipes.

## 1. Execution Flow Overview

After the user types a command and presses Enter, Minishell goes through several phases:

1.  **Lexing:** The input string is broken down into meaningful tokens (words, operators like `<`, `>`, `|`).
2.  **Parsing:** These tokens are then structured into one or more `t_command` objects, representing simple commands, pipelines, and redirections.
3.  **Execution:** The executor takes these `t_command` structures and performs the necessary system calls to run the commands, manage I/O, and handle processes.

The executor must distinguish between:
*   **Built-in Commands:** Commands handled directly by the shell process itself (e.g., `cd`, `echo`).
*   **External Commands:** Programs located in the file system (e.g., `/bin/ls`, `/usr/bin/grep`). These require creating new processes.

## 2. Built-in Commands

Built-in commands are functions compiled directly into the shell executable. They are executed within the shell's own process.

**Characteristics:**

*   **No `fork()` typically:** They don't usually require creating a new child process. This makes them faster and more efficient.
*   **Directly modify shell state:** Built-ins like `cd`, `export`, `unset` can change the shell's current working directory or environment variables. An external `cd` command (if one existed) would only change the directory of its child process, not the shell's.
*   **I/O Redirection:** Even though they don't `fork`, built-ins still respect I/O redirections. Their standard input/output streams can be changed using `dup2()`, but these changes must be carefully reverted afterward to avoid affecting subsequent shell operations.

**Examples in Minishell:**
`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

**Execution Process for Built-ins:**

1.  Identify if the command is a built-in.
2.  If it is, save the current `STDIN_FILENO` and `STDOUT_FILENO` with `dup()` so they can be restored later. 
   `tmp_stdin = dup(STDIN_FILENO); tmp_stdout = dup(STDOUT_FILENO);`
3.  Apply any I/O redirections (using `dup2()`). 
   `dup2(fd_input_file, STDIN_FILENO); dup2(fd_output_file, STDOUT_FILENO);`
4.  Call the corresponding built-in function (e.g., `ft_cd(args)`).
5.  Restore the original `STDIN_FILENO` and `STDOUT_FILENO` (using `dup2()` with saved FDs).
   `dup2(tmp_stdin, STDIN_FILENO); dup2(tmp_stdout, STDOUT_FILENO);`
7.  Set the shell's exit status.

## 3. External Commands

External commands are executable programs found in the system's file path. Executing them involves a series of crucial system calls.

**The `fork`-`execve`-`waitpid` Triad:**

This is the fundamental pattern for running external programs.

### `fork()`: Creating a Child Process

`pid_t fork(void);`

*   **Purpose:** Creates a new process that is an almost exact copy of the calling process (the parent).
*   **Return Value:**
    *   **In the parent:** Returns the Process ID (PID) of the new child process.
    *   **In the child:** Returns `0`.
    *   **On error:** Returns `-1`.

**Conceptual Diagram:**

```
  Parent Process (Shell)
         |
         |  fork()
         V
  +-----------------+-----------------+
  |                 |                 |
  | Parent Continues| Child Process   |
  | (e.g., waits)   | (copy of parent)|
  | PID = child_pid | PID = 0         |
  +-----------------+-----------------+
```

After `fork()`, both parent and child processes execute concurrently, starting from the line immediately after the `fork()` call. They have separate memory spaces.

### `execve()`: Replacing the Child's Image

`int execve(const char *pathname, char *const argv[], char *const envp[]);`

*   **Purpose:** Replaces the current process image with a new process image specified by `pathname`. This means the code, data, and stack of the calling process are overwritten.
*   **`pathname`:** The path to the executable file (e.g., `/bin/ls`).
*   **`argv`:** An array of strings representing the command-line arguments for the new program (e.g., `{"ls", "-l", NULL}`).
*   **`envp`:** An array of strings representing the environment variables for the new program (e.g., `{"PATH=/usr/bin:/bin", "USER=malj", NULL}`).
*   **Return Value:** `execve()` *only returns if an error occurs*. If successful, the new program begins execution from its `main()` function.

**Finding `pathname` (PATH Resolution):**
If `pathname` is not an absolute path (doesn't start with `/`), the shell searches for the executable in the directories listed in the `PATH` environment variable.

**Conceptual Diagram (inside the child process):**

```
  Child Process (copy of Shell)
         |
         |  I/O redirections (dup2)
         |
         |  execve("/bin/ls", {"ls", "-l"}, envp)
         V
  +-----------------+
  |                 |
  |  New Process    |
  |  (e.g., 'ls -l')|
  |                 |
  +-----------------+
  (Original child process image is gone)
```

### `waitpid()`: Parent Waiting for Child

`pid_t waitpid(pid_t pid, int *wstatus, int options);`

*   **Purpose:** The parent process uses `waitpid()` to wait for a specific child process (`pid`) to change state (e.g., terminate, stop, or resume).
*   **`pid`:**
    *   `> 0`: Wait for the child with the specified PID.
    *   `-1`: Wait for any child process.
    *   `0`: Wait for any child process in the same process group as the caller.
*   **`wstatus`:** A pointer to an integer where status information about the child's termination is stored. Macros like `WIFEXITED()`, `WEXITSTATUS()`, `WIFSIGNALED()`, `WTERMSIG()` are used to interpret this value.
*   **`options`:** `WNOHANG` (don't block), `WUNTRACED` (return if child is stopped).

**Conceptual Diagram:**

```
  Parent Process (Shell)          Child Process (ls -l)
         |                                |
         | fork()                         |
         |--------------------------------|
         |                                |
         | waitpid(child_pid, &status, 0) | (executes 'ls -l')
         | (blocks)                       |
         |                                |
         |                                |
         |                                | (finishes)
         |<-------------------------------|
         | (unblocks)                     |
         |                                |
         | Interprets status              |
```

## 4. I/O Redirection

A shell allows users to change where a command reads its input from (stdin) or sends its output to (stdout, stderr). This is managed using file descriptors and the `dup2()` system call.

### File Descriptors (FDs)

In Unix-like systems, everything is a file. This includes devices, sockets, and pipes. When a process opens a file or creates a pipe, it gets a small integer called a file descriptor.

*   `0`: **STDIN_FILENO** (Standard Input) - Default: keyboard.
*   `1`: **STDOUT_FILENO** (Standard Output) - Default: terminal screen.
*   `2`: **STDERR_FILENO** (Standard Error) - Default: terminal screen.

### `dup()` and `dup2()` System Calls

These functions are used to duplicate file descriptors, effectively allowing you to redirect I/O.

#### `int dup(int oldfd);`
*   **Purpose:** Creates a *new* file descriptor that refers to the same open file description as `oldfd`. The new FD will be the lowest available number. Normally is used when you want to save a copy of an existing FD before redirecting it. In this project dup is used in the built-in commands to save the original STDIN and STDOUT before applying redirections, so that they can be restored afterward. Why only in built-ins? Because built-ins run in the shell process itself, so they need to restore the original FDs after execution. External commands run in child processes, so they don't need to restore FDs since the child process will be replaced by `execve()`.
*   **Example:** `new_fd = dup(old_fd);`

#### `int dup2(int oldfd, int newfd);`
*   **Purpose:** Duplicates `oldfd` to `newfd`. If `newfd` is already open, it is first closed. Then `newfd` is made to refer to the same open file description as `oldfd`.
*   **Key for Redirection:** This is the workhorse for redirection because you can force a specific file (e.g., `output.txt`) to become `STDIN_FILENO`, `STDOUT_FILENO`, or `STDERR_FILENO`.

**Conceptual Diagram of `dup2(fd_file, STDOUT_FILENO)`:**

```
BEFORE dup2:
  FD Table of Process:
  0 (STDIN)  -> Keyboard
  1 (STDOUT) -> Terminal Screen
  2 (STDERR) -> Terminal Screen
  3 (fd_file)-> "output.txt" (open for writing)

AFTER dup2(fd_file, STDOUT_FILENO):
  FD Table of Process:
  0 (STDIN)  -> Keyboard
  1 (STDOUT) -> "output.txt"  <-- Now points to the file!
  2 (STDERR) -> Terminal Screen
  3 (fd_file)-> "output.txt"  <-- Old FD for the file still exists,
                                   should be closed if no longer needed.
```

### Types of Redirection and Implementation:

**General Steps for any Redirection:**

1.  Open the target file (`open()` system call).
2.  If it's an input redirection (`<`), `dup2(fd_file, STDIN_FILENO)`.
3.  If it's an output redirection (`>` or `>>`), `dup2(fd_file, STDOUT_FILENO)`.
4.  Close the original file descriptor for the file (`close(fd_file)`). It's no longer needed because `STDIN_FILENO`/`STDOUT_FILENO` now point to it.

#### `<` (Input Redirection)
`command < input.txt`

*   Opens `input.txt` for reading.
*   Makes `STDIN_FILENO` (0) point to `input.txt`.

**Code Example (Conceptual, inside child before `execve`):**
```c
int fd_in = open("input.txt", O_RDONLY);
if (fd_in == -1) { /* error handling */ }
dup2(fd_in, STDIN_FILENO); // Redirect stdin to input.txt
close(fd_in);             // Close original fd_in (fd_in == STDIN_FILENO now)
// execve(...)
```

#### `>` (Output Redirection - Truncate)
`command > output.txt`

*   Opens `output.txt` for writing, creating it if it doesn't exist, and truncating it if it does.
*   Makes `STDOUT_FILENO` (1) point to `output.txt`.

**Code Example:**
```c
int fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd_out == -1) { /* error handling */ }
dup2(fd_out, STDOUT_FILENO); // Redirect stdout to output.txt
close(fd_out);
// execve(...)
```

#### `>>` (Output Redirection - Append)
`command >> append.txt`

*   Opens `append.txt` for writing, creating it if it doesn't exist, and appending to the end if it does.
*   Makes `STDOUT_FILENO` (1) point to `append.txt`.

**Code Example:**
```c
int fd_append = open("append.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
if (fd_append == -1) { /* error handling */ }
dup2(fd_append, STDOUT_FILENO); // Redirect stdout to append.txt
close(fd_append);
// execve(...)
```

#### `2>` (Standard Error Redirection)
`command 2> error.log`

*   Similar to `>` but redirects `STDERR_FILENO` (2).

**Code Example:**
```c
int fd_err = open("error.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd_err == -1) { /* error handling */ }
dup2(fd_err, STDERR_FILENO); // Redirect stderr to error.log
close(fd_err);
// execve(...)
```
You can also redirect `stderr` to `stdout` using `2>&1`. This implies `dup2(STDOUT_FILENO, STDERR_FILENO);`.

### Example Exercise: Redirection

**Command:** `echo "Hello World" > output.txt`
**Steps:**
1.  Shell forks.
2.  Child process:
    a.  Opens `output.txt` in `O_WRONLY | O_CREAT | O_TRUNC` mode. Let's say `fd_out = 3`.
    b.  `dup2(3, 1)` (redirects `STDOUT_FILENO` to `output.txt`).
    c.  Closes `fd_out` (3).
    d.  `execve("/bin/echo", {"echo", "Hello World"}, envp)`.
3.  The `echo` command writes "Hello World" to its `STDOUT_FILENO`, which is now `output.txt`.
4.  Parent process waits for child.

## 5. Pipes (`|`)

Pipes are a form of inter-process communication (IPC) that allows the output of one command to be used as the input of another. `command1 | command2`

### What are Pipes?

A pipe is a unidirectional data channel. Data written to one end of the pipe can be read from the other end.

### `pipe()` System Call

`int pipe(int pipefd[2]);`

*   **Purpose:** Creates a pipe and returns two file descriptors in the `pipefd` array:
    *   `pipefd[0]`: The read end of the pipe.
    *   `pipefd[1]`: The write end of the pipe.
*   **Return Value:** `0` on success, `-1` on error.

**Conceptual Diagram of `pipe()`:**

```
pipefd[0] <--- READ FROM PIPE ---|-----|--- WRITE TO PIPE ---> pipefd[1]
                                 Pipe Buffer
```

### Connecting Commands with Pipes

For a pipeline like `cmd1 | cmd2 | cmd3`, you need a pair of pipes between each command.

**Execution Steps for `command1 | command2`:**

1.  **Create a pipe:** The parent shell calls `pipe(pipefd)`.
    *   `pipefd[0]` (read end)
    *   `pipefd[1]` (write end)
2.  **Fork for `command1`:**
    *   **Child 1 (for `command1`):**
        *   Closes `pipefd[0]` (read end, as `command1` only writes to the pipe).
        *   `dup2(pipefd[1], STDOUT_FILENO)`: Redirect `command1`'s `stdout` to the write end of the pipe.
        *   Closes `pipefd[1]`.
        *   Applies any other redirections for `command1`.
        *   `execve("command1", ...)`.
    *   **Parent:** Does not close anything yet. It will fork again for `command2`.
3.  **Fork for `command2`:**
    *   **Child 2 (for `command2`):**
        *   Closes `pipefd[1]` (write end, as `command2` only reads from the pipe).
        *   `dup2(pipefd[0], STDIN_FILENO)`: Redirect `command2`'s `stdin` to the read end of the pipe.
        *   Closes `pipefd[0]`.
        *   Applies any other redirections for `command2`.
        *   `execve("command2", ...)`.
    *   **Parent:** Now, the parent has forked both children. It must `close(pipefd[0])` and `close(pipefd[1])` to ensure the pipe is correctly managed. If the parent keeps the pipe ends open, the children might not receive EOF correctly.
4.  **Parent `waitpid()` for both children.**

**Conceptual Diagram: `cmd1 | cmd2`**

```
                       pipefd[0] <--- READ END
                       pipefd[1] ---> WRITE END

        Shell Process
             |
             | pipe() (creates pipefd[0], pipefd[1])
             |
             | fork() for cmd1
             +--------------------+---------------------+
             | Child 1 (for cmd1) |     Shell Parent    |
             |--------------------|                     |
             | close(pipefd[0])   |  fork() for cmd2    |
             | dup2(pipefd[1], 1) |---------------------+-------------------+
             | close(pipefd[1])   | Child 2 (for cmd2)  |   Shell Parent    |
             | (execve cmd1)      |---------------------|                   |
             |                    | close(pipefd[1])    | close(pipefd[0])  |
             |                    | dup2(pipefd[0], 0)  | close(pipefd[1])  |
             |                    | close(pipefd[0])    | waitpid(child1)   |
             |                    | (execve cmd2)       | waitpid(child2)   |
             |                    |                     |                   |
             V                    V                     V                   V
      cmd1 writes to pipe       cmd2 reads from pipe     Shell continues
```

### Example Exercise: Pipe

**Command:** `ls -l | grep "minishell"`
**Steps:**
1.  Shell creates a pipe: `pipefd[0]` (read), `pipefd[1]` (write).
2.  Shell forks for `ls -l`.
    a.  Child (LS): Closes `pipefd[0]`. `dup2(pipefd[1], STDOUT_FILENO)`. Closes `pipefd[1]`. `execve("/bin/ls", {"ls", "-l"}, envp)`.
3.  Shell forks for `grep "minishell"`.
    a.  Child (GREP): Closes `pipefd[1]`. `dup2(pipefd[0], STDIN_FILENO)`. Closes `pipefd[0]`. `execve("/bin/grep", {"grep", "minishell"}, envp)`.
4.  Parent: Closes `pipefd[0]` and `pipefd[1]`. Waits for both children.
5.  `ls -l` writes its output to the pipe. `grep "minishell"` reads from the pipe and filters the lines, printing matching ones to its `STDOUT_FILENO` (which is still the terminal).

## 6. Combining Redirections and Pipes

When a command has both redirections and is part of a pipeline, redirections are applied *after* the pipe connection. This means that a redirection will override the pipe's standard input/output.

**Example:** `cat < in.txt | grep "word" > out.txt`

1.  `cat < in.txt`: `cat`'s `stdin` comes from `in.txt`. Its `stdout` goes to the pipe.
2.  `grep "word" > out.txt`: `grep`'s `stdin` comes from the pipe. Its `stdout` goes to `out.txt`.

**Order of Operations (inside a child process):**
1.  Close unused pipe ends.
2.  `dup2()` for pipe connections (e.g., `dup2(pipe_read_end, STDIN_FILENO)` for the right-hand side of a pipe).
3.  Apply explicit file redirections (e.g., `dup2(fd_input_file, STDIN_FILENO)`). This will override the pipe's `dup2` if both are present for `STDIN`.
4.  Close any remaining original file descriptors.
5.  `execve()`.

## 7. Error Handling and Exit Status

Robust error handling is critical for a shell.

*   **Check Return Values:** Always check the return values of system calls (`fork`, `pipe`, `open`, `dup2`, `execve`). If a call fails, `perror()` can print a descriptive error message.
*   **Child Process Exit Status:** When a child process terminates, its exit status is passed back to the parent via `waitpid()`.
    *   `WIFEXITED(status)`: True if child exited normally.
    *   `WEXITSTATUS(status)`: The actual exit code (0 for success, non-zero for error).
    *   `WIFSIGNALED(status)`: True if child was terminated by a signal.
    *   `WTERMSIG(status)`: The signal number that terminated the child.
*   **Shell Variable Exit Status `($?)`:** The shell stores the exit status of the last foreground command in the special variable `$?`. Your shell must update this after each command execution.

## 8. Visual Learning Tips

Understanding process creation, file descriptors, and pipes can be abstract.

*   **Draw Diagrams:** Always draw the file descriptor tables for the parent and each child process, and how `dup2()` changes them. Sketch the pipes as physical connections.
*   **Use `strace`:** The `strace` command (on Linux) is an invaluable tool. It traces system calls made by a process.
    *   `strace -f -o output.txt minishell` will run your shell and record all system calls (including those of forked children due to `-f`). Analyze `output.txt` to see `fork`, `pipe`, `open`, `dup2`, `execve`, `waitpid` calls in action.
    *   `strace -e open,dup2,pipe,fork,execve ls -l | grep "minishell"`: You can filter `strace` to only show specific system calls for a command.

By diligently working through these steps and utilizing visual aids and debugging tools, you'll gain a deep understanding of how your Minishell executes commands.

For example:
```
$ strace -f -e open,dup2,pipe,fork,execve ls -l | grep "minishell"
```

```
open("/bin/ls", O_RDONLY) = 3 
pipe([4, 5]) = 0 
fork() = 12345 (child process) 
[Child Process] 
dup2(5, 1) = 1 
close(4) 
close(5) 
execve("/bin/ls", ["ls", "-l"], envp) = 0 
[Parent Process] close(5) waitpid(12345, &status, 0) = 12345
close(5) 
waitpid(12345, &status, 0) = 12345
```
This output shows the parent process creating a pipe, forking a child, the child redirecting its `stdout` to the pipe, and executing `ls -l`. The parent waits for the child to finish.


## Minimal examples to understand Pipes

**Example 1: `ls -l | grep "minishell"`**
1.  Shell creates a pipe: `pipefd[0]` (read), `pipefd[1]` (write).
2.  Shell forks for `ls -l`.
3.  Child (LS): Closes `pipefd[0]`. `dup2(pipefd[1], STDOUT_FILENO)`. Closes `pipefd[1]`. `execve("/bin/ls", {"ls", "-l"}, envp)`.
4.  Shell forks for `grep "minishell"`. 
5.  Child (GREP): Closes `pipefd[1]`. `dup2(pipefd[0], STDIN_FILENO)`. 
6.  Closes `pipefd[0]`. `execve("/bin/grep", {"grep", "minishell"}, envp)`. 
7.  Parent: Closes `pipefd[0]` and `pipefd[1]`. Waits for both children. 

**Example 2: `cat < in.txt | grep "word" > out.txt`** 
1. Shell creates a pipe: `pipefd[0]` (read), `pipefd[1]` (write). 
2. Shell forks for `cat < in.txt`. 
3. Child (CAT): Opens `in.txt`, `dup2(fd_in, STDIN_FILENO)`, closes `fd_in`. Closes `pipefd[0]`. `dup2(pipefd[1], STDOUT_FILENO)`. Closes `pipefd[1]`. Executes `cat`. 
4. Shell forks for `grep "word" > out.txt`. 
5. Child (GREP): Opens `out.txt`, `dup2(fd_out, STDOUT_FILENO)`, closes `fd_out`. Closes `pipefd[1]`. `dup2(pipefd[0], STDIN_FILENO)`. Closes `pipefd[0]`. Executes `grep`. 
6. Parent: Closes both ends of the pipe and waits for children.

**Example 3: `echo "Hello World" > output.txt`** 
1. Shell forks for `echo`. 
2. Child (ECHO): Opens `output.txt` in write mode, `dup2(fd_out, STDOUT_FILENO)`, closes `fd_out`. Executes `echo`. 
3. Parent waits for child.


# Exercises to understand Pipes and Redirections

These are standalone C programs you can compile and run to build intuition about how `pipe()`, `fork()`, and `dup2()` work together.

## Exercise 1: Basic pipe — parent writes, child reads

The simplest possible pipe: the parent sends a string through the pipe, and the child reads and prints it.

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid;
    char    buf[100];

    pipe(pipefd);               // pipefd[0] = read end, pipefd[1] = write end
    pid = fork();
    if (pid == 0)               // CHILD: reads from pipe
    {
        close(pipefd[1]);       // close write end (child only reads)
        read(pipefd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(pipefd[0]);
    }
    else                        // PARENT: writes to pipe
    {
        close(pipefd[0]);       // close read end (parent only writes)
        write(pipefd[1], "hello from parent", 18);
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compile and run: `gcc -o ex1 ex1.c && ./ex1`

**What to observe:**
- The child prints `hello from parent` even though no file was involved — data traveled through the pipe in memory.
- Each side closes the end it doesn't use. This is **critical** — if the child doesn't close the write end, `read()` will never get EOF.

---

## Exercise 2: Pipe + `dup2` — redirect stdout to pipe

Now we make the child redirect its `stdout` into the pipe, so the parent can capture what the child "prints".

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid;
    char    buf[100];
    int     n;

    pipe(pipefd);
    pid = fork();
    if (pid == 0)               // CHILD: redirect stdout → pipe, then write
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);  // stdout now goes into the pipe
        close(pipefd[1]);
        printf("I am the child!\n");     // this goes to the pipe, not terminal
    }
    else                        // PARENT: read from pipe
    {
        close(pipefd[1]);
        n = read(pipefd[0], buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Parent captured: %s", buf);
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compile and run: `gcc -o ex2 ex2.c && ./ex2`

**What to observe:**
- The child's `printf` doesn't appear on the terminal — it goes into the pipe.
- The parent reads it and prints `Parent captured: I am the child!`.
- This is exactly what happens in `cmd1 | cmd2`: cmd1's stdout is redirected to the pipe.

---

## Exercise 3: Simulating `ls | grep` with `execve`

This is the real deal — two child processes connected by a pipe, each replaced by an external program via `execve`.

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid1;
    pid_t   pid2;

    pipe(pipefd);

    // --- Child 1: runs "ls -l", stdout → pipe ---
    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]);                        // don't need read end
        dup2(pipefd[1], STDOUT_FILENO);          // stdout → pipe
        close(pipefd[1]);
        char *argv[] = {"ls", "-l", NULL};
        char *envp[] = {NULL};
        execve("/bin/ls", argv, envp);
        perror("execve ls");                     // only reached on error
    }

    // --- Child 2: runs "grep Makefile", stdin ← pipe ---
    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]);                        // don't need write end
        dup2(pipefd[0], STDIN_FILENO);           // stdin ← pipe
        close(pipefd[0]);
        char *argv[] = {"grep", "Makefile", NULL};
        char *envp[] = {NULL};
        execve("/usr/bin/grep", argv, envp);
        perror("execve grep");
    }

    // --- Parent: close both ends and wait ---
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
```

Compile and run: `gcc -o ex3 ex3.c && ./ex3`

**What to observe:**
- Output is the same as running `ls -l | grep Makefile` in bash.
- The parent **must** close both pipe ends — otherwise `grep` never receives EOF and hangs forever.
- Each child closes the pipe end it doesn't use **before** calling `execve`.

---

---

## Exercise 4: Output redirection `>` — write to a file (truncate)

Simulates `echo "Hello World" > output.txt`. The child redirects its stdout to a file, then runs a command that writes to stdout.

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    pid = fork();
    if (pid == 0)               // CHILD
    {
        int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (perror("open"), 1);
        dup2(fd, STDOUT_FILENO);    // stdout → output.txt
        close(fd);
        char *argv[] = {"echo", "Hello World", NULL};
        char *envp[] = {NULL};
        execve("/bin/echo", argv, envp);
        perror("execve");
    }
    else                        // PARENT
        waitpid(pid, NULL, 0);
    return (0);
}
```

Compile and run: `gcc -o ex4 ex4.c && ./ex4 && cat output.txt`

**What to observe:**
- Nothing is printed to the terminal — the output went to `output.txt`.
- `cat output.txt` shows `Hello World`.
- `O_TRUNC` means the file is emptied first. Run it twice — the file always has exactly one line.

---

## Exercise 5: Append redirection `>>` — write to a file (append)

Simulates `echo "line N" >> log.txt`. Same as Exercise 4 but with `O_APPEND` instead of `O_TRUNC`.

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    pid = fork();
    if (pid == 0)               // CHILD
    {
        int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (perror("open"), 1);
        dup2(fd, STDOUT_FILENO);    // stdout → log.txt (append)
        close(fd);
        char *argv[] = {"echo", "another line", NULL};
        char *envp[] = {NULL};
        execve("/bin/echo", argv, envp);
        perror("execve");
    }
    else                        // PARENT
        waitpid(pid, NULL, 0);
    return (0);
}
```

Compile and run: `gcc -o ex5 ex5.c && ./ex5 && ./ex5 && ./ex5 && cat log.txt`

**What to observe:**
- Run it multiple times — each run **adds** a line instead of overwriting the file.
- `cat log.txt` shows three lines of `another line`.
- The only difference from Exercise 4 is `O_APPEND` vs `O_TRUNC`.

---

## Exercise 6: Heredoc `<<` — feed inline text as stdin

Simulates `cat << EOF`. The parent writes literal text into a pipe, and the child reads from it as stdin. This is how a shell implements heredocs without temp files.

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid;

    // The "heredoc" content — what the user would type between << EOF and EOF
    char *heredoc = "first line\nsecond line\nthird line\n";

    pipe(pipefd);
    pid = fork();
    if (pid == 0)               // CHILD: stdin ← pipe, then run cat
    {
        close(pipefd[1]);                       // don't need write end
        dup2(pipefd[0], STDIN_FILENO);          // stdin ← pipe
        close(pipefd[0]);
        char *argv[] = {"cat", NULL};
        char *envp[] = {NULL};
        execve("/bin/cat", argv, envp);
        perror("execve");
    }
    else                        // PARENT: write heredoc content into pipe
    {
        close(pipefd[0]);                       // don't need read end
        write(pipefd[1], heredoc, strlen(heredoc));
        close(pipefd[1]);                       // signal EOF to child
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compile and run: `gcc -o ex6 ex6.c && ./ex6`

**What to observe:**
- `cat` prints the three lines to the terminal, even though no file exists — the data came from the pipe.
- The parent writes the heredoc content into the pipe and then **closes** the write end — this sends EOF so `cat` knows when to stop.
- This is exactly how minishell can implement `<< DELIMITER`: read lines from the user until `DELIMITER`, write them into a pipe, and connect the pipe to the command's stdin.

---

## Exercise 7: Interactive heredoc `<<` — read from user until delimiter

This is the real deal. Simulates `cat << EOF` exactly like bash: prompts the user for input line by line, stops when the delimiter is typed, and feeds everything into the command's stdin.

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Reads lines from the user until `delimiter` is typed, writes them into write_fd
void	read_heredoc(int write_fd, const char *delimiter)
{
    char	*line;
    size_t	len;
    ssize_t	nread;

    line = NULL;
    len = 0;
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);          // prompt, just like bash
        nread = getline(&line, &len, stdin);
        if (nread == -1)                        // Ctrl+D (EOF)
            break ;
        // Remove trailing newline for comparison
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';
        if (strcmp(line, delimiter) == 0)        // delimiter found → stop
            break ;
        // Restore the newline and write to pipe
        line[strlen(line)] = '\n';
        write(write_fd, line, strlen(line) + 1);
    }
    free(line);
}

int main(void)
{
    int     pipefd[2];
    pid_t   pid;
    char    *delimiter;

    delimiter = "EOF";                          // change this to test other delimiters
    printf("heredoc> Type lines, then type '%s' to finish:\n", delimiter);

    pipe(pipefd);

    // Read all heredoc input BEFORE forking (like bash does)
    read_heredoc(pipefd[1], delimiter);
    close(pipefd[1]);                           // done writing → send EOF to pipe

    pid = fork();
    if (pid == 0)               // CHILD: stdin ← pipe, then run cat
    {
        close(pipefd[1]);                       // already closed, but good habit
        dup2(pipefd[0], STDIN_FILENO);          // stdin ← pipe
        close(pipefd[0]);
        char *argv[] = {"cat", "-n", NULL};     // -n to number lines
        char *envp[] = {NULL};
        execve("/bin/cat", argv, envp);
        perror("execve");
    }
    else                        // PARENT
    {
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compile and run: `gcc -o ex7 ex7.c && ./ex7`

**Example session:**
```
heredoc> Type lines, then type 'EOF' to finish:
> hello world
> this is a heredoc
> just like in bash
> EOF
     1	hello world
     2	this is a heredoc
     3	just like in bash
```

**What to observe:**
- The program prompts with `> ` for each line, just like bash does with heredocs.
- When you type `EOF` (the delimiter), input stops and `cat -n` prints all the collected lines with line numbers.
- Pressing `Ctrl+D` instead of typing the delimiter also stops input (EOF on stdin).
- The heredoc is read **before** forking — this is important because in minishell, if you have multiple heredocs, they should all be collected before any command runs.
- The key insight: a heredoc is just a pipe where the **shell itself** is the writer instead of another command.

---

### Key takeaways from the exercises

| Rule | Why |
|---|---|
| Always close unused pipe ends | Otherwise `read()` blocks forever waiting for EOF |
| `dup2` before `execve` | The new program inherits the redirected FDs |
| Parent closes both ends after forking | The parent is not part of the data flow |
| `waitpid` for every child | Avoid zombie processes |
| `O_TRUNC` for `>`, `O_APPEND` for `>>` | The only difference between truncate and append redirection |
| Heredoc uses a pipe, not a file | Parent writes content → pipe → child reads as stdin |



# FAQs

**Q: Do I need to close one of the pipes[0] or pipes[1] after creating it with `pipe()`?** Yes, you should close the end of the pipe that you don't use in each process because it could lead to resource leaks and unintended behavior. For example, if a child process is only writing to the pipe, it should close the read end (`pipes[0]`). If a child process is only reading from the pipe, it should close the write end (`pipes[1]`). This is important because if both ends are left open, the reading process will never receive an EOF signal and will block indefinitely.

**but what if I leave both open until I close both after used?**
The rule is about per-process open ends, not timing
The kernel counts how many open file descriptors point to each pipe end across all processes. read() returns EOF only when the reference count of the write end drops to zero — meaning every process that had it open has closed it.

What happens after fork()
```
After pipe() + fork():

Parent holds:  pipefd[0] (read),  pipefd[1] (write)
Child holds:   pipefd[0] (read),  pipefd[1] (write)    ← inherited copies

Write-end reference count = 2  (parent + child)
```

Scenario: child is the reader, but doesn't close pipefd[1]

```
Parent closes pipefd[1]  →  write-end refcount = 1 (child still has it)
Parent closes pipefd[0]  →  (good)

Child calls read(pipefd[0], ...)
  → Kernel checks: is write-end refcount == 0?  NO (child itself holds it)
  → read() blocks FOREVER
  → DEADLOCK — the child is waiting for EOF from itself
```

Scenario: parent keeps both ends open until after waitpid()
```
Child 1 (writer):  closes pipefd[0], writes, closes pipefd[1], exits ✓
Child 2 (reader):  closes pipefd[1], reads...

  → Kernel checks write-end refcount:
      Child 1 closed it  →  refcount decremented
      Parent STILL has it open  →  refcount ≥ 1
  → Child 2's read() NEVER gets EOF
  → Child 2 hangs forever
  → Parent's waitpid() for Child 2 hangs forever
  → DEADLOCK
```

**Q: Why do built-ins need to save and restore file descriptors, but external commands don't?**
Built-ins run in the shell's own process, so any changes they make to file descriptors (like redirecting `stdout`) will affect the shell itself. To prevent this, they save the originalFDs before redirection and restore them afterward. External commands run in child processes created by `fork()`. When the child process executes `execve()`, it replaces its entire memory space with the new program. This means that any changes to file descriptors in the child process do not affect the parentshell, so there is no need to save and restore FDs for external commands.

**Q: What happens if a child process fails to execute `execve()`?**
If `execve()` fails (e.g., the executable is not found, or there are permission issues), it returns `-1` and sets `errno`. The child process should handle this error, typically by printing an error message and exiting with a non-zero status. The parent process will then receive this exit status when it calls `waitpid()`, allowing the shell to set the appropriate exit status for the user.

**Q: Can I have multiple pipes in a single command line?**
Yes, you can have multiple pipes. For example, `cmd1 | cmd2 | cmd3` creates a pipeline where the output of `cmd1` goes to `cmd2`, and the output of `cmd2` goes to `cmd3`. Each command in the pipeline will require its own set of pipes and careful management of file descriptors to ensure that data flows correctly between them.

**Q: Case `cat | cat | echo hola`**
In this case, the first `cat` will read from `stdin` (which is the terminal) and write to the pipe. The second `cat` will read from the pipe and write to its `stdout`, which is also the terminal. The `echo hola` command will execute after the pipeline, and it will print "hola" to the terminal. The first two `cat` commands won't produce any visible output unless you type something into the terminal while they are running, in which case that input would be passed through both `cat` commands before "hola" is printed. But it will neccesary to press Enter per cat command, so the first `cat` will read the input and pass it to the second `cat`, which will then pass it to the terminal. After that, `echo hola` will print "hola". If you just run `cat | cat | echo hola` without typing anything, you'll only see "hola" printed, and the first two `cat` commands will be waiting for input. A similar command to see what is passed from cat is `cat | cat | cat`, where you can type something and see it passed through all three `cat` commands before it is printed to the terminal, but it will get trapped in an infinite loop if you don't press Ctrl+D to signal EOF, because the last `cat` will be waiting for input from the terminal, and the first `cat` will be waiting for input from the terminal as well, creating a deadlock.
