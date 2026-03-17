# Changes Required to Separate Bonus from Mandatory

The two bonus features are:
- **`&&` and `||`** (logical operators)
- **Wildcards `*`** (globbing)

42 norm requires bonus files to be named `<name>_bonus.c`. The strategy is:
- **Guard with `#if BONUS`** when the change fits inside the existing function
  body without pushing it past 25 lines.
- **Duplicate the file as `_bonus.c`** when the changes would exceed 25 lines
  inside any function, or when the entire file is bonus-only. The Makefile
  then selects which variant to compile.

The enum values `AND`, `OR`, `L_PAREN`, `R_PAREN`, `NODE_AND`, `NODE_OR`
are kept in `structs.h` for **both** builds. They just never get produced in
the mandatory lexer/parser, so they are harmless dead values.

> **Critical norminette rule:** `#if` / `#else` / `#endif` are **only allowed
> at global scope** (`PREPOC_ONLY_GLOBAL`). They can never appear inside a
> function body. The only valid pattern is:
> ```c
> #if BONUS
> return_type	func(args)
> { /* bonus body */ }
> #else
> return_type	func(args)
> { /* mandatory stub */ }
> #endif
> ```
> A blank line must follow each preprocessor directive (`NL_AFTER_PREPROC`).
> Functions inside `#if`/`#else` blocks must still be separated by blank lines.

---

## Summary Table

| # | File | Strategy | Reason |
|---|------|----------|--------|
| 1 | `Makefile` | New `bonus` target | Selects `_bonus.c` files |
| 2 | `src/wildcards.c` → **`wildcards_bonus.c`** | Rename (bonus-only) | Entire file is bonus |
| 3 | `src/wildcards_utils.c` → **`wildcards_utils_bonus.c`** | Rename (bonus-only) | Entire file is bonus |
| 4 | `src/parser.c` + **`parser_bonus.c`** | Duplicate file | `parse_simple_cmd` is 24 lines; guards would push it to 29 |
| 5 | `src/executor.c` | `#if BONUS` / `#else` stub at global scope | `exec_node_logic` needs bonus body + mandatory stub; `traverse_tree` calls it unconditionally |
| 6 | `src/lexer_utils.c` | `#if BONUS` / `#else` stub at global scope | `is_special_char` defined twice — bonus body and mandatory body |
| 7 | `src/main_loop.c` | `#if BONUS` / `#else` stub at global scope | `process_tokens` defined twice — with and without `expand_wildcards()` |
| 8 | `includes/minishell.h` | `#if BONUS` prototype guards | Bonus-only functions |

**Total: 8 files touched, 3 files renamed/duplicated.**

---

## 1. `Makefile`

- `SRC_FILES` contains `parser.c` but **not** `wildcards.c` / `wildcards_utils.c`
  (those no longer exist under that name).
- The mandatory build uses `parser.c` and `-DBONUS=0`.
- The bonus build swaps `parser.c` → `parser_bonus.c` and adds
  `wildcards_bonus.c` + `wildcards_utils_bonus.c` on top.

```makefile
SRC_FILES = ... \
    parser.c \
    ...            # wildcards.c and wildcards_utils.c are NOT here

BONUS_EXTRA = \
    wildcards_bonus.c \
    wildcards_utils_bonus.c

# Bonus obj list: swap parser.o for parser_bonus.o, then append wildcard objs
OBJS_BONUS := $(subst $(OBJ_DIR)/parser.o,$(OBJ_DIR)/parser_bonus.o,$(OBJS))
OBJS_BONUS += $(addprefix $(OBJ_DIR)/, $(BONUS_EXTRA:.c=.o))

$(NAME): CFLAGS += -DBONUS=0
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LREAD) -o $(NAME)

bonus: CFLAGS += -DBONUS=1
bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(LREAD) -o $(NAME)
```

> `make` → no wildcards, simplified `parser.c`, `-DBONUS=0`.  
> `make bonus` → swaps in `parser_bonus.c`, adds `wildcards_bonus.c` +
> `wildcards_utils_bonus.c`, compiles with `-DBONUS=1`.

---

## 2 & 3. `wildcards.c` → `wildcards_bonus.c` / `wildcards_utils.c` → `wildcards_utils_bonus.c`

Rename both files. No content changes needed — they are 100% bonus code.
The mandatory build simply does not compile them.

Functions inside:
- `match_pattern()`, `process_dir_entry()`, `get_wildcard_matches()`,
  `insert_matches()`, `expand_wildcards()` — wildcard expansion pipeline
- `swap_nodes_value()`, `sort_matches()` — alphabetical sort of matches

---

## 4. `parser.c` (mandatory) + `parser_bonus.c` (bonus)

**Why a duplicate?** `parse_simple_cmd` currently has a **24-line body**.
Adding `#if BONUS / #else / #endif` for the `L_PAREN` check and the `while`
condition would add 5 preprocessor lines → **29 lines**. Exceeds the norm.

### `parser.c` (mandatory version — simplified)

Remove `parse_expression()` entirely. Change `parse_simple_cmd()` and
`parser()` to not reference `AND`, `OR`, `L_PAREN`, or `R_PAREN`:

