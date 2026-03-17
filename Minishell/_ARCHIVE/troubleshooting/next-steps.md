# Next Steps: Essential Implementations for Minishell

This document outlines two crucial features for a robust shell: **Signal Handling** and **Heredoc Redirection**. Understanding and implementing these correctly will significantly enhance your Minishell's functionality and user experience.

## 1. Signal Handling

Signals are software interrupts sent to a program to indicate that an important event has occurred. They are a fundamental part of Unix-like operating systems and are vital for interactive shell behavior.

### What are Signals?

Imagine you're running a program in your terminal. What happens if you press `Ctrl-C`? The program usually stops. This is because `Ctrl-C` sends a `SIGINT` (Signal Interrupt) to the foreground process. Signals can be used to:

*   **Interrupt a process:** `SIGINT` (Ctrl-C)
*   **Terminate a process:** `SIGTERM`, `SIGKILL`
*   **Pause/Resume a process:** `SIGSTOP`, `SIGCONT`
*   **Indicate an error:** `SIGSEGV` (Segmentation Fault), `SIGFPE` (Floating Point Exception)
*   **Handle child process status changes:** `SIGCHLD`

In a shell, we need to specifically handle signals to prevent the shell itself from terminating when a child process is interrupted, and to provide proper prompt management.

### Common Signals in a Shell

*   **`SIGINT` (Interrupt):** Sent by `Ctrl-C`.
    *   **Shell (parent process):** Should typically ignore `SIGINT` when a child process is running, to avoid terminating the shell itself. When the shell is waiting for input (e.g., `readline`), `SIGINT` should usually display a new prompt on a new line.
    *   **Child processes:** Should usually terminate upon receiving `SIGINT` (default behavior).
*   **`SIGQUIT` (Quit):** Sent by `Ctrl-`.
    *   **Shell (parent process):** Should generally ignore `SIGQUIT`.
*   **`SIGTERM` (Terminate):** A request to terminate a process gracefully.
*   **`SIGCHLD` (Child Stopped or Terminated):** Sent to the parent process when a child process stops or terminates. This is crucial for the parent to clean up child process resources (e.g., wait for them).

### `signal()` vs. `sigaction()`

Historically, `signal()` was used for signal handling. However, `sigaction()` is the preferred and more robust method for several reasons, primarily its more precise control over signal semantics and reentrancy.

*   **`signal()`:** Simpler, but has portability issues and doesn't guarantee reentrant behavior (meaning the signal handler can safely call functions that might be interrupted by another signal).
*   **`sigaction()`:** Provides finer control, including whether system calls are restarted, and allows blocking other signals within the handler. It's the POSIX standard.

For Minishell, `sigaction()` is recommended.

### Implementation Steps for Signal Handling

The key is to set different signal handlers for the shell process itself and for any child processes it forks to execute commands.

#### 1. Define a Signal Handler Function

A signal handler function typically takes an integer argument (the signal number).

```c
#include <signal.h>
#include <stdio.h> // For perror, printf
#include <readline/readline.h> // For rl_on_new_line, rl_replace_line, rl_redisplay

// Global flag to indicate if a signal was received (optional, for specific logic)
volatile sig_atomic_t g_signal_received = 0;

void    handle_sigint_main(int sig)
{
    (void)sig; // Avoid unused parameter warning
    g_signal_received = 1; // Set flag if needed
    printf("
"); // Move to a new line
    rl_on_new_line(); // Tell readline that we're on a new line
    rl_replace_line("", 0); // Clear the current input buffer
    rl_redisplay(); // Display the new prompt
}

void    handle_sigint_child(int sig)
{
    (void)sig;
    // In a child process, SIGINT should typically just terminate the process.
    // The default behavior is usually sufficient here, but if you want custom
    // cleanup before exit, you could add it.
    // For now, let's just exit with a specific status.
    exit(128 + SIGINT); // 128 + signal_number is a common convention
}

void    handle_sigquit_ignore(int sig)
{
    (void)sig;
    // SIGQUIT (Ctrl-\) should typically be ignored by the shell process.
    // For child processes, you might want to restore default or also ignore.
    printf("Quit: %d
", sig); // Or just do nothing, depending on desired behavior
}

// More generic handler for when no child is running, but readline is not active
void    handle_sigint_waiting(int sig)
{
    (void)sig;
    g_signal_received = 1;
    // Do nothing, let the calling function handle the exit or loop.
    // This could be useful if you're in a loop waiting for something,
    // and SIGINT should break that loop.
}
```

