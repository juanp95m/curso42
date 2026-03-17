# Flux examples

## 1st example

```
(echo ok && false) || echo fallback

              NODE_OR              ← traverse_tree() starts here
             /        \
         NODE_AND     NODE_CMD
        /        \      └── args: ["echo", "fallback"]
    NODE_CMD   NODE_CMD
    ["echo",   ["false"]
      "ok"]


traverse_tree(NODE_OR)
       │
       └─ NODE_OR ─────────────────────────────────▶ exec_node_logic()
                 │
                 │  STEP 1: evaluate LEFT child
                 │
                 ├── traverse_tree(NODE_AND)
                 │         │
                 │         └─ NODE_AND ─────────────▶ exec_node_logic()
                 │                   │
                 │                   │  STEP 1a: evaluate LEFT child
                 │                   │
                 │                   ├── traverse_tree(NODE_CMD: echo ok)
                 │                   │         │
                 │                   │         └─ NODE_CMD ──▶ exec_node_cmd()
                 │                   │                   │
                 │                   │                   └─ BUILTIN (echo) ──▶ exec_builtin_parent()
                 │                   │                              [runs in PARENT process]
                 │                   │                              prints "ok" → returns $? = 0
                 │                   │
                 │                   │  STEP 1b: AND → status == 0 → run RIGHT child
                 │                   │
                 │                   └── traverse_tree(NODE_CMD: false)
                 │                             │
                 │                             └─ NODE_CMD ──▶ exec_node_cmd()
                 │                                       │
                 │                                       └─ EXTERNAL (false) ──▶ fork()
                 │                                                           /              \
                 │                                                       PARENT            CHILD
                 │                                                          │                 │
                 │                                                     waitpid(pid)    execve("false")
                 │                                                          │                 │
                 │                                                      $? = 1          exits with 1
                 │
                 │                   NODE_AND returns $? = 1
                 │
                 │  STEP 2: OR → status != 0 → run RIGHT child
                 │
                 └── traverse_tree(NODE_CMD: echo fallback)
                           │
                           └─ NODE_CMD ──────────────▶ exec_node_cmd()
                                     │
                                     └─ BUILTIN (echo) ──▶ exec_builtin_parent()
                                                [runs in PARENT process]
                                                prints "fallback" → returns $? = 0

       NODE_OR returns $? = 0
```

The key points to explain to the evaluator:

Root is always the rightmost operator — || is the root because && binds first (left-associative, same precedence).
Parentheses only affect nesting in the token; the tree structure handles grouping naturally — NODE_AND sits as the left child of NODE_OR.
Short-circuit evaluation — NODE_AND runs false only because echo ok returned 0. Then NODE_OR runs echo fallback only because NODE_AND returned 1 (non-zero).
echo is a builtin → runs in the parent, no fork(). false is external → triggers fork() + execve() + waitpid().

### por que tenemos que ignore signals antes del fork y luego restaurar el interactive signals en exec_node_cmd()

Son tres razones distintas, una por cada pieza:

1. setup_ignore_signals() ANTES del fork() — proteger al padre

Mientras el padre está esperando (waitpid) que el hijo termine, el usuario puede pulsar Ctrl+C. Si el padre tiene activo handle_sigint, ese handler correría en el padre: imprimiría un newline, llamaría a rl_redisplay()… todo mientras el hijo sigue ejecutándose. Eso rompería la pantalla y el estado de readline.

Con SIG_IGN el padre simplemente ignora la señal. El kernel la entrega también al hijo (porque los procesos del mismo grupo de proceso reciben la señal), y el hijo la maneja con su propio handler (SIG_DFL), terminando correctamente. El padre recoge ese estado via waitpid.

2. setup_child_signals() EN EL HIJO justo después del fork()

fork() hereda los handlers del padre — en este punto el hijo hereda SIG_IGN. Un proceso ejecutado con execve no puede recibir señales que el padre tiene en SIG_IGN si no las resetea antes. Por eso el hijo restaura SIG_DFL para SIGINT y SIGQUIT inmediatamente, antes de llamar a execve. Así el programa externo (p.ej. cat, sleep) se comporta normalmente ante Ctrl+C.

3. setup_interactive_signals() DESPUÉS del waitpid() — restaurar la shell

Una vez el hijo ha terminado, la shell vuelve al prompt interactivo. Hay que restaurar el handler handle_sigint para que Ctrl+C vuelva a limpiar la línea de readline y mostrar un nuevo prompt, en lugar de seguir ignorado.

Resumen del ciclo completo:

```
PARENT (interactive handler activo)
  │
  ├─ setup_ignore_signals()     ← padre inmune a Ctrl+C durante la espera
  │
  ├─ fork()
  │      │
  │      └─ CHILD: setup_child_signals()  ← resetea a SIG_DFL
  │                exec_external_child()
  │                execve(...)            ← Ctrl+C termina el hijo
  │
  ├─ waitpid()                  ← padre espera, ignorando señales
  │
  └─ setup_interactive_signals() ← padre restaura handle_sigint para el prompt
```

