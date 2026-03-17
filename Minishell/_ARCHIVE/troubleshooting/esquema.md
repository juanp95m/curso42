
# Diagrama de Flujo

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                        TANQUESHELL - DIAGRAMA DE FLUJO                     ║
╚══════════════════════════════════════════════════════════════════════════════╝


  ┌─────────────────────────────────────────────────┐
  │              INICIO (main.c)                    │
  │  1. init_shell_state(&shell, envp)              │
  │     - Copia envp a env_list (lista enlazada)    │
  │     - last_exit_code = 0                        │
  │  2. Inicializa vars: OLDPWD, SHLVL, PWD, etc.  │
  └────────────────────┬────────────────────────────┘
                       │
                       ▼
  ╔════════════════════════════════════════════╗
  ║         BUCLE PRINCIPAL (while 1)         ║◄─────────────────────────────┐
  ╚════════════════════╤══════════════════════╝                              │
                       │                                                     │
                       ▼                                                     │
  ┌────────────────────────────────────────┐                                 │
  │  readline("Tanqueshell$>")             │                                 │
  │  o get_next_line() si no es TTY        │                                 │
  └──────────────┬─────────────────────────┘                                 │
                 │                                                           │
        ┌────────┼────────┐                                                  │
        ▼        ▼        ▼                                                  │
   ┌────────┐ ┌──────┐ ┌────────────┐                                       │
   │ NULL   │ │ ""   │ │ input OK   │                                       │
   │(Ctrl-D)│ │vacío │ │ "ls -l |.."│                                       │
   └───┬────┘ └──┬───┘ └─────┬──────┘                                       │
       │         │            │                                              │
       ▼         │            │     add_history(input)                       │
   ┌────────┐    │            ▼                                              │
   │ EXIT   │    └──────► continue ──────────────────────────────────────────►│
   │ SHELL  │                                                                │
   └────────┘                                                                │
                                                                             │
  ═══════════════════════════════════════════════════════════════             │
  ║ FASE 1: LEXER   lexer(input_readline)  →  t_token *tokens  ║             │
  ═══════════════════════════════════════════════════════════════             │
                                                                             │
      Input: "echo $USER | wc -l > out.txt"                                  │
                       │                                                     │
                       ▼                                                     │
      ┌──────────────────────────────────────────────────┐                   │
      │  Recorre carácter a carácter el string:          │                   │
      │                                                  │                   │
      │  ¿Espacio?  → Saltar (i++)                       │                   │
      │                                                  │                   │
      │  ¿Char especial (|<>&())?                        │                   │
      │     → handle_operator()                          │                   │
      │       - Detecta dobles: >> << && ||              │                   │
      │       - Crea token con assign_token_type()       │                   │
      │         (PIPE, REDIRECT_IN, REDIRECT_OUT,        │                   │
      │          APPEND, HEREDOC, AND, OR, L/R_PAREN)    │                   │
      │                                                  │                   │
      │  ¿Otro carácter?                                 │                   │
      │     → handle_word()                              │                   │
      │       - Busca fin de la palabra                  │                   │
      │       - Respeta comillas (' y ")                 │                   │
      │       - Detecta tipo: recon_builtin()            │                   │
      │         (ECHO, CD, ENV, EXIT, EXPORT, PWD,       │                   │
      │          UNSET, o WORD genérico)                  │                   │
      │       - Guarda info de quote (NONE/SINGLE/DOUBLE)│                   │
      └────────────────────────┬─────────────────────────┘                   │
                               │                                             │
                               ▼                                             │
      Resultado (lista enlazada de tokens):                                  │
      ┌──────┐   ┌───────┐   ┌────┐   ┌────┐   ┌─────┐   ┌───┐   ┌───────┐ │
      │ECHO  │──▶│ WORD  │──▶│PIPE│──▶│WORD│──▶│WORD │──▶│ > │──▶│ WORD  │ │
      │"echo"│   │"$USER"│   │"|" │   │"wc"│   │"-l" │   │   │   │"out"  │ │
      └──────┘   └───────┘   └────┘   └────┘   └─────┘   └───┘   └───────┘ │
                                                                             │
  ═══════════════════════════════════════════════════════════════             │
  ║ FASE 1b: EXPANSIÓN   expand_dollars(&shell, tokens)         ║            │
  ═══════════════════════════════════════════════════════════════             │
                                                                             │
      ┌──────────────────────────────────────────────────────┐               │
      │  1. add_expansion_info(tokens)                       │               │
      │     - Marca expandable=TRUE si tiene $ y             │               │
      │       NO está entre comillas simples                 │               │
      │                                                      │               │
      │  2. expand_dollars(&shell, tokens)                   │               │
      │     - Recorre tokens marcados expandable=TRUE        │               │
      │     - Para cada $VAR:                                │               │
      │       · $? → shell->last_exit_code                   │               │
      │       · $VAR → busca en env_list (get_env_var)       │               │
      │       · Si no existe → string vacío ""               │               │
      │     - Reemplaza token->value con la expansión        │               │
      │                                                      │               │
      │  3. remove_quotes_from_tokens(tokens)                │               │
      │     - Elimina comillas ' y " de cada token           │               │
      │     - Respeta contexto (no borra comillas anidadas)  │               │
      └────────────────────────┬─────────────────────────────┘               │
                               │                                             │
                               ▼                                             │
      Tokens expandidos y limpios:                                           │
      ┌──────┐   ┌────────┐   ┌────┐   ┌────┐   ┌─────┐  ┌───┐  ┌───────┐  │
      │ECHO  │──▶│ WORD   │──▶│PIPE│──▶│WORD│──▶│WORD │──▶│ > │──▶│ WORD │  │
      │"echo"│   │"jperez"│   │"|" │   │"wc"│   │"-l" │  │   │  │"out"  │  │
      └──────┘   └────────┘   └────┘   └────┘   └─────┘  └───┘  └───────┘  │
                                                                             │
  ═══════════════════════════════════════════════════════════════             │
  ║ FASE 2: PARSER   parser(tokens)  →  t_node *nodes (AST)    ║            │
  ═══════════════════════════════════════════════════════════════             │
                                                                             │
      ┌──────────────────────────────────────────────────────┐               │
      │  Parsing descendente recursivo con precedencia:      │               │
      │                                                      │               │
      │  parse_expression() ─ Nivel 1: && y ||               │               │
      │       │                                              │               │
      │       └──► parse_pipe() ─ Nivel 2: |                 │               │
      │                 │                                    │               │
      │                 └──► parse_simple_cmd() ─ Nivel 3    │               │
      │                       │                              │               │
      │                       ├─ Si "(" → handle_parenthesis │               │
      │                       │   (recursión a expression)   │               │
      │                       │                              │               │
      │                       └─ Si no → crear t_command:    │               │
      │                          - WORD/BUILTIN → add_arg()  │               │
      │                          - < → parse_infile()        │               │
      │                          - > / >> → parse_outfile()  │               │
      │                          - << → parse_heredoc()      │               │
      └────────────────────────┬─────────────────────────────┘               │
                               │                                             │
                               ▼                                             │
      AST generado para "echo jperez | wc -l > out.txt":                     │
                                                                             │
                         ┌──────────┐                                        │
                         │NODE_PIPE │                                        │
                         │    |     │                                        │
                         └─┬──────┬─┘                                        │
                       ┌───┘      └───┐                                      │
                       ▼              ▼                                      │
                ┌───────────┐  ┌────────────────┐                            │
                │ NODE_CMD  │  │   NODE_CMD     │                            │
                │           │  │                │                            │
                │ args:     │  │ args:          │                            │
                │ ["echo",  │  │ ["wc", "-l"]  │                            │
                │  "jperez"]│  │ outfile:"out"  │                            │
                │           │  │ append: FALSE  │                            │
                └───────────┘  └────────────────┘                            │
                                                                             │
  ═══════════════════════════════════════════════════════════════             │
  ║ FASE 2b: RESOLVE PATHS   assign_fullpath_recursive()       ║            │
  ═══════════════════════════════════════════════════════════════             │
                                                                             │
      ┌──────────────────────────────────────────────────────┐               │
      │  Recorre el AST recursivamente:                      │               │
      │  Para cada NODE_CMD → find_command(args[0], shell)   │               │
      │    - Si args[0] contiene '/'  → usa la ruta directa  │               │
      │    - Si no → busca en $PATH (ft_split por ':')       │               │
      │      · Prueba /usr/bin/echo, /bin/echo, etc.         │               │
      │      · access(full_path, X_OK) para verificar        │               │
      │    - Guarda en cmd->fullpath                         │               │
      └────────────────────────┬─────────────────────────────┘               │
                               │                                             │
                               ▼                                             │
  ═══════════════════════════════════════════════════════════════             │
  ║ FASE 3: EXECUTOR   traverse_tree(nodes, &shell)            ║            │
  ═══════════════════════════════════════════════════════════════             │
                                                                             │
      ┌──────────────────────────────────────────────────────────┐           │
      │  traverse_tree(node) evalúa según node->type:            │           │
      │                                                          │           │
      │  ┌─────────────────────────────────────────────────┐     │           │
      │  │ NODE_PIPE → exec_node_pipe()                    │     │           │
      │  │   1. pipe(pfd) → crea tubería                   │     │           │
      │  │   2. fork() hijo izquierdo:                     │     │           │
      │  │      - dup2(pfd[1], STDOUT) → salida al pipe    │     │           │
      │  │      - traverse_tree(node->left)                │     │           │
      │  │   3. fork() hijo derecho:                       │     │           │
      │  │      - dup2(pfd[0], STDIN) → entrada del pipe   │     │           │
      │  │      - traverse_tree(node->right)               │     │           │
      │  │   4. close_pipe() + waitpid() ambos hijos       │     │           │
      │  │   5. Retorna exit status del hijo derecho       │     │           │
      │  └─────────────────────────────────────────────────┘     │           │
      │                                                          │           │
      │  ┌─────────────────────────────────────────────────┐     │           │
      │  │ NODE_AND → exec_node_logic()                    │     │           │
      │  │   - Ejecuta left                                │     │           │
      │  │   - Si exit_code == 0 → ejecuta right           │     │           │
      │  │   - Si no → NO ejecuta right                    │     │           │
      │  │                                                 │     │           │
      │  │ NODE_OR → exec_node_logic()                     │     │           │
      │  │   - Ejecuta left                                │     │           │
      │  │   - Si exit_code != 0 → ejecuta right           │     │           │
      │  │   - Si no → NO ejecuta right                    │     │           │
      │  └─────────────────────────────────────────────────┘     │           │
      │                                                          │           │
      │  ┌─────────────────────────────────────────────────┐     │           │
      │  │ NODE_CMD → exec_node_cmd()                      │     │           │
      │  │                                                 │     │           │
      │  │   ¿Es BUILTIN?                                 │     │           │
      │  │      │                                          │     │           │
      │  │   SÍ ▼                        NO ▼              │     │           │
      │  │ ┌──────────────────┐   ┌─────────────────────┐  │     │           │
      │  │ │exec_builtin_     │   │fork() → hijo:       │  │     │           │
      │  │ │parent()          │   │ exec_external_child()│  │     │           │
      │  │ │                  │   │                     │  │     │           │
      │  │ │1.Salva STDIN/OUT │   │1.setup_redirections()│  │     │           │
      │  │ │  (dup)           │   │  (dup2 infile/      │  │     │           │
      │  │ │2.setup_          │   │   outfile)          │  │     │           │
      │  │ │  redirections()  │   │2.execve(fullpath,   │  │     │           │
      │  │ │3.run_builtin():  │   │   args, envp)      │  │     │           │
      │  │ │  cd/echo/pwd/    │   │                     │  │     │           │
      │  │ │  export/unset/   │   │Si falla:            │  │     │           │
      │  │ │  env/exit        │   │ "command not found" │  │     │           │
      │  │ │4.Restaura        │   │  exit(127)          │  │     │           │
      │  │ │  STDIN/OUT       │   │                     │  │     │           │
      │  │ │5.Retorna status  │   │Padre: waitpid()     │  │     │           │
      │  │ └──────────────────┘   │ → exit status       │  │     │           │
      │  │                        └─────────────────────┘  │     │           │
      │  └─────────────────────────────────────────────────┘     │           │
      └────────────────────────────┬─────────────────────────────┘           │
                                   │                                         │
                                   ▼                                         │
      ┌──────────────────────────────────────────────┐                       │
      │  shell.last_exit_code = resultado            │                       │
      └──────────────────────────┬───────────────────┘                       │
                                 │                                           │
                                 ▼                                           │
  ═══════════════════════════════════════════════════════════════             │
  ║ FASE 4: CLEANUP                                             ║           │
  ═══════════════════════════════════════════════════════════════             │
                                                                             │
      ┌──────────────────────────────────────────────┐                       │
      │  free_tokens(tokens)    ← libera lista tokens│                       │
      │  free_ast(nodes)        ← libera árbol AST   │                       │
      │  free(input_readline)   ← libera el input    │                       │
      └──────────────────────────┬───────────────────┘                       │
                                 │                                           │
                                 └───────────────────────────────────────────┘
                                      Vuelve al readline


  ══════════════════════════════════════════════════
  ║  RESUMEN DEL PIPELINE COMPLETO               ║
  ══════════════════════════════════════════════════

  ┌──────────┐    ┌──────────┐    ┌──────────┐    ┌──────────┐    ┌─────────┐
  │ readline │    │  LEXER   │    │ EXPANDER │    │  PARSER  │    │EXECUTOR │
  │          │───▶│          │───▶│          │───▶│          │───▶│         │
  │ "echo    │    │ Tokeniza │    │ $VAR →   │    │ Tokens → │    │ AST →   │
  │  $HOME"  │    │ string   │    │ valor    │    │ AST      │    │ fork/   │
  │          │    │ a lista  │    │ + quita  │    │ (árbol)  │    │ execve  │
  │          │    │ enlazada │    │ comillas │    │          │    │         │
  └──────────┘    └──────────┘    └──────────┘    └──────────┘    └─────────┘
                                                                       │
                                                                       ▼
                                                              ┌─────────────┐
                                                              │  RESULTADO  │
                                                              │ en pantalla │
                                                              │ + exit_code │
                                                              └─────────────┘


  ══════════════════════════════════════════════════
  ║  BUILTINS DISPONIBLES                         ║
  ══════════════════════════════════════════════════

  ┌───────────┬──────────────────────────────────────────────┐
  │ Builtin   │ Descripción                                  │
  ├───────────┼──────────────────────────────────────────────┤
  │ echo      │ Imprime args (-n sin newline)                │
  │ cd        │ Cambia directorio (actualiza PWD/OLDPWD)     │
  │ pwd       │ Imprime directorio actual                    │
  │ export    │ Añade/modifica variable de entorno           │
  │ unset     │ Elimina variable de entorno                  │
  │ env       │ Imprime todas las variables de entorno       │
  │ exit      │ Sale de la shell con código de salida        │
  └───────────┴──────────────────────────────────────────────┘

  * Builtins se ejecutan en el proceso PADRE (sin fork)
  * Comandos externos se ejecutan en un proceso HIJO (fork + execve)


  ══════════════════════════════════════════════════
  ║  ESTRUCTURAS DE DATOS CLAVE                   ║
  ══════════════════════════════════════════════════

  t_shell ──► Estado global (env_list, last_exit_code)
  t_token ──► Lista enlazada doble (value, type, quote, expandable)
  t_node  ──► Nodo del AST (type: CMD|PIPE|AND|OR, left, right, cmd)
  t_command ──► Comando (args[], fullpath, infile, outfile, heredoc, append)
  t_env   ──► Variable de entorno (key, value) en lista enlazada
```