# Memory Error Analysis - Valgrind Output 2

```bash
make[1]: Leaving directory '/home/../Minishell/lib/libft'
Build complete: minishell
==946703== Memcheck, a memory error detector
==946703== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==946703== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==946703== Command: ./minishell
==946703==
Minishell$> echo hola || echo adios
hola
==946703== Conditional jump or move depends on uninitialised value(s)
==946703==    at 0x10DBEB: main (in /home/../Minishell/minishell)
==946703==  Uninitialised value was created by a stack allocation
==946703==    at 0x10DB03: main (in /home/../Minishell/minishell)
==946703==
Minishell$> exit
exit
==946703== Invalid read of size 8
==946703==    at 0x10C059: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b149e0 is 16 bytes inside a block of size 24 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C294: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C3C4: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid read of size 8
==946703==    at 0x10C065: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b149d0 is 0 bytes inside a block of size 24 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C294: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C3C4: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid read of size 8
==946703==    at 0x10C071: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b149d0 is 0 bytes inside a block of size 24 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C294: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C3C4: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid free() / delete / delete[] / realloc()
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C07B: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b14a30 is 0 bytes inside a block of size 9 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C26B: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10F420: ft_strdup (in /home/../Minishell/minishell)
==946703==    by 0x10C3E5: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid read of size 8
==946703==    at 0x10C080: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b149d8 is 8 bytes inside a block of size 24 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C294: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C3C4: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid read of size 8
==946703==    at 0x10C08D: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b149d8 is 8 bytes inside a block of size 24 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C294: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C3C4: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid free() / delete / delete[] / realloc()
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C098: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b14a80 is 0 bytes inside a block of size 23 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C288: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10F420: ft_strdup (in /home/../Minishell/minishell)
==946703==    by 0x10C3FF: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703== Invalid free() / delete / delete[] / realloc()
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C0A4: free_env_list (in /home/../Minishell/minishell)
==946703==    by 0x10C0E3: free_shell (in /home/../Minishell/minishell)
==946703==    by 0x10DBFE: main (in /home/../Minishell/minishell)
==946703==  Address 0x4b149d0 is 0 bytes inside a block of size 24 free'd
==946703==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C294: free_env_node (in /home/../Minishell/minishell)
==946703==    by 0x10C206: free_resources (in /home/../Minishell/minishell)
==946703==    by 0x10E46D: builtin_exit (in /home/../Minishell/minishell)
==946703==    by 0x10CE64: run_builtin (in /home/../Minishell/minishell)
==946703==    by 0x10CF0D: exec_builtin_parent (in /home/../Minishell/minishell)
==946703==    by 0x10C8BF: exec_node_cmd (in /home/../Minishell/minishell)
==946703==    by 0x10C9C6: traverse_tree (in /home/../Minishell/minishell)
==946703==    by 0x10D9EF: process_input (in /home/../Minishell/minishell)
==946703==    by 0x10DBD9: main (in /home/../Minishell/minishell)
==946703==  Block was alloc'd at
==946703==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==946703==    by 0x10C3C4: ft_env_new (in /home/../Minishell/minishell)
==946703==    by 0x109C67: create_envp_list (in /home/../Minishell/minishell)
==946703==    by 0x109D33: init_shell_state (in /home/../Minishell/minishell)
==946703==    by 0x10DB3B: main (in /home/../Minishell/minishell)
==946703==
==946703==
==946703== FILE DESCRIPTORS: 7 open (3 std) at exit.
==946703== Open AF_UNIX socket 114: <unknown>
==946703==    <inherited from parent>
==946703==
==946703== Open file descriptor 89: /dmabuf:
==946703==    <inherited from parent>
==946703==
==946703== Open file descriptor 81: /dmabuf:
==946703==    <inherited from parent>
==946703==
==946703== Open AF_UNIX socket 12: <unknown>
==946703==    <inherited from parent>
==946703==
==946703==
==946703== HEAP SUMMARY:
==946703==     in use at exit: 232,869 bytes in 234 blocks
==946703==   total heap usage: 1,070 allocs, 1,073 frees, 296,584 bytes allocated
==946703==
==946703== LEAK SUMMARY:
==946703==    definitely lost: 0 bytes in 0 blocks
==946703==    indirectly lost: 0 bytes in 0 blocks
==946703==      possibly lost: 0 bytes in 0 blocks
==946703==    still reachable: 0 bytes in 0 blocks
==946703==         suppressed: 232,869 bytes in 234 blocks
==946703==
==946703== For lists of detected and suppressed errors, rerun with: -s
==946703== ERROR SUMMARY: 633 errors from 9 contexts (suppressed: 0 from 0)
```

