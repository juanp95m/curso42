# Memory Leak Analysis

## src/parser.c (fixed)

### Potential Leaks:

* **`parse_infile`, `parse_outfile`, `parse_heredoc`**:
  
  * **Description**: The `command->infile`, `command->outfile`, and `command->heredoc_delimiter` fields were originally assigned direct pointers to token values. Now, `ft_strdup` is correctly used to duplicate these values. The corresponding `free` calls have been added to `free_single_cmd` in `src/clean.c`, thus resolving this leak.
  * **Status**: Fixed.

* **`find_command`**:
  
  * **Description**: The `char *` returned by `find_command` (either from `ft_strdup(cmd)` or `search_in_paths`) is dynamically allocated and *must be freed by the caller*. The caller (`assign_fullpath_recursive`) assigns this to `node->cmd->fullpath`. The `free_single_cmd` function in `src/clean.c` now correctly frees `node->cmd->fullpath`, thus resolving this leak.
  * **Status**: Fixed.

## src/clean.c (fixed)

### Potential Leaks:

* **`free_single_cmd`**:
  * **Description**: This function was missing `free` calls for `cmd->infile`, `cmd->outfile`, and `cmd->heredoc_delimiter`. These calls are now correctly implemented.
  * **Status**: Fixed.

## src/free_tools.c (fixed)

### Potential Leaks:

* **`free_commands`**:
  * **Description**: The function's comment indicates it should not free individual argument strings, assuming they are pointers to token values. However, `add_arg` in `src/parser.c` uses `ft_strdup` to duplicate argument strings, meaning `tmp->args` contains pointers to dynamically allocated memory. `free_commands` only `free(tmp->args)`, which frees the array of pointers but *not* the strings themselves, leading to a significant memory leak for all command arguments. This has been corrected by replacing `free(tmp->args);` with `free_array(tmp->args);`.
  * **Status**: Fixed.

## src/executor_utils.c (fixed)

### Potential Leaks:

* **`exec_external_child`**:
  * **Description**: The `char **` array returned by `from_envlist_2_envp` is passed to `execve`. If `execve` fails, this array, which was dynamically allocated, is not freed before the child process exits. This has been corrected by adding `free_array(envp_new);` after `execve` and before `exit(126);`.
  * **Status**: Fixed.

## src/main.c (fixed)

### Potential Leaks:

* **`create_basic_env_vars`**:
  
  * **Description**: The `char *` returned by `getcwd(NULL, 0)` is used to set the "PWD" environment variable but is not freed after its value has been `ft_strdup`'d into the environment list. This has been corrected by storing the `getcwd` result in `cwd_val` and calling `free(cwd_val);` after `set_env_var`.
  * **Status**: Fixed.

* **`process_input` (Indirect via `free_ast`)**:
  
  * **Description**: `process_input` calls `free_ast(nodes)`, which is intended to free the entire Abstract Syntax Tree. This function (after applying the fixes to `free_single_cmd` in `src/clean.c`) should correctly free all allocated memory within the AST.
  * **Status**: Fixed.

## Still Reachable Memory

Valgrind reported `8,338 bytes in 6 blocks` as "still reachable." This typically indicates memory that was allocated but not explicitly freed, though a pointer to it still exists. In long-running applications like a shell, these might accumulate, but they are not considered critical memory leaks like "definitely lost" bytes.

* **5 bytes in `remove_quotes` (from `src/quote_removal.c`)**: Allocated for string manipulation during quote removal.

* **5 bytes in `ft_strdup` (called by `add_arg` in `src/parser.c`)**: A small string duplicated for an argument.

* **32 bytes in `create_ast_node` (from `src/parser.c`)**: Allocation for an Abstract Syntax Tree node.

* **40 bytes in `create_new_token` (from `src/lexer.c`)**: Allocation for a new token during lexing.

* **64 bytes in `create_cmd_node` (from `src/parser.c`)**: Allocation for a command node in the AST.

* **8,192 bytes in `ft_calloc` (called by `create_cmd_node` in `src/parser.c`)**: A larger allocation, likely for the `args` array within a `t_command` node.

### Specific Suggestions for Still Reachable Memory:

1. **Review Parser Error Paths**:
   
   * **Problem**: The "still reachable" status often arises when memory is allocated during parsing, but an error occurs before the full AST or command structure is completed and subsequently freed. Even if `free_ast_node` and `free_tokens` appear correct, they might not be invoked for partially constructed structures.
   
   * **Action**:
     
     * **`create_ast_node` and `create_cmd_node` (in `src/parser.c`)**:
       
       * In `parse_simple_cmd`, if `create_cmd_node()` fails, `node` (allocated by `create_ast_node`) is freed. This is good.
       
       * However, review `parse_simple_cmd`, `parse_pipe`, `parse_expression`, `handle_parenthesis`, and `handle_cmd_token`. Ensure that if any `malloc` or `ft_calloc` fails (returns `NULL`), or if a parsing error prevents a structure from being fully integrated into the AST, any *already allocated* memory related to that partial structure is immediately freed before returning `NULL` up the call stack.
     
     * **`add_arg` (in `src/parser.c`)**: The `ft_strdup` call within `add_arg` contributes to "still reachable" bytes. This suggests that some `t_command` structures, once they have arguments added, might not be fully freed. This could be due to error paths in `handle_cmd_token` or `parse_simple_cmd` that do not lead to `free_single_cmd` being called.
     
     * **`create_new_token` (in `src/lexer.c`) and `remove_quotes` (in `src/quote_removal.c`)**: These functions allocate `t_token` values. While `free_tokens` is intended to free them, ensure that in all scenarios, especially error handling within `lexer` or `remove_quotes_from_tokens`, any created tokens are eventually passed to `free_tokens`.

2. **`ft_calloc` in `create_cmd_node` (8,192 bytes)**:
   
   * **Problem**: This significant allocation is for `command->args`. While `free_array` is called by `free_single_cmd` to free this, its "still reachable" status implies a `t_command` struct containing this array is not consistently freed.
   
   * **Action**: Focus on the entire lifecycle of `t_command` structs. If `t_command` is allocated, it *must* eventually be freed by `free_single_cmd`, which then frees `command->args`. Trace all paths where `create_cmd_node` is called and ensure `free_single_cmd` is reached, particularly in error conditions.

3. **`readline` Library and Global Variables**:
   
   * It's possible that a small portion of the "still reachable" memory is due to the `readline` library's internal allocations that are not released until the program exits. This is generally acceptable for library functions. However, if the allocations are not from `readline`, it points back to un-freed application-specific memory.

## Open File Descriptors

Valgrind reported `9 open (3 std)` file descriptors at exit. While 3 are standard (stdin, stdout, stderr), the remaining 6 are application-specific. These should ideally be closed before program exit to prevent resource leaks, especially in a shell that might execute many commands.

* **File descriptor 4: `/dev/pts/0`** (from `dup` in `exec_builtin_parent` at `0x10CEA7` in `src/executor_utils.c`)

* **File descriptor 3: `/dev/pts/0`** (from `dup` in `exec_builtin_parent` at `0x10CE9A` in `src/executor_utils.c`)

* **AF_UNIX socket 114**: Inherited from parent.

* **File descriptor 89: `/dmabuf:`**: Inherited from parent.

* **File descriptor 81: `/dmabuf:`**: Inherited from parent.

* **AF_UNIX socket 12**: Inherited from parent.

### Specific Suggestions for Open File Descriptors:

1. **File Descriptors 3 and 4 (`/dev/pts/0`) from `exec_builtin_parent` (in `src/executor_utils.c`)**:
   
   * **Problem**: Valgrind reports these as open at exit, despite `exec_builtin_parent` explicitly calling `close(saved_io[0])` and `close(saved_io[1])`. This suggests a subtle issue where these specific file descriptors might be re-opened, or not truly closed in all edge cases.
   
   * **Action**:
     
     * **Deep Dive into `exec_builtin_parent` and `setup_redirections`**:
       
       * Carefully trace the execution flow through `exec_builtin_parent` and `setup_redirections` (`handle_input_redirections`, `handle_output_redirections`, `get_heredoc_fd`).
       
       * Ensure that *every* `open()` or `dup()` call has a corresponding `close()` call, even in error branches (e.g., if `open()` fails, or if `setup_redirections` returns an error).
       
       * Consider using `fcntl(fd, F_SETFD, FD_CLOEXEC)` on any newly opened file descriptors to ensure they are closed on `execve`. Although this is more relevant for child processes, it's a good practice for file descriptor management.
     
     * **Verify `dup` vs. `dup2` usage**: While `dup2` is used for redirection, `dup` is used to save the original STDIN/STDOUT. The original `saved_io` FDs must be closed. The current code *does* close them. Investigate if there's any path where `dup` is called but `close` is not reached.
     
     * **Program Termination**: If the program `exit()`s prematurely due to an error *before* the `close` calls in `exec_builtin_parent`, these FDs would remain open. This is less likely given the test case (`echo hola || echo adios`) which completes successfully.

2. **Inherited File Descriptors (AF_UNIX sockets, `/dmabuf:`)**:
   
   * **Problem**: These file descriptors are inherited from the `minishell`'s parent process and are not explicitly closed.
   
   * **Action**:
     
     * **Proactive Closing in `main`**: In the `main` function (or an early initialization function), iterate through a range of file descriptors (e.g., from `3` up to a reasonable limit like `FD_SETSIZE` or `sysconf(_SC_OPEN_MAX)`) and `close()` any that are not `STDIN_FILENO`, `STDOUT_FILENO`, or `STDERR_FILENO`. This should be done only once at startup.
     
     * **Example Code Snippet for `main.c`**:
       
       ```c
       // In main.c, after init_shell_state(&shell, envp);
       
       // and potentially after create_basic_env_vars(&shell);
       
       int fd_limit = sysconf(_SC_OPEN_MAX); // Get the maximum number of open files
       
       for (int fd = 3; fd < fd_limit; fd++) {
       
           // Check if the fd is valid and not one of the standard ones
       
           // A simple close might suffice, but fcntl(fd, F_GETFD) can check if it's open.
       
           // However, directly calling close() on an invalid fd is safe.
       
           close(fd);
       
       }
       ```
       
       *Note: Be cautious when blindly closing file descriptors. Ensure no critical descriptors are inadvertently closed if they are needed for core shell functionality (e.g., communication with a terminal). However, for inherited non-standard FDs, this is generally a safe and good practice.*