#### 2. Set up `sigaction`

You'll need a function to configure your signal handlers. This function will be called at different points in your shell's lifecycle.

```c
#include <signal.h>
#include <errno.h> // For errno

void    setup_signal_handlers(int mode)
{
    struct sigaction sa;

    // Clear sa to ensure no garbage values
    ft_bzero(&sa, sizeof(sa)); // Assuming ft_bzero from libft

    // SA_RESTART attempts to restart interrupted system calls
    sa.sa_flags = SA_RESTART;
    // Sigemptyset initializes a signal set to empty, blocking no signals
    sigemptyset(&sa.sa_mask);

    if (mode == 0) // Main shell process, waiting for input (readline)
    {
        sa.sa_handler = &handle_sigint_main;
        if (sigaction(SIGINT, &sa, NULL) == -1)
            perror("sigaction SIGINT main");

        sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
        if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction SIGQUIT main");
    }
    else if (mode == 1) // Main shell process, a child command is executing
    {
        sa.sa_handler = SIG_IGN; // Ignore SIGINT (so it only affects child)
        if (sigaction(SIGINT, &sa, NULL) == -1)
            perror("sigaction SIGINT during child exec");

        sa.sa_handler = SIG_IGN; // Ignore SIGQUIT
        if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction SIGQUIT during child exec");
    }
    else if (mode == 2) // Child process (command being executed)
    {
        sa.sa_handler = SIG_DFL; // Restore default SIGINT behavior (terminate)
        if (sigaction(SIGINT, &sa, NULL) == -1)
            perror("sigaction SIGINT child");

        sa.sa_handler = SIG_DFL; // Restore default SIGQUIT behavior (terminate + core dump)
        if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction SIGQUIT child");
    }
    // You might also need a mode to restore defaults or set specific handlers for builtins
}
```

#### 3. Integrate into `main` and `executor`

*   **`main.c`:**
    *   At the start of your `main` loop, before `readline()`, call `setup_signal_handlers(0)` to set handlers for input waiting state.
    *   When you fork a child process to execute an external command:
        *   **Parent:** Before `waitpid()`, call `setup_signal_handlers(1)` to temporarily ignore `SIGINT`/`SIGQUIT` while waiting. After `waitpid()`, restore `setup_signal_handlers(0)`.
        *   **Child:** Immediately after `fork()`, but before `execve()`, call `setup_signal_handlers(2)` to restore default signal behaviors for the command being executed.

```c
// main.c excerpt
int main(int argc, char **argv, char **envp)
{
    // ... initial setup ...
    g_shell = init_shell(envp); // Example shell struct init

    while (1)
    {
        setup_signal_handlers(0); // Set handlers for readline
        char *line = readline("minishell> ");
        g_signal_received = 0; // Reset signal flag

        if (!line) // EOF (Ctrl-D)
        {
            printf("exit
");
            break;
        }
        if (line[0] == '\0') // Empty line
        {
            free(line);
            continue;
        }
        add_history(line);

        // ... lexing, parsing ...
        t_command *cmds = parse_input(line);

        // For external commands:
        if (is_external_command(cmds)) // Pseudo-code
        {
            pid_t pid = fork();
            if (pid == -1)
                perror("fork");
            else if (pid == 0) // Child process
            {
                setup_signal_handlers(2); // Restore defaults for child
                execute_command(cmds); // execve() will replace this process
                exit(1); // Should not reach here if execve succeeds
            }
            else // Parent process
            {
                setup_signal_handlers(1); // Ignore SIGINT/SIGQUIT while waiting
                int status;
                waitpid(pid, &status, 0);
                // Update g_shell->last_exit_status based on WEXITSTATUS/WTERMSIG
            }
        }
        else // Built-in command or other internal logic
        {
            execute_builtin(cmds);
        }

        free(line);
        // ... free cmds structure ...
    }
    // ... cleanup ...
    return (0);
}
```

This ensures that the shell remains responsive to `Ctrl-C` when waiting for input but doesn't die when a child process receives `Ctrl-C`.

## 2. Heredoc Implementation (`<<`)

Heredoc (here document) is a form of I/O redirection that allows you to feed multiple lines of input to a command until a specified delimiter string is encountered. It's commonly seen with commands like `cat << EOF`.

### What is a Heredoc?

A heredoc takes input from the lines immediately following the command until it finds a line containing only the specified delimiter. This input is then redirected to the standard input of the command.

**Example:**
```bash
cat << END_OF_FILE
Hello,
This is a multiline
input for cat.
END_OF_FILE
```
The `cat` command will receive "Hello,
This is a multiline
input for cat.
" as its standard input.

### How it Works (Conceptual)

1.  **Parsing:** When the lexer/parser encounters `<<`, it recognizes it as a heredoc operator. The subsequent token is the `delimiter`.
2.  **Input Collection:** Before executing the main command, the shell needs to read lines from its own standard input until it finds the delimiter.
3.  **Temporary Storage:** The collected lines are stored somewhere that the target command can read them from. This is typically done using:
    *   A **temporary file:** The most common approach. The collected input is written to a file, and then the command's stdin is redirected from this file.
    *   A **pipe:** Less common for a single heredoc, but feasible. The input is written to one end of a pipe, and the command reads from the other.
4.  **Redirection:** The target command's standard input is then redirected to this temporary storage.
5.  **Cleanup:** After the command finishes, the temporary file (if used) must be deleted.

### Implementation Steps for Heredoc

#### 1. Parsing and Identifying Heredocs

Your parser needs to identify `<<` and extract the delimiter. The delimiter can be quoted, which affects how variables inside the heredoc are expanded. If the delimiter is quoted, variable expansion (`$VAR`) does not occur within the heredoc content.

```c
// Example t_command structure could include:
typedef struct s_redir
{
    t_redir_type    type; // e.g., REDIR_IN, REDIR_OUT, REDIR_HEREDOC
    char            *file; // For REDIR_HEREDOC, this would be the delimiter
    // ... other members ...
}   t_redir;

typedef struct s_command
{
    char            **args;
    t_list          *redirections; // List of t_redir
    // ... other members ...
}   t_command;

// In your parser:
if (current_token->type == TOKEN_HEREDOC) // Assuming lexer identifies <<
{
    t_redir *redir = malloc(sizeof(t_redir));
    redir->type = REDIR_HEREDOC;
    // The next token is the delimiter
    current_token = get_next_token();
    redir->file = ft_strdup(current_token->value); // Store delimiter
    // Handle quotes in delimiter: if quoted, variables won't expand in heredoc
    // You might need a flag in t_redir for 'expand_vars_in_heredoc'
    ft_lstadd_back(&cmd->redirections, ft_lstnew(redir));
}
```

#### 2. Creating a Temporary File

You'll need a unique temporary filename. `mkstemp()` is a safe way to do this.

```c
#include <unistd.h> // For close, unlink
#include <fcntl.h>  // For O_WRONLY, O_CREAT
#include <stdio.h>  // For dprintf, remove
#include <readline/readline.h> // For readline

char    *create_temp_heredoc_file(void)
{
    char    *filename;
    int     fd;

    // Allocate space for a template name, e.g., "/tmp/minishell_heredoc_XXXXXX"
    filename = ft_strdup("/tmp/minishell_heredoc_XXXXXX");
    if (!filename)
    {
        perror("ft_strdup for heredoc filename");
        return (NULL);
    }
    // mkstemp replaces XXXXXX with a unique string and creates the file with 0600 permissions
    fd = mkstemp(filename);
    if (fd == -1)
    {
        perror("mkstemp for heredoc");
        free(filename);
        return (NULL);
    }
    close(fd); // Close the file descriptor, we just need the name for now
    return (filename);
}
```

#### 3. Reading Input and Writing to Temporary File

This part is typically done in a **child process** to avoid blocking the main shell process and to correctly handle signals during heredoc input.

```c
#include <sys/wait.h> // For waitpid
#include <string.h>   // For strcmp
#include <stdlib.h>   // For exit

// Function to handle the heredoc input loop
void    read_heredoc_input(const char *delimiter, int fd_temp_file, int expand_vars)
{
    char    *line;

    while (1)
    {
        line = readline("> "); // Prompt for heredoc input
        if (!line) // EOF (Ctrl-D) during heredoc input
        {
            // Optionally print a warning about unexpected EOF
            dprintf(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s`)
", delimiter);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0) // Delimiter found
        {
            free(line);
            break;
        }
        if (expand_vars)
            line = expand_variables(line); // Implement your variable expansion
        dprintf(fd_temp_file, "%s
", line); // Write line to temp file
        free(line);
    }
    close(fd_temp_file);
    exit(0); // Child process exits after collecting input
}

