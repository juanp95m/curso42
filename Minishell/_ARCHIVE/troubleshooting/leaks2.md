# Memory Leak Analysis - Valgrind Output

```bash
==4088088== Memcheck, a memory error detector
==4088088== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==4088088== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==4088088== Command: ./minishell
==4088088==
Minishell$> echo hola || echo adios
hola
Minishell$> exit
exit
==4088088==
==4088088== FILE DESCRIPTORS: 9 open (3 std) at exit.
==4088088== Open file descriptor 4: /dev/pts/0
==4088088==    at 0x49E096B: dup (syscall-template.S:120)
==4088088==    by 0x10CEA7: exec_builtin_parent (in /home/../Minishell/minishell)
==4088088==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==4088088==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==4088088==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== Open file descriptor 3: /dev/pts/0
==4088088==    at 0x49E096B: dup (syscall-template.S:120)
==4088088==    by 0x10CE9A: exec_builtin_parent (in /home/../Minishell/minishell)
==4088088==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==4088088==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==4088088==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== Open AF_UNIX socket 114: <unknown>
==4088088==    <inherited from parent>
==4088088==
==4088088== Open file descriptor 89: /dmabuf:
==4088088==    <inherited from parent>
==4088088==
==4088088== Open file descriptor 81: /dmabuf:
==4088088==    <inherited from parent>
==4088088==
==4088088== Open AF_UNIX socket 12: <unknown>
==4088088==    <inherited from parent>
==4088088==
==4088088==
==4088088== HEAP SUMMARY:
==4088088==     in use at exit: 241,212 bytes in 241 blocks
==4088088==   total heap usage: 1,070 allocs, 829 frees, 296,584 bytes allocated
==4088088==
==4088088== 5 bytes in 1 blocks are still reachable in loss record 2 of 81
==4088088==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4088088==    by 0x10BEE7: remove_quotes (in /home/../Minishell/minishell)
==4088088==    by 0x10BF3B: remove_quotes_from_tokens (in /home/../Minishell/minishell)
==4088088==    by 0x10D9AE: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== 5 bytes in 1 blocks are still reachable in loss record 3 of 81
==4088088==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4088088==    by 0x10F408: ft_strdup (in /home/../Minishell/minishell)
==4088088==    by 0x10B08A: add_arg (in /home/../Minishell/minishell)
==4088088==    by 0x10B58F: handle_cmd_token (in /home/../Minishell/minishell)
==4088088==    by 0x10B6F6: parse_simple_cmd (in /home/../Minishell/minishell)
==4088088==    by 0x10B759: parse_pipe (in /home/../Minishell/minishell)
==4088088==    by 0x10B7F0: parse_expression (in /home/../Minishell/minishell)
==4088088==    by 0x10B8D0: parser (in /home/../Minishell/minishell)
==4088088==    by 0x10D9BE: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== 32 bytes in 1 blocks are still reachable in loss record 17 of 81
==4088088==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4088088==    by 0x10AF7C: create_ast_node (in /home/../Minishell/minishell)
==4088088==    by 0x10B69D: parse_simple_cmd (in /home/../Minishell/minishell)
==4088088==    by 0x10B759: parse_pipe (in /home/../Minishell/minishell)
==4088088==    by 0x10B7F0: parse_expression (in /home/../Minishell/minishell)
==4088088==    by 0x10B8D0: parser (in /home/../Minishell/minishell)
==4088088==    by 0x10D9BE: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== 40 bytes in 1 blocks are still reachable in loss record 18 of 81
==4088088==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4088088==    by 0x10A546: create_new_token (in /home/../Minishell/minishell)
==4088088==    by 0x10A88B: handle_word (in /home/../Minishell/minishell)
==4088088==    by 0x10AAB8: lexer (in /home/../Minishell/minishell)
==4088088==    by 0x10D957: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== 64 bytes in 1 blocks are still reachable in loss record 24 of 81
==4088088==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4088088==    by 0x10AED8: create_cmd_node (in /home/../Minishell/minishell)
==4088088==    by 0x10B6B7: parse_simple_cmd (in /home/../Minishell/minishell)
==4088088==    by 0x10B759: parse_pipe (in /home/../Minishell/minishell)
==4088088==    by 0x10B7F0: parse_expression (in /home/../Minishell/minishell)
==4088088==    by 0x10B8D0: parser (in /home/../Minishell/minishell)
==4088088==    by 0x10D9BE: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== 8,192 bytes in 1 blocks are still reachable in loss record 68 of 81
==4088088==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4088088==    by 0x10ECE4: ft_calloc (in /home/../Minishell/minishell)
==4088088==    by 0x10AEF9: create_cmd_node (in /home/../Minishell/minishell)
==4088088==    by 0x10B6B7: parse_simple_cmd (in /home/../Minishell/minishell)
==4088088==    by 0x10B759: parse_pipe (in /home/../Minishell/minishell)
==4088088==    by 0x10B7F0: parse_expression (in /home/../Minishell/minishell)
==4088088==    by 0x10B8D0: parser (in /home/../Minishell/minishell)
==4088088==    by 0x10D9BE: process_input (in /home/../Minishell/minishell)
==4088088==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==4088088==
==4088088== LEAK SUMMARY:
==4088088==    definitely lost: 0 bytes in 0 blocks
==4088088==    indirectly lost: 0 bytes in 0 blocks
==4088088==      possibly lost: 0 bytes in 0 blocks
==4088088==    still reachable: 8,338 bytes in 6 blocks
==4088088==         suppressed: 232,874 bytes in 235 blocks
==4088088==
==4088088== For lists of detected and suppressed errors, rerun with: -s
==4088088== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Based on the provided `valgrind_output.txt`, the following leaks were observed when running the command sequence `echo hola || echo adios` followed by `exit`.

## Overview

Valgrind reports **241,212 bytes in 241 blocks** still in use at exit. These are categorized as "still reachable", meaning the pointers to this memory still exist, but the program terminated before freeing them.

The stack traces consistently point to memory allocated during the parsing and execution phase of the *current command* (`exit`).

## Detailed Leak Analysis

### 1. Token Creation Leaks

* **Location:** `create_new_token` called by `handle_word` -> `lexer`.

* **Size:** 40 bytes per token.

* **Evidence:**
  
  ```
  40 bytes in 1 blocks are still reachable in loss record 18 of 81
     at 0x4846828: malloc
     by 0x10A546: create_new_token
     by 0x10A88B: handle_word
     ...
  ```

* **Cause:** The tokens for the command `exit` are created and stored in a list. When `builtin_exit` runs, it calls `exit()`, terminating the process immediately. The call to `free_tokens(tokens)` at the end of `process_input` is never reached.

### 2. AST Node Creation Leaks

* **Location:** `create_ast_node` called by `parse_simple_cmd`.

* **Size:** 32 bytes per node.

* **Evidence:**
  
  ```
  32 bytes in 1 blocks are still reachable in loss record 17 of 81
     at 0x4846828: malloc
     by 0x10AF7C: create_ast_node
     ...
  ```

* **Cause:** Similar to tokens, the Abstract Syntax Tree (AST) nodes for `exit` are allocated but `free_ast(nodes)` is never called because the program exits prematurely inside the execution phase.

### 3. Command Node Leaks

* **Location:** `create_cmd_node` called by `parse_simple_cmd`.

* **Size:** 64 bytes (struct) + 8,192 bytes (likely for command buffer or arguments via `ft_calloc`).

* **Evidence:**
  
  ```
  64 bytes in 1 blocks are still reachable in loss record 24 of 81
     at 0x4846828: malloc
     by 0x10AED8: create_cmd_node
     ...
  
  8,192 bytes in 1 blocks are still reachable in loss record 68 of 81
     at 0x4846828: malloc
     by 0x10ECE4: ft_calloc
     by 0x10AEF9: create_cmd_node
  ```

* **Cause:** The `t_command` structure and its internal buffers (likely `args` array or similar) are attached to the AST. They leak for the same reason: abrupt termination prevents `free_ast` from running.

### 4. String Duplication Leaks

* **Location:** `ft_strdup` inside `add_arg` and `remove_quotes`.

* **Size:** Small blocks (5 bytes etc).

* **Evidence:**
  
  ```
  5 bytes in 1 blocks are still reachable ... create_new_token/remove_quotes
  ```

* **Cause:** Strings duplicated for command arguments or token values.

## Proposed Fix

The issue is that `builtin_exit` terminates the parent process directly using the system call `exit()`, bypassing the cleanup logic located at the end of `process_input`.

### Structural Change Required

1. **Modify `t_shell` struct:**
   Add a flag to indicate that the shell should exit.
   
   ```c
   typedef struct s_shell {
       // ... existing fields
       int exit_requested; // New flag: 1 if exit command was run
   } t_shell;
   ```

2. **Update `builtin_exit` (`src/builtins/builtin_exit.c`):**
   Instead of calling `exit()`, set the flag.
   
   ```c
   int builtin_exit(char **args, t_shell *shell)
   {
       // ... (argument processing logic)
   
       // OLD: exit(exit_code);
       // NEW:
       shell->exit_requested = 1; 
       shell->last_exit_code = exit_code; // Store the exit code
       return (exit_code);
   }
   ```

3. **Update `process_input` (`src/main.c`):**
   Ensure cleanup happens *before* reacting to the exit flag.
   
   ```c
   static void process_input(char *input, t_shell *shell)
   {
       // ... (parsing and execution)
   
       if (nodes)
       {
           assign_fullpath_recursive(nodes, shell);
           shell->last_exit_code = traverse_tree(nodes, shell);
       }
   
       // CLEANUP (This will now run because we returned from traverse_tree)
       free_tokens(tokens); 
       free_ast(nodes);
   }
   ```

4. **Update `main` loop:**
   Check the flag to break the loop.
   
   ```c
   while (1)
   {
       // ... get input ...
       process_input(input, &shell);
       free(input);
   
       // CHECK EXIT FLAG
       if (shell->exit_requested)
           break; 
   }
   // Perform final shell cleanup (free env, etc.)
   free_shell(&shell);
   return (shell->last_exit_code);
   ```

This approach ensures that even when `exit` is called, the control flow returns to `main`, allowing `process_input` to free the AST and tokens of the `exit` command itself before the program terminates.
