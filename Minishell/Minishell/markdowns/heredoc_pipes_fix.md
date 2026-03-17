# Bug: Heredocs fallan dentro de pipes

## Ejemplo que fallaba

```bash
cat << eof << iof | grep "hola"
```

## ¿Por qué fallaba?

### Flujo ANTES del fix

1. `exec_node_pipe()` hace `fork()` para crear el hijo izquierdo (`cat << eof << iof`).
2. Dentro de `open_fork()`, el hijo redirige STDOUT al pipe (`dup2(pfd[1], STDOUT_FILENO)`).
3. El hijo ejecuta `exec_node_cmd()` → `exec_external_child()` → `setup_redirections()` → `handle_input_redirections()` → `get_heredoc_fd()`.
4. `get_heredoc_fd()` llama a `process_heredoc()`, que hace **otro fork()** para leer el heredoc con `readline("> ")`.
5. **Problema**: Este "nieto" hereda los file descriptors del pipe. Aunque en el lado izquierdo STDIN no se redirige al pipe, el proceso hijo puede tener problemas con el terminal porque ya está en un subproceso forkeado. El `readline()` puede no funcionar correctamente porque el proceso hijo ya no es el líder del grupo de procesos del terminal.

### El problema de fondo

**Los heredocs se leían DENTRO de los procesos hijos del pipe**, cuando deberían leerse **ANTES** de crear el pipe. Bash lee todos los heredocs desde el terminal antes de ejecutar nada.

```
ANTES (mal):
  main → fork(pipe_left) → fork(pipe_right)
                ↓
          fork(heredoc) → readline("> ")  ← ❌ ya no tiene control del terminal
```

## Solución implementada

### Flujo DESPUÉS del fix

```
AHORA (bien):
  main → preprocess_heredocs() → readline("> ")  ← ✅ terminal real
           ↓
       guarda fd en cmd->heredoc_fd
           ↓
       fork(pipe_left) → usa cmd->heredoc_fd directamente
       fork(pipe_right) → ...
```

### Cambios realizados

| Archivo | Cambio |
|---------|--------|
| `includes/structs.h` | Añadido campo `int heredoc_fd` a `t_command` |
| `src/struct_initializer.c` | Inicializa `heredoc_fd = -1` |
| `src/heredoc.c` | Nueva función `preprocess_heredocs()` que recorre el AST recursivamente y lee todos los heredocs ANTES de ejecutar |
| `src/main_loop.c` | Llama a `preprocess_heredocs()` antes de `traverse_tree()` |
| `src/executor_utils.c` | `handle_input_redirections()` ahora usa `cmd->heredoc_fd` (ya pre-computado) en vez de llamar a `get_heredoc_fd()` |
| `src/free_complex.c` | Cierra `heredoc_fd` si quedó abierto al liberar el comando |
| `includes/minishell.h` | Prototipo de `preprocess_heredocs()` |

### ¿Por qué `heredoc_fd` en `t_command`?

Al leer el heredoc en el proceso principal (antes de cualquier fork), obtenemos un fd válido. Lo guardamos en `cmd->heredoc_fd` para que cuando el hijo del pipe ejecute las redirecciones, simplemente haga `dup2(cmd->heredoc_fd, STDIN_FILENO)` sin necesidad de volver a leer el heredoc.

### ¿Qué pasa con `Ctrl+C` en un heredoc?

Si el usuario pulsa `Ctrl+C` durante la lectura de un heredoc, `preprocess_heredocs()` devuelve `1` y `process_input()` asigna `g_signal_status` (130) como exit code sin ejecutar el árbol. Así `echo $?` muestra `130` como en bash.