La regla de bash que se está replicando es: el padre (shell) ignora Ctrl+C mientras espera a un hijo; el hijo muere con él; la shell continúa viva y muestra un nuevo prompt.

# Por que export no crea la variable TEST en bash? export TEST=juan | grep TEST

Porque el | fuerza que ambos lados del pipe se ejecuten en procesos hijos (subshells). El export corre en un hijo, no en la shell padre.

```
bash (PARENT)
  │
  ├─ fork() → CHILD 1: ejecuta "export TEST=juan"
  │                    TEST existe en el env de CHILD 1
  │                    CHILD 1 termina → su env desaparece
  │
  └─ fork() → CHILD 2: ejecuta "grep TEST"
                        lee stdin del pipe
                        nunca ve TEST porque no está en su env
```
El env de un proceso hijo nunca se propaga hacia arriba. fork() copia el estado del padre hacia el hijo, pero los cambios en el hijo no vuelven al padre ni a sus hermanos.

# Por que usamos read_line_raw y no get_next_line?

La respuesta está en write_heredoc_loop(): ya usa readline cuando el input es un terminal. read_line_raw solo se usa en modo no-interactivo (isatty() == false). Son dos situaciones completamente distintas que justifican no usar get_next_line:

1. En modo interactivo ya se usa readline
```
if (isatty(STDIN_FILENO))
    line = readline("> ");   // ← readline, con prompt "> "
else
    line = read_line_raw(STDIN_FILENO);  // ← sin prompt, sin buffer
```

if (isatty(STDIN_FILENO))    line = readline("> ");   // ← readline, con prompt "> "else    line = read_line_raw(STDIN_FILENO);  // ← sin prompt, sin buffer
readline ya gestiona el prompt > , el historial, las teclas de edición, y devuelve NULL cuando heredoc_sigint cierra stdin ante Ctrl+C. No hay ninguna razón para reemplazarlo.

2. get_next_line tiene un buffer interno estático — problema fatal en pipes
```
echo "line1\nline2\nEOF\nmore_input" | ./minishell
```
get_next_line acumula datos en un buffer estático entre llamadas. En modo no-interactivo el stdin es un pipe:


echo "line1\nline2\nEOF\nmore_input" | ./minishell
get_next_line podría leer más bytes de los necesarios del pipe en su buffer interno. Cuando el heredoc termina y la shell pasa a ejecutar el siguiente comando, esos bytes extra ya se consumieron del pipe y se perdieron — el siguiente read no los vería.

read_line_raw lee de a 1 byte (read(fd, buf, 1)), garantizando que no consume ni un byte más allá del \n. El pipe queda intacto para quien venga después.

3. El contexto es un proceso hijo que va a exit()

El heredoc corre en un hijo forkeado (process_heredoc → fork() → heredoc_child_process). Un buffer estático de get_next_line que quede "a medias" en ese hijo no importa porque el proceso termina con exit(). Pero el problema del punto 2 (consumir bytes del pipe del padre) sigue siendo real antes del exit.

Resumen:

| Situación           | Función usada      | Por qué                                                                 |
|---------------------|-------------------|-------------------------------------------------------------------------|
| isatty() == true    | readline("> ")    | Prompt interactivo, historial, Ctrl+C via cierre de stdin               |
| isatty() == false   | read_line_raw()   | Lee 1 byte a la vez, no consume el pipe más allá del \n                |
| get_next_line       | nunca             | Buffer interno consume bytes del pipe que pertenecen a comandos posteriores |


# Make bonus no muestra el mensaje nothing to be done

bonus es PHONY, así que siempre ejecuta su recipe independientemente de timestamps — para tener el mismo comportamiento necesitas el mismo truco de convertir el binario en un target real. El patrón equivalente sería separar el rule de bonus igual que all/$(NAME):

Updated Makefile
Espera, ese cambio crea una regla duplicada para $(NAME) con recipes distintas — eso no funciona bien. Déjame revertirlo y hacerlo correctamente:

Edited
Makefile+2-4
La respuesta real: no se puede aplicar el mismo truco a bonus de forma limpia.

El motivo: all funciona porque $(NAME) es un archivo real — Make compara timestamps y decide si relinkar. Pero bonus es .PHONY, así que siempre ejecuta su recipe sin importar nada.

Para que bonus también dijera "Nothing to be done" habría que quitarlo de .PHONY y convertirlo en un target real (un archivo), lo cual va en contra de la semántica habitual y complicaría el Makefile innecesariamente para un proyecto de 42.

Lo que sí se arregló con el | en bonus: el problema del libft tocando el timestamp (si existía) ya no causará problemas en los .o de bonus.