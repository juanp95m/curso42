# Fix: Pipe Syntax Error Detection

## Problema

Dos comandos que bash rechaza con un error de sintaxis eran ejecutados incorrectamente por minishell:

| Comando     | Bash (esperado)                                | Minishell (incorrecto) |
|-------------|------------------------------------------------|------------------------|
| `\| ls \| wc` | `syntax error near unexpected token '|'`    | ejecutaba y daba output |
| `ls \|   \| wc` | `syntax error near unexpected token '|'` | ejecutaba y daba output |

## Causa raíz

La función `check_syntax_errors()` ya existía documentada en `src/check_syntax.md`, pero **nunca se compilaba** (era un `.md`, no un `.c`) y su llamada en `main_loop.c` estaba **comentada**. En consecuencia, el parser intentaba ejecutar esos tokens inválidos sin validar previamente la estructura.

## Qué hace la función de validación

`check_syntax_errors(t_token *tokens)` recorre la lista de tokens **antes de la expansión y el parsing** y detecta tres patrones inválidos:

### 1. Pipe/operador al inicio (`| ls | wc`)
```
tokens: PIPE → WORD("ls") → PIPE → WORD("wc")
         ^
         is_pipe_op(tokens->type) == true  →  ERROR
```
Mensaje: `minishell: syntax error near unexpected token '|'`

### 2. Dos operadores consecutivos (`ls |   | wc`)
```
tokens: WORD("ls") → PIPE → PIPE → WORD("wc")
                      ^^^^   ^^^^
          is_pipe_op(cur) && is_pipe_op(cur->next)  →  ERROR
```
El lexer descarta los espacios, así que `|   |` produce dos tokens `PIPE` seguidos.
Mensaje: `minishell: syntax error near unexpected token '|'`

### 3. Pipe/operador al final (`ls | wc |`)
```
tokens: ... → PIPE   (último token)
               ^^^^
         is_pipe_op(cur->type) && cur->next == NULL  →  ERROR
```
Mensaje: `minishell: syntax error near unexpected token 'newline'`

## Cambios realizados

### 1. `src/check_syntax.c` (archivo nuevo)
Se creó el archivo `.c` compilable a partir del código que ya existía en `src/check_syntax.md`.
Corrección adicional: `#include <minishell.h>` → `#include "minishell.h"`.

### 2. `Makefile`
Se añadió `check_syntax.c` a la lista `SRC_FILES` para que sea compilado.

```makefile
# Antes
main.c \
main_loop.c \

# Después
check_syntax.c \
main.c \
main_loop.c \
```

### 3. `includes/minishell.h`
Se descomentó la declaración de la función.

```c
// Antes
// int   check_syntax_errors(t_token *tokens);

// Después
int     check_syntax_errors(t_token *tokens);
```

### 4. `src/main_loop.c`
Se activó la llamada (antes comentada) y se movió **antes** de `process_tokens` para validar la sintaxis sobre los tokens crudos, igual que hace bash.

```c
// Antes (todo comentado y DESPUÉS de process_tokens)
tokens = process_tokens(tokens, shell);
// if (check_syntax_errors(tokens)) { ... }

// Después (activo y ANTES de process_tokens)
if (check_syntax_errors(tokens))
{
    shell->last_exit_code = 2;
    free_tokens(tokens);
    return ;
}
tokens = process_tokens(tokens, shell);
```

## Por qué el check va ANTES de process_tokens

Bash detecta errores de sintaxis durante el parsing, **antes** de la expansión de variables. Colocar el check antes de `process_tokens` replica ese comportamiento: si la estructura de operadores es inválida, el shell la rechaza sin intentar expandir `$VAR` ni ejecutar nada.

## Cobertura de operadores

La función cubre los tres operadores de control que actúan como separadores de comandos:

| Token | Tipo    | Cubierto |
|-------|---------|----------|
| `\|`  | `PIPE`  | ✓        |
| `\|\|`| `OR`    | ✓        |
| `&&`  | `AND`   | ✓        |
