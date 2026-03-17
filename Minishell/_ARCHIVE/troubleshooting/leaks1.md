# Memory Leak Analysis

## Summary of Findings (Valgrind Analysis)

The provided `valgrind_output.txt` shows that when the shell exits (via the `exit` command), there are still reachable memory blocks. These blocks correspond to the Token List and the Abstract Syntax Tree (AST) of the **currently executing command**.

The trace indicates that the memory allocated by:
*   `create_new_token` (40 bytes)
*   `create_ast_node` (32 bytes)
*   `create_cmd_node` (64 bytes + 8,192 bytes for `malloc` inside `create_cmd_node` -> `ft_calloc`)
*   `ft_strdup` inside `add_arg` (5 bytes)
*   `remove_quotes` (5 bytes)

is not freed.

**Root Cause:**
This happens because `builtin_exit` calls `exit()` directly, terminating the process immediately. The `process_input` function, which is responsible for calling `free_tokens` and `free_ast` *after* execution completes, never gets to reach those cleanup lines because the process dies inside `traverse_tree`.

## src/builtins/builtin_exit.c (To Be Fixed)

### Identified Leak: Global Cleanup on Exit

*   **Description**: When `exit` is called in an interactive session (parent process), it terminates the program using `exit(code)`. This prevents the stack from unwinding back to `process_input`, skipping the `free_tokens(tokens)` and `free_ast(nodes)` calls.
*   **Proposed Fix**:
    1.  Add a flag `int exit_requested;` to the `t_shell` structure.
    2.  Modify `builtin_exit` to set this flag and return the exit code instead of calling `exit()` (when running in the main parent process).
    3.  Modify `process_input` (or `main`) to check this flag after `process_input` returns, and if set, break the main loop to perform a clean exit, or simply let `process_input` finish its cleanup and then have `main` check the flag.

## src/main.c (Potential Issue)

### Potential Leaks:

*   **`run_script`**:
    *   **Description**: The `run_script` function iterates through lines from a file using `get_next_line`. `get_next_line` allocates memory for each line. If `process_input` does not free the passed line (which is standard behavior, as it treats input as read-only or copies it), there is a leak for every line of the script.
    *   **Status**: Needs verification. If `process_input` does not `free(input)`, `run_script` must do it. **Update:** The user has been advised to add `free(line)` in the loop.

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
  * **Description**: The `char **` array returned by `from_envlist_2_envp` is passed to `execve`. If `execve` fails, this array, which was dynamically allocated, is not freed before the child process exits. This has been corrected by adding `free_array(envp_new);`.
  * **Status**: Fixed.

## src/main.c (fixed)

### Potential Leaks:

* **`create_basic_env_vars`**:
  
  * **Description**: The `char *` returned by `getcwd(NULL, 0)` is used to set the "PWD" environment variable but is not freed after its value has been `ft_strdup`'d into the environment list. This has been corrected by storing the `getcwd` result in `cwd_val` and calling `free(cwd_val);`.
  * **Status**: Fixed.