Based on the provided `valgrind_output2.txt`, we are now facing a different class of errors compared to the previous leaks. These are **Double Free** and **Invalid Read** errors, which typically occur when the program tries to access or free memory that has already been freed.

## Overview of Errors

Valgrind reports multiple instances of:

1. **Invalid read of size 8**: Reading memory that has been freed.
2. **Invalid free()**: Attempting to free memory that has already been freed.
3. **Conditional jump or move depends on uninitialised value(s)**: Using variables before they are set.

These errors are triggered during the `exit` command execution.

## Detailed Error Analysis

### 1. Double Free in `free_env_list` / `free_shell`

* **Evidence:**
  
  ```
  Invalid read of size 8
     at 0x10C059: free_env_list
     by 0x10C0E3: free_shell
     by 0x10DBFE: main
   Address 0x... is 16 bytes inside a block of size 24 free'd
     at 0x484988F: free
     by 0x10C294: free_env_node
     by 0x10C206: free_resources
     by 0x10E46D: builtin_exit
  ```

* **Cause:**
  The sequence of events seems to be:
  
  1. `builtin_exit` calls `free_resources(shell)`.
  2. `free_resources` likely frees the environment list (`free_env_list` or similar).
  3. `builtin_exit` returns (or exits via the new flag mechanism, or `main` continues).
  4. Control returns to `main`.
  5. `main` calls `free_shell(&shell)`.
  6. `free_shell` tries to free `shell->env_list` *again*.
  
  Since `builtin_exit` already cleaned up the environment (via `free_resources`), `main` crashes when it tries to clean it up a second time.

### 2. Uninitialized Value in `main`

* **Evidence:**
  
  ```
  Conditional jump or move depends on uninitialised value(s)
     at 0x10DBEB: main
   Uninitialised value was created by a stack allocation
     at 0x10DB03: main
  ```

* **Cause:** A variable declared in `main` (likely on the stack) is being used in a conditional check (like `if (something)`) without strict initialization. Given the line numbers, this might be related to `shell` struct initialization or a status flag.

## Proposed Fixes

### Fix 1: Avoid Double Free of Environment

The `builtin_exit` function should **NOT** free the global shell resources if the plan is to return to `main` and let `main` handle the cleanup. Or, if `builtin_exit` frees them, it must set the pointers in `t_shell` to `NULL` so subsequent frees are safe.

**Option A (Recommended): Centralized Cleanup in Main**
Modify `builtin_exit` to **ONLY** set the `exit_requested` flag and return the exit code. Remove `free_resources(shell)` from `builtin_exit`. Let the `main` function (or `process_input`) handle the teardown.

**Code Change in `src/builtins/builtin_exit.c`:**

```c
int builtin_exit(char **args, t_shell *shell)
{
    int exit_code;

    // ... calculate exit_code logic ...

    // DO NOT call free_resources(shell) here if main will do it later!
    // free_resources(shell); <--- REMOVE THIS

    shell->exit_requested = 1; // Signal main to exit
    shell->last_exit_code = exit_code;
    return (exit_code);
}
```

### Fix 2: Initialize Shell Structure Completely

Ensure that when `t_shell shell;` is declared in `main`, it is zero-initialized or fully initialized immediately.

**Code Change in `src/main.c`:**

```c
int main(int ac, char **av, char **envp)
{
    t_shell shell;

    ft_bzero(&shell, sizeof(t_shell)); // Zero out all fields!
    // ... existing init code ...
}
```

If `init_shell_state` (0x109D33) doesn't initialize every single field (like `exit_requested`), `valgrind` will complain when you check that field.

### Summary

1. **Remove `free_resources` from `builtin_exit`**: Let `main` be the only one responsible for the final cleanup (`free_shell`).
2. **Zero-initialize `shell`**: Use `ft_bzero` or `memset` at the start of `main`.
