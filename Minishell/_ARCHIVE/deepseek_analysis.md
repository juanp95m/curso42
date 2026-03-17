After reviewing your minishell code, I’ve identified several areas that could lead to memory leaks, norm violations, or behavior not matching the project requirements. Below are detailed suggestions to fix these issues.

---

## 1. Error Handling in the Lexer
- **Issue**: `handle_word` and `handle_operator` can return `-1` on allocation failure, but `lexer` does not check this. If they fail, `lexer` continues with a negative index, causing undefined behavior.
- **Fix**: Modify `lexer` to check the return value of `handle_word` and `handle_operator`. If either returns `-1`, free any tokens already built and return `NULL`. Also, add a check for unclosed quotes in `skip_quotes` (return an error if no closing quote is found) and propagate that error.

**Example**:
```c
int ret;
while (line[i])
{
    if (is_space(line[i]))
        i++;
    else if (is_special_char(line[i]))
    {
        ret = handle_operator(line, i, &head);
        if (ret < 0)
            return (free_tokens(head), NULL);
        i = ret;
    }
    else
    {
        ret = handle_word(line, i, &head);
        if (ret < 0)
            return (free_tokens(head), NULL);
        i = ret;
    }
}
```

---

## 2. `dup_env_array` – Dangerous Error Handling
- **Issue**: After `malloc`, `newenv` contains uninitialized pointers. If `ft_strdup` fails, `free_array(newenv)` is called, which will attempt to free garbage pointers until it hits a NULL, potentially crashing.
- **Fix**: Set all pointers to `NULL` immediately after allocation, then fill. This way `free_array` works safely.

```c
newenv = malloc(sizeof(char *) * (count + 1));
if (!newenv)
    return (NULL);
i = 0;
while (i <= count)   // set all to NULL
    newenv[i++] = NULL;
i = 0;
while (envp[i])
{
    newenv[i] = ft_strdup(envp[i]);
    if (!newenv[i])
    {
        free_array(newenv);
        return (NULL);
    }
    i++;
}
newenv[i] = NULL;
```

---

## 3. Parser – Handle `ft_strdup` Failures in `add_arg`
- **Issue**: `add_arg` uses `ft_strdup` without checking for failure. If it returns `NULL`, the argument is lost and later access may crash.
- **Fix**: Make `add_arg` return an `int` (1 on success, 0 on failure). Propagate errors up to `parse_simple_cmd`.

```c
int add_arg(t_command *cmd, t_token *token)
{
    int i = 0;
    while (cmd->args[i])
        i++;
    if (i < 1023)
    {
        cmd->args[i] = ft_strdup(token->value);
        if (!cmd->args[i])
            return (0);
        cmd->args[i + 1] = NULL;
        if (i == 0)
            cmd->builtin_type = (token->type > BUILTIN) ? token->type : EXTERNAL;
    }
    return (1);
}
```

Then in `handle_cmd_token`:
```c
if ((*tokens)->type == WORD || (*tokens)->type >= BUILTIN)
{
    if (!add_arg(cmd, *tokens))
        return (0);
    *tokens = (*tokens)->next;
}
```

---

## 4. Redirection Parsing – Double Free
- **Issue**: `parse_infile`, `parse_outfile`, and `parse_heredoc` call `free_single_cmd(command)` on failure. Later, the caller (`parse_simple_cmd`) also frees the command, leading to a double free.
- **Fix**: Remove the `free_single_cmd` calls. Just return `FALSE` and let the caller clean up.

---

## 5. Token Splitter – Allocation Failures in `handle_split_token`
- **Issue**: The function frees `curr->value` before creating new tokens. If a later `ft_strdup` or `create_new_token` fails, the original value is lost and the list is left in an inconsistent state.
- **Fix**: First duplicate all new strings and create tokens in a temporary list. If any allocation fails, free the temporary list and leave the original token unchanged. Only after all succeed, insert the new tokens and free the original.

**Simpler approach**: If any allocation fails, do not split the token at all. Keep the original value.