// Main logic for processing a heredoc before command execution
char    *process_heredoc(const char *delimiter, int expand_vars)
{
    char    *temp_filename;
    pid_t   pid;
    int     status;
    int     fd_temp_file;

    temp_filename = create_temp_heredoc_file();
    if (!temp_filename)
        return (NULL);

    fd_temp_file = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd_temp_file == -1)
    {
        perror("open heredoc temp file");
        free(temp_filename);
        return (NULL);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork heredoc");
        close(fd_temp_file);
        unlink(temp_filename); // Clean up temp file
        free(temp_filename);
        return (NULL);
    }
    else if (pid == 0) // Child process: collects heredoc input
    {
        // Set specific signal handlers for the heredoc child to avoid
        // affecting the parent shell's readline, e.g., ignore SIGINT.
        // Or terminate cleanly. A simple exit(1) on SIGINT might be desired.
        // setup_signal_handlers_heredoc_child(); // Custom signal setup for heredoc child
        read_heredoc_input(delimiter, fd_temp_file, expand_vars);
    }
    else // Parent process: waits for child to finish
    {
        close(fd_temp_file); // Parent closes its copy of the fd
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status))
        {
            // Child was terminated by a signal (e.g., Ctrl-C during heredoc input)
            // Handle this gracefully, potentially returning NULL or an error.
            unlink(temp_filename);
            free(temp_filename);
            return (NULL);
        }
    }
    return (temp_filename); // Return the path to the temp file
}
```

#### 4. Integrating with Execution and Cleanup

Before executing any command (including built-ins), you should check for heredocs. If one exists, process it to get the temporary filename. Then, during the I/O redirection setup for the command, use this temporary file as `stdin`.

```c
// In your executor function, before execve or builtin execution:
// Iterate through command->redirections
t_list *current_redir = cmd->redirections;
char *heredoc_file = NULL;

while (current_redir)
{
    t_redir *redir = (t_redir *)current_redir->content;
    if (redir->type == REDIR_HEREDOC)
    {
        // If multiple heredocs, only the last one takes effect.
        // Free previous heredoc_file if already set
        if (heredoc_file)
        {
            unlink(heredoc_file); // Delete previous temp file
            free(heredoc_file);
        }
        // Assume expand_vars is determined by quoting of delimiter
        int expand_vars = !is_delimiter_quoted(redir->file); // Implement this check
        heredoc_file = process_heredoc(redir->file, expand_vars);
        if (!heredoc_file)
        {
            // Handle error, e.g., signal during heredoc input
            return (1); // Error
        }
    }
    current_redir = current_redir->next;
}

// Later, during redirection setup for the command:
int     in_fd = STDIN_FILENO;
if (heredoc_file)
{
    in_fd = open(heredoc_file, O_RDONLY);
    if (in_fd == -1)
    {
        perror("open heredoc_file for command");
        unlink(heredoc_file);
        free(heredoc_file);
        return (1);
    }
    // Now, if this is the final command in a pipe or directly executed:
    // dup2(in_fd, STDIN_FILENO);
    // close(in_fd);
    // Be careful with dup2 in parent vs child, and when to close fds.
}
// ...
// After the command (or entire pipeline) has finished executing:
if (heredoc_file)
{
    unlink(heredoc_file); // Delete the temporary file
    free(heredoc_file);
}
```

### Key Considerations for Heredoc

*   **Signal Handling during Heredoc Input:** When `readline` is prompting for heredoc input, `SIGINT` (Ctrl-C) should terminate the heredoc input and potentially cancel the command, but *not* terminate the main shell. This requires a specific signal handler for the child process reading heredoc input.
*   **Multiple Heredocs:** If a command has multiple heredocs (e.g., `cmd << ONE << TWO`), only the content of the *last* one is used. The previous ones are processed but their content is discarded.
*   **Variable Expansion:** As mentioned, if the delimiter is quoted (e.g., `cmd << 'EOF'`), variable expansion (`$VAR`) inside the heredoc content should *not* occur. If the delimiter is unquoted (`cmd << EOF`), then variable expansion *should* occur. This needs careful handling during the `read_heredoc_input` phase.
*   **Error Handling:** What happens if `Ctrl-D` is pressed before the delimiter? The shell usually issues a warning and then proceeds as if the delimiter was found at EOF.
*   **Temporary File Permissions:** Ensure the temporary file is created with secure permissions (e.g., `0600`) and is deleted promptly after use.
*   **Resource Management:** Remember to `free` all allocated memory (filenames, lines) and `close` all file descriptors.

By carefully implementing these steps, you'll add robust signal handling and powerful heredoc functionality to your Minishell.