```c
// parse_simple_cmd: mandatory while condition (no AND/OR/parens)
while (*tokens && (*tokens)->type != PIPE)
// No L_PAREN branch

// parser: calls parse_pipe directly
t_node  *parser(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    return (parse_pipe(&tokens));
}
```

`parse_pipe()` is identical in both versions.

### `parser_bonus.c` (bonus version — full copy with bonus changes)

Keep the full current content of `parser.c` unchanged. This version has:
- The `L_PAREN` branch in `parse_simple_cmd()`
- The bonus `while` condition using `AND`/`R_PAREN`
- `parse_expression()` with the `&&`/`||` loop
- `parser()` calling `parse_expression()`

---

## 5. `src/executor.c` — `#if BONUS` / `#else` stub at global scope

`exec_node_logic` is defined twice at global scope. `traverse_tree` calls it
unconditionally — safe because mandatory parser never produces `NODE_AND`/`NODE_OR`
nodes, so the stub is dead code in the mandatory build.

```c
#if BONUS

int	exec_node_logic(t_node *node, t_shell *shell)
{
    int	status;

    status = traverse_tree(node->left, shell);
    if (node->type == NODE_AND)
    {
        if (status == 0)
            return (traverse_tree(node->right, shell));
    }
    else
    {
        if (status != 0)
            return (traverse_tree(node->right, shell));
    }
    return (status);
}

#else

int	exec_node_logic(t_node *node, t_shell *shell)
{
    (void)node;
    (void)shell;
    return (0);
}

#endif
```

`traverse_tree` body stays clean with no preprocessor inside it:

```c
int	traverse_tree(t_node *node, t_shell *shell)
{
    if (!node)
        return (shell->last_exit_code);
    if (node->type == NODE_PIPE)
        return (exec_node_pipe(node, shell));
    else if (node->type == NODE_AND || node->type == NODE_OR)
        return (exec_node_logic(node, shell));
    else if (node->type == NODE_CMD)
        return (exec_node_cmd(node, shell));
    return (0);
}
```

---

## 6. `src/lexer_utils.c` — `#if BONUS` / `#else` stub at global scope

`is_special_char` is defined twice at global scope — `#if` cannot go inside a
function body.

```c
#if BONUS

int	is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&'
        || c == '(' || c == ')');
}

#else

int	is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

#endif
```

> This is the root gate: by not recognising `&`, `(`, `)` as special chars
> in mandatory, `&&`, `||`, `(`, `)` are never tokenised, so no downstream
> code in the lexer/parser ever sees them.

---

## 7. `src/main_loop.c` — `#if BONUS` / `#else` stub at global scope

`process_tokens` is defined twice at global scope — the wildcard call cannot
be guarded inside the function body.

```c
#if BONUS

t_token	*process_tokens(t_token *tokens, t_shell *shell)
{
    tokens = add_expansion_info(tokens);
    tokens = expand_dollars(shell, tokens);
    tokens = split_expanded_tokens(tokens);
    tokens = expand_wildcards(tokens);
    tokens = remove_quotes_from_tokens(tokens);
    return (tokens);
}

#else

t_token	*process_tokens(t_token *tokens, t_shell *shell)
{
    tokens = add_expansion_info(tokens);
    tokens = expand_dollars(shell, tokens);
    tokens = split_expanded_tokens(tokens);
    tokens = remove_quotes_from_tokens(tokens);
    return (tokens);
}

#endif
```

---

## 8. `includes/minishell.h` — Guard bonus-only prototypes

```c
#if BONUS
/* src/wildcards_bonus.c */
t_token	*expand_wildcards(t_token *head);

/* src/wildcards_utils_bonus.c */
void	swap_nodes_value(t_token *a, t_token *b);
void	sort_matches(t_token *head);

/* src/parser_bonus.c */
t_node	*parse_expression(t_token **tokens);

/* src/executor.c (bonus build) */
int	exec_node_logic(t_node *node, t_shell *shell);

/* src/parser_utils.c */
t_node	*handle_parenthesis(t_token **tokens);
#endif
```

---

## Change Count

| Category | Count |
|---|---|
| Files renamed to `_bonus.c` (bonus-only content) | 2 |
| Files duplicated as `_bonus.c` (same + bonus changes) | 1 (`parser`) |
| Files with `#if BONUS` guards | 3 (`executor.c`, `lexer_utils.c`, `main_loop.c`) |
| Header + Makefile updates | 2 |
| **Total files touched** | **8** |
| **`#if BONUS` blocks to insert** | **5** |

---

## Recommended Order of Work

1. Rename `wildcards.c` → `wildcards_bonus.c` and `wildcards_utils.c` → `wildcards_utils_bonus.c`.
2. Create `parser_bonus.c` as a copy of the current `parser.c`. Simplify `parser.c` (mandatory).
3. Add the 2 guards in `executor.c`.
4. Add the guard in `lexer_utils.c` (`is_special_char`).
5. Add the guard in `main_loop.c` (`process_tokens`).
6. Guard the prototypes in `minishell.h`.
7. Update the `Makefile` with the `bonus` target.
8. Run `make` and verify mandatory compiles and runs without wildcards/`&&`/`||`.
9. Run `make bonus` and verify bonus features work.