```c
static int handle_split_token(t_token *curr, char **words)
{
    t_token *new_list = NULL;
    t_token *last = NULL;
    int i = 0;

    // Create all new tokens first
    while (words[i])
    {
        t_token *new = create_new_token(ft_strdup(words[i]), WORD);
        if (!new)
        {
            free_tokens(new_list);
            return (0);
        }
        new->quote = NONE;
        new->expandable = FALSE;
        if (!new_list)
            new_list = new;
        else
            last->next = new;
        last = new;
        i++;
    }
    // All succeeded, now replace the current token
    free(curr->value);
    curr->value = ft_strdup(words[0]); // already have it, but safe to dup again
    // Insert the rest after curr
    if (new_list->next)
    {
        last->next = curr->next;
        if (curr->next)
            curr->next->prev = last;
        curr->next = new_list->next;
        new_list->next->prev = curr;
    }
    free_tokens(new_list); // new_list itself is not needed
    return (1);
}
```

---

## 6. Expander – Handle `ft_strjoin_free` Failures
- **Issue**: `process_expansion` may return `NULL` if any allocation fails. `expand_dollars` then frees the old value and sets it to `NULL`, causing later crashes.
- **Fix**: Check the result of `process_expansion`. If it returns `NULL`, keep the old value (or set an empty string) and report an error (e.g., set a flag to abort processing).

```c
if (tmp->expandable)
{
    expanded_str = process_expansion(tmp->value, shell);
    if (!expanded_str)
    {
        // Handle error – maybe keep original value or set to empty?
        // For simplicity, keep original and continue.
        continue;
    }
    free(tmp->value);
    tmp->value = expanded_str;
    tmp->expandable = FALSE;
}
```

---

## 7. Quote Removal – Avoid NULL Assignment
- **Issue**: `remove_quotes` may return `NULL`. The code then frees the old value and sets it to `NULL`, breaking later steps.
- **Fix**: Only replace if the new string is allocated.

```c
new_value = remove_quotes(tmp->value);
if (new_value)
{
    free(tmp->value);
    tmp->value = new_value;
}
// else keep old value (or handle error)
```

---

## 8. Parser – Error Propagation in `parse_pipe` and `parse_expression`
- **Issue**: If `parse_simple_cmd` returns `NULL` when building the right side of a pipe or logical operator, the node is left with a `NULL` child, and the loop may continue, leading to an invalid AST.
- **Fix**: After assigning `node->right`, check if it is `NULL`. If so, free the node and the left child, and return `NULL`.

```c
node->right = parse_simple_cmd(tokens);
if (!node->right)
{
    free_ast(node->left);
    free(node);
    return (NULL);
}
```

---

## 9. Lexer – Check for Unclosed Quotes
- **Issue**: The subject says “Not interpret unclosed quotes”. Your lexer currently treats them as quoted, removing the opening quote. This may be acceptable, but typical minishell implementations treat them as syntax errors.
- **Suggestion**: Add a check in `skip_quotes` that returns an error if the closing quote is not found. Then in `lexer`, return `NULL` and free tokens. This aligns with common expectations.

---

## 10. Norm Compliance – Line Length and Function Size
- **Issue**: Some lines may exceed 80 columns (e.g., long error messages, color codes in debug functions). Also, a few functions might be close to 25 lines.
- **Check**: Use `norminette` to identify violations. Common fixes:
  - Break long strings across multiple lines.
  - Split functions that are too long into smaller helpers (e.g., `process_heredoc` could be split).
  - Ensure no more than 5 variables per function (most are fine, but double-check).

---

## 11. Header Guards
- **Issue**: `structs.h` (from `Minishell_flath.md`) lacks header guards.
- **Fix**: Add:
```c
#ifndef STRUCTS_H
# define STRUCTS_H
... // content
#endif
```

---

## 12. Global Variable Usage
- **Issue**: The subject allows **at most one global variable** to store the signal number. You have `g_signal_status`, which is correct. Ensure it is never used to store pointers or complex data.

---

## 13. Memory Leaks in Error Paths
- **Issue**: Throughout the code, many allocation failures are not handled consistently. For example, in `create_envp_list`, if `ft_env_new` fails, the key and value are freed, but no further action is taken. This is acceptable, but the shell should probably exit or report an error. Since minishell is expected to be robust, you may want to abort the current command and free all resources.
- **Suggestion**: In `process_input`, after each step (lexer, expander, parser), check for `NULL` returns and free partial structures. For instance:
```c
tokens = lexer(input);
if (!tokens)
    return;
tokens = add_expansion_info(tokens);
tokens = expand_dollars(shell, tokens);
if (!tokens) // expand_dollars could return NULL on critical failure
    return;
...
```

---

## 14. Pipe Fork Failure Handling
- **Issue**: In `exec_node_pipe`, if either `fork` in `open_fork` fails, the function does not handle it properly. The parent may wait on invalid PIDs.
- **Fix**: Check the return of `open_fork`. If it returns `-1`, close the pipe, wait for any successfully created child, and return an error status.

---

## 15. `find_command` – Memory Leak in Case of `access` Failure
- **Issue**: When `cmd` contains a `/` and `access` fails, the function returns `NULL` without freeing anything. That's fine, but note that `cmd` itself is not allocated. No leak.

---

## Summary of Critical Fixes
1. **Lexer error handling** – prevent crashes on allocation failure.
2. **`dup_env_array`** – fix unsafe `free_array` call.
3. **Parser** – handle `ft_strdup` failures and avoid double frees in redirection parsing.
4. **Token splitter** – make splitting atomic to avoid losing data.
5. **Expander & quote removal** – avoid setting token values to `NULL`.
6. **Header guards** – add to `structs.h`.
7. **Norm** – run `norminette` and fix line lengths/function sizes.

Implementing these changes will make your minishell more robust, memory-leak free, and compliant with the 42 Norm and project requirements.

---


# Revision heredoc tmp file

The Valgrind output shows two issues when pressing Ctrl+C during a heredoc:

1. **File descriptor leak**: `.heredoc_tmp_0` remains open at exit (fd 3), even though the file is unlinked.
2. **Memory leaks**: Many “still reachable” blocks from environment variables, tokens, AST nodes, etc., indicating incomplete cleanup on exit.

The file descriptor leak occurs because the parent process may open the heredoc file for reading, but an error or signal interrupts the command before the fd is closed. The “still reachable” memory suggests the shell exits without calling all necessary free functions.

Below are fixes to ensure proper cleanup and norm compliance.

---

## 1. Heredoc: Ensure File Descriptor is Closed on All Paths

The current `process_heredoc` (fork version) opens the file in the child, and the parent opens it again for reading if the child succeeds. However, if the command later fails (e.g., redirection error) or the user presses Ctrl+C, the parent’s fd may not be closed.

**Solution**:  
- After opening the heredoc file for reading in the parent, immediately unlink it (so it disappears after the last close).  
- Store the fd in the command structure temporarily, and close it in a cleanup function if the command fails.  
- Temporarily ignore `SIGINT` in the parent while waiting for the child to avoid readline interference.

### Revised `process_heredoc`

```c
int	process_heredoc(char *delimiter, int heredoc_num)
{
	char				*filename;
	pid_t				pid;
	int					status;
	int					tmp_fd;
	struct sigaction	old_sa;
	struct sigaction	sa;

	// Temporarily ignore SIGINT in parent
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, &old_sa);

	filename = generate_heredoc_name(heredoc_num);
	if (!filename)
	{
		sigaction(SIGINT, &old_sa, NULL);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		free(filename);
		sigaction(SIGINT, &old_sa, NULL);
		return (-1);
	}
	if (pid == 0)
	{
		setup_heredoc_signals();
		heredoc_child_process(filename, delimiter);
	}
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &old_sa, NULL); // Restore parent handler

	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		unlink(filename);
		free(filename);
		g_signal_status = 130;
		return (-1);
	}
	tmp_fd = open(filename, O_RDONLY);
	unlink(filename); // Delete immediately; file stays open until closed
	free(filename);
	return (tmp_fd);
}
```

### Close the fd in `handle_input_redirections` on Error

In `handle_input_redirections`, if opening the infile fails, the heredoc fd is already closed. However, if the heredoc fd is obtained and then an error occurs later (e.g., in output redirection), the fd is already duplicated and closed. The only risk is if an error occurs **before** the fd is duplicated. To be safe, add a cleanup at the end of `setup_redirections` that closes the heredoc fd if it was opened but not used.

Better: Pass the fd back to the caller and close it in the command cleanup.

But the simplest fix is to ensure that `handle_input_redirections` always closes the fd after use, even on error. It already does that.

The remaining risk is if `get_heredoc_fd` returns a valid fd, but the command is never executed (e.g., syntax error before execution). In that case, the fd would leak. To prevent that, we should store the fd in the command structure and close it when the command is freed.

---

## 2. Store Heredoc FD in Command Structure and Close on Free

Add an `int heredoc_fd` field to `t_command` (initialized to -1). In `get_heredoc_fd`, assign it. In `handle_input_redirections`, after using the fd, set it to -1. In `free_single_cmd`, if `heredoc_fd != -1`, close it.

**In `structs.h`:**
```c
typedef struct s_command
{
    // ... existing fields ...
    int heredoc_fd; // -1 if not open
} t_command;
```

**In `create_cmd_node`:**
```c
new_cmd->heredoc_fd = -1;
```

**In `get_heredoc_fd`:**
```c
static int get_heredoc_fd(t_command *cmd, t_shell *shell)
{
    if (!cmd->heredoc_delimiter)
        return (-1);
    cmd->heredoc_fd = process_heredoc(cmd->heredoc_delimiter, shell->heredoc_count);
    return (cmd->heredoc_fd);
}
```

**In `handle_input_redirections`:**
```c
if (cmd->heredoc_fd != -1)
{
    dup2(cmd->heredoc_fd, STDIN_FILENO);
    close(cmd->heredoc_fd);
    cmd->heredoc_fd = -1;
}
```

**In `free_single_cmd`:**
```c
if (cmd->heredoc_fd != -1)
    close(cmd->heredoc_fd);
```

This guarantees the fd is closed when the command is freed, even if the command is never executed.

---

## 3. Fix “Still Reachable” Memory Leaks

The Valgrind output shows many allocations from environment variables, tokens, AST nodes, etc., that are not freed on exit. The main issue is that `free_shell` is called, but some allocations may be missed because:

- `shell->env_vars` is freed, but the environment list (`env_list`) may not be fully freed if some nodes were added after `create_envp_list`.
- Tokens and AST from the last command are freed in `process_input`, but if the shell exits due to a signal, they might not be freed.

**Ensure all dynamic memory is freed before exit:**

- In `main`, after `run_interactive`, call `free_shell`. That’s already done.
- In `run_interactive`, if `get_user_input` returns NULL (EOF), break and let `main` free.
- In `process_input`, tokens and AST are freed at the end. That’s correct.
- However, if an error occurs during lexing/parsing (e.g., unclosed quotes), the function should return early and free any partially built structures.

**Check all early return paths in `process_input`:**

```c
void process_input(char *input, t_shell *shell)
{
    t_token *tokens;
    t_node  *nodes;

    if (isatty(STDIN_FILENO))
        add_history(input);
    tokens = lexer(input);
    if (!tokens) // lexer error (e.g., unclosed quote)
        return;
    tokens = add_expansion_info(tokens);
    tokens = expand_dollars(shell, tokens);
    if (!tokens) // expansion error (allocation failure)
    {
        free_tokens(tokens);
        return;
    }
    tokens = split_expanded_tokens(tokens);
    tokens = expand_wildcards(tokens);
    tokens = remove_quotes_from_tokens(tokens);
    nodes = parser(tokens);
    if (!nodes) // parse error
    {
        free_tokens(tokens);
        return;
    }
    shell->current_tokens = tokens;
    shell->current_ast = nodes;
    assign_fullpath_recursive(nodes, shell);
    shell->last_exit_code = traverse_tree(nodes, shell);
    shell->current_tokens = NULL;
    shell->current_ast = NULL;
    shell->heredoc_count = 0;
    free_tokens(tokens);
    free_ast(nodes);
}
```

Make sure `lexer` returns `NULL` on error (e.g., unclosed quotes or allocation failure) and frees any partial token list internally.

---

## 4. Signal Handling in Parent During Heredoc

The earlier fix already temporarily ignores `SIGINT` in the parent. This prevents the parent’s interactive signal handler from running while waiting for the child, which could call readline functions and corrupt state.

**Add the signal ignore/restore in `process_heredoc` as shown above.**

---

## 5. Norm Compliance Checks

- **Function length**: Some functions (e.g., `process_heredoc`, `handle_input_redirections`) may exceed 25 lines. Split them if needed.
- **Line length**: Ensure no line exceeds 80 columns. Break long strings and comments.
- **Variable declarations**: Declare all variables at the top of the function, one per line.
- **Header guards**: Add them to `structs.h` and any other headers missing them.
- **Global variable**: You already have `g_signal_status` – that’s the allowed single global.

Run `norminette` and fix any errors it reports.

---

## 6. Additional Improvements

- In `dup_env_array`, after allocating `newenv`, set all pointers to `NULL` immediately to make `free_array` safe on failure.
- In `add_arg`, check the return of `ft_strdup` and propagate failure.
- In `parse_redirections`, avoid calling `free_single_cmd` on error; let the caller clean up.

By implementing these changes, your minishell will properly clean up resources on Ctrl+C and exit without leaks.