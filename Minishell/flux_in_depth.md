# Esquema de Llamadas y Flujo de Ejecución (Minishell)

Este documento detalla el árbol de llamadas principal y describe el flujo de ejecución del proyecto Minishell, basado en los archivos del directorio `src/` y las declaraciones en `minishell.h`.

## 1. Árbol de Ejecución General (Esquemas Mandatory y Bonus)

El flujo varía dependiendo de si evaluamos la parte **Mandatory** (solo tuberías `|`) o el **Bonus** (que incluye operadores lógicos `&&`, `||` y comodines `*`).

### 1.1 Esquema Mandatory (`parser.c`)
```text
main()
 ├── init_shell_state()
 ├── setup_interactive_signals()
 └── run_shell() (Bucle interactivo)
      └── process_input()
           ├── get_user_input()
           ├── lexer()
           ├── check_syntax_errors()
           ├── process_tokens()
           │    ├── expand_dollars()
           │    └── remove_quotes_from_tokens()
           ├── parser() [Sin lógica &&/||]
           │    └── parse_pipe()
           │         └── parse_simple_cmd()
           │              └── dispatch_redirections()
           └── execute_command_tree()
                ├── preprocess_heredocs()
                └── traverse_tree()
                     ├── exec_node_pipe()
                     └── exec_node_cmd()
                          ├── exec_builtin_parent()
                          └── exec_external_child()
```

### 1.2 Esquema Bonus (`parser_bonus.c`)
```text
main()
 ├── init_shell_state()
 ├── setup_interactive_signals()
 └── run_shell() (Bucle interactivo)
      └── process_input()
           ├── get_user_input()
           ├── lexer()
           ├── check_syntax_errors()
           ├── process_tokens()
           │    ├── expand_dollars()
           │    ├── expand_wildcards() [BONUS] -> match_pattern()
           │    └── remove_quotes_from_tokens()
           ├── parser() [Maneja Lógica Compleja]
           │    └── parse_expression()  <- [Maneja && y ||]
           │         ├── parse_pipe()
           │         └── parse_simple_cmd()
           │              └── dispatch_redirections()
           └── execute_command_tree()
                ├── preprocess_heredocs()
                └── traverse_tree()
                     ├── exec_node_logic() <- [Exclusivo Bonus]
                     ├── exec_node_pipe()
                     └── exec_node_cmd()
                          ├── exec_builtin_parent()
                          └── exec_external_child()
```

---

## 2. Descripción por Sectores

### 2.1. Inicialización y Bucle Principal (`main`, `main_loop`, `struct_initializer`)
- **`main()`**: Punto de entrada. Configura el nivel de shell (`SHLVL`), procesa los argumentos y variables de entorno iniciales, instala `setup_interactive_signals()` para que la shell maneje Ctrl+C, y llama al bucle de la shell.
- **`init_shell_state()`**: Inicializa la estructura principal `t_shell` (variables globales, lista enlazada del entorno, etc.).
- **`create_envp_list()`**: Convierte el array `envp` en una lista enlazada para poder modificar las variables de entorno (usando `ft_env_new` y `ft_env_add_back`).
- **`run_shell()`**: Mantiene viva la consola, esperando nuevas instrucciones y dándole una salida adecuada a los comandos procesados.
- **`process_input()` / `get_user_input()`**: Lee la línea proporcionada en la terminal por el usuario. Utiliza **`readline`** en modo interactivo (cuando `isatty(STDIN_FILENO)` es verdadero) o **`read_line_raw`** en modo no-interactivo (cuando el stdin es un pipe o redirección). Llama a las fases de tokenizado, parseo y ejecución.

#### Por qué `read_line_raw` en lugar de `get_next_line`

| Situación           | Función usada      | Razón                                                                 |
|---------------------|-------------------|-------------------------------------------------------------------------|
| `isatty() == true`  | `readline("> ")` | Prompt interactivo, historial, Ctrl+C via cierre de stdin              |
| `isatty() == false` | `read_line_raw()` | Lee 1 byte a la vez, no consume el pipe más allá del `\n`              |
| `get_next_line`     | nunca             | Buffer interno consume bytes del pipe que pertenecen a comandos posteriores |

**Explicación detallada:**

1. **En modo interactivo** (`isatty() == true`):  
   `readline` proporciona autocompletar, historial con flechas, y manejo de Ctrl+C mediante cierre del stdin. No hay razón para reemplazarlo.

2. **En modo no-interactivo** (`isatty() == false`):  
   Cuando el stdin es un pipe (ej: `echo "comando" | ./minishell`), `get_next_line` acumula datos en un buffer estático. Si una heredoc lee más bytes del necesario con `get_next_line`, esos bytes permanecen en el buffer interno, y el siguiente comando ejecutado no los verá — han sido consumidos del pipe y están atrapados en la memoria estática.
   
   `read_line_raw` lee de a 1 byte (mediante `read(fd, buf, 1)`), garantizando que no se consume ni un byte más allá del `\n`. Esto asegura que el pipe permanece intacto para quien venga después.

3. **Context heredoc en proceso hijo:**  
   El heredoc corre en un proceso hijo forkeado (`process_heredoc() → fork() → heredoc_child_process()`). Un buffer estático que quede "a medias" no importa porque el proceso termina con `exit()`, pero el problema de consumir demasiados bytes del pipe del padre persiste antes del exit.

### 2.2. Análisis Léxico (Lexer)
Su objetivo es transformar un string (el input del usuario) en una lista enlazada de "tokens" (palabras, comillas, redirecciones, pipes).
- **`lexer()`**: Recorre la string introducida y va separándola en bloques (tokens).
- **`handle_word()` / `handle_operator()`**: Clasifican la porción leída de la string, identificando si es una cadena de texto normal o un operador reservado (`|`, `>`, `<`...).
- **`skip_quotes()`**: Analiza hasta dónde abarcan las comillas simples o dobles, garantizando que el texto dentro de ellas se mantenga agrupado.
- **`create_new_token()` / `add_token_back()`**: Inicializa una estructura de token y la enlaza a la lista del lexer temporal.

### 2.3. Validación y Expansión (`expander`, `check_syntax`)
El paso intermedio entre obtener tokens y generar el árbol es confirmar la sintaxis y analizar variables del entorno.
- **`check_syntax_errors()`**: Tras obtener la lista de tokens, comprueba que la estructura tenga sentido (e.g. que no envíes un pipe `|` solitario o una redirección sin un archivo a la derecha).
- **`process_tokens()`**: Actúa como un orquestador o pre-procesador de tokens antes de dar paso al `parser`.
- **`expand_dollars()`**: Revisa tokens en busca del símbolo `$` y sustituye su valor por lo que se encuentre en las variables de entorno de `t_shell`.
- **`split_expanded_tokens()`**: Si una variable expandida genera múltiples parámetros, los divide en nuevos tokens lógicos.
- **`expand_wildcards()`** *(Bonus)*: Sustituye los literales `*` por los nombres de los archivos coincidentes del directorio actual.
  - **`match_pattern()`**: Función auxiliar estática que verifica si un nombre de archivo coincide con el patrón wildcard. Implementa matching recursivo para `*` (que coincide con cualquier secuencia de caracteres, incluyendo subcarpetas si se usa recursivamente).
  - **`process_dir_entry()`**: Función auxiliar estática que procesa cada entrada del directorio durante el globbing. Salta automáticamente archivos ocultos (cuyo nombre comienza con `.`) a menos que el patrón especifique explícitamente la búsqueda de ocultos.
- **`remove_quotes_from_tokens()`**: Una vez evaluadas las variables dentro de las comillas dobles, limpia el input eliminando las comillas sobrantes.

### 2.4. Análisis Sintáctico (Parser): Mandatory vs Bonus
Toma la lista de tokens validada y expandida, convirtiéndola en un Árbol Sintáctico Abstracto (AST) de tipo `t_node`. Aquí se aloja la gran diferencia estructural entre la versión base y el bonus del proyecto.

#### Mandatory (`parser.c`): Árbol de Tuberías
En la parte Mandatory, el proyecto está exento de lógica compleja. El parser simplemente genera un "falso árbol" sesgado a la derecha, agrupando los comandos con tuberías.
- **`parser()`**: Entrada que conecta directamente a la evaluación de pipes.
- **`parse_pipe()`**: Toma los tokens y busca el símbolo PIPE (`|`). Si lo halla, instancia la jerarquía: el hijo izquierdo (`left`) asimila el comando actual, y el derecho (`right`) absorbe la siguiente partición o pipe.
- **`parse_simple_cmd()`**: Compila y enlaza un comando junto a sus strings de parámetros en un solo nodo hoja.

#### Bonus (`parser_bonus.c`): Árbol Binario Lógico
La inclusión de operadores lógicos `&&` y `||` transforma el parseo en la creación de un verdadero Árbol Binario basado en niveles de prioridad.
- **`parser()` / `parse_expression()`**: Entrada recursiva al parseo complejo. `parse_expression()` recorre el array priorizando la búsqueda de `&&` o `||` para posicionarlos como los **nodos raíz o intermedios** de ramificaciones extensas, generando un `NODE_AND` o `NODE_OR`.
- **Cascada de precedencia descendente**: En el Bonus, la jerarquía obedece a Bash. La llamada entra en `parse_expression()` (evaluación lógica) y desciende a pedir fragmentos a `parse_pipe()`. Como los pipelines unen comandos mucho más firmemente que un condicional, el sub-árbol en el que se convierte un bloque `&&` está internamente gobernado por pipes.
- **`dispatch_redirections()`**: recursiva que camina por el AST. Dependiendo del tipo de nodo instruye la continuación a una ruta u otra.
- **`exec_node_logic()` [Exclusiva Bonus]**: Empleada por el executor para resolver los operadores lógicos devueltos por `parser_bonus.c`. Decide si avanzar (y ejecutar) el ramal derecho (`right`) del árbol analizando el `last_exit_code` obtenido de la ejecución del ramal izquierdo (`left`). Implementa el "cortocircuito" (ej. Un `||` no ejecuta su derecha si la izquierda dio éxito/0).
- **`exec_node_pipe()` [Mandatory/Bonus]ecutor)
Entra a recorrer el AST (`t_node`), realiza un fork si corresponde, enruta descriptores de archivos, y lanza binarios.
- **`execute_command_tree()`**: Raíz de la ejecución. Desata la gestión de heredocs, asignación de rutas y finalmente lanza la lectura del árbol.
- **`assign_fullpath_recursive()`**: Navega el árbol comprobando la variable de entorno `PATH` uniendo directorios hasta encontrar si una instrucción (por ejemplo `ls`) se encuentra alojada en el PC de manera válida.
- **`preprocess_heredocs()` / `process_heredoc()`**: Busca en todo el AST cualquier documento con el esquema `<<` _Heredoc_ para leer los inputs multi-líneas y escribirlos en una pipe o archivo temporal ANTES del resto de la ejecución.
- **`traverse_tree()`**: Función iterativa que camina sobre el árbol. Dependiendo del tipo de nodo, manda ejecutar.
- **`exec_node_logic()`**: Se encarga de evaluar si un comando era un `&&` o un `||` y decide avanzar en el árbol en base al código de salida (`last_exit_code`).
- **`exec_node_pipe()`**: Maneja la ejecución de pipelines:
  - Llama a **`setup_ignore_signals()`** ANTES del `fork()` para proteger el padre (la shell ignora Ctrl+C mientras espera a los hijos).
  - Llama a **`open_fork()`** para crear sub-procesos que se conectan mediante tuberías.
  - Una vez que el hijo está forkeado, llama a **`setup_child_signals()`** EN EL HIJO para restaurar `SIG_DFL`, permitiendo que Ctrl+C termine el proceso hijo normalmente.
  - Llama a **`wait_pipe()`** donde el padre espera a que los hijos terminen, ignorando cualquier Ctrl+C.
  - Después de que todos los procesos terminan, llama a **`setup_interactive_signals()`** para restaurar el handler `handle_sigint` del padre, permitiendo que la shell vuelva a responder a Ctrl+C.
  - Llamada a **`close_pipe()`** para limpiar los descriptores de archivo.

#### Caso especial: `export TEST=juan | grep TEST`
¿Por qué no se muestra TEST en el resultado de grep? Porque el pipe `|` fuerza que ambos lados se ejecuten en procesos hijos (subshells):

```text
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

El entorno (environment) de un proceso hijo nunca se propaga hacia arriba. `fork()` copia el estado del padre hacia el hijo, pero los cambios en el hijo no se transmiten al padre ni a sus hermanos. Por eso las variables `export`adas dentro de un pipeline no afectan a la shell padre.

- **`exec_node_cmd()`**: Nodo final u hoja del árbol. Determina si el comando debe correrse:
  - Vía **`exec_builtin_parent()`**: Si es un builtin que altera el entorno real (`cd`, `export`, `unset`, `exit`), debe ejecutarse en el "proceso padre" sin hacer un fork para asegurar persistencia.
  - Vía **`exec_external_child()`**: Para otros ejecutables o pipelines, realiza el mapeo final, aplica redirecciones con **`setup_redirections()`** usando `dup2`, y lanza _execve_ dentro de un sub-proceso hijo.

### 2.6. Señales y Limpieza

#### Manejo de Señales: Ciclo Completo en Tres Pasos

El manejo de Ctrl+C (y otras señales) requiere tres pasos claramente diferenciados durante la ejecución de un comando externo. Cada paso protege un aspecto diferente del flujo de control:

**PASO 1: `setup_ignore_signals()` ANTES del `fork()`** — *Proteger al padre*

Antes de crear un proceso hijo, el padre (la shell) llama a `setup_ignore_signals()` para instalar `SIG_IGN` en SIGINT y SIGQUIT. Esto significa que mientras el padre está esperando (`waitpid`) a que el hijo termine, el usuario puede pulsar Ctrl+C:
- Si el padre tuviera activo `handle_sigint`, ese handler correría en el padre: imprimiría un newline, llamaría a `rl_redisplay()`, etc. — Todo mientras el hijo sigue ejecutándose. Eso rompería la pantalla y el estado de readline.
- Con `SIG_IGN`, el padre simplemente ignora la señal.
- El kernel entrega la señal también al hijo (porque los procesos del mismo grupo de proceso reciben la misma señal), y el hijo la maneja normalmente con `SIG_DFL`, terminando correctamente.
- El padre recoge el estado del hijo via `waitpid()`.

**PASO 2: `setup_child_signals()` EN EL HIJO justo después del `fork()`** — *Restaurar comportamiento normal*

Cuando se hace `fork()`, el hijo hereda todos los handlers del padre — en este punto el hijo hereda `SIG_IGN`. Un programa ejecutado con `execve()` no puede recibir y manejar señales que están en `SIG_IGN`. Por eso el hijo debe restaurar `SIG_DFL` para SIGINT y SIGQUIT inmediatamente después de `fork()` y ANTES de llamar a `execve()`:
- Así el programa externo (p.ej. `cat`, `sleep`, `less`) se comporta normalmente ante Ctrl+C.
- Cuando el usuario pulsa Ctrl+C, el hijo recibe SIGINT con handler `SIG_DFL`, que termina el proceso estándar.

**PASO 3: `setup_interactive_signals()` DESPUÉS del `waitpid()`** — *Restaurar la shell*

Una vez el hijo ha terminado y el padre regresa de `waitpid()`, la shell vuelve al prompt interactivo. En este punto:
- El padre restaura el handler `handle_sigint` (vía `setup_interactive_signals()`) para que Ctrl+C vuelva a limpiar la línea de readline y mostrar un nuevo prompt.
- Sin este paso, Ctrl+C seguiría siendo ignorado por el padre, y el shell no respondería correctamente.

#### Resumen del Ciclo Completo

```
PARENT (interactive handler activo)
  │
  ├─ setup_ignore_signals()        ← padre inmune a Ctrl+C durante la espera
  │
  ├─ fork()
  │      │
  │      └─ CHILD: setup_child_signals()  ← restaura SIG_DFL
  │                exec_external_child()
  │                execve(...)            ← Ctrl+C termina el hijo, padre lo recibe via waitpid
  │
  ├─ waitpid()                     ← padre espera, ignorando señales
  │
  └─ setup_interactive_signals()   ← padre restaura handle_sigint para el próximo prompt
```

**La regla de bash que se está replicando:** El padre (shell) ignora Ctrl+C mientras espera a un hijo. El hijo muere normalmente con Ctrl+C. La shell continúa viva, recoge el estado de salida del hijo, y muestra un nuevo prompt listo para el siguiente comando.

#### Limpieza y Liberación de Recursos

- **`free_ast()`**: Libera todo el árbol sintáctico (nodos, listas de argumentos y redirecciones).
- **`free_tokens()`**: Libera la lista de tokens generada por el lexer.
- **`cleanup_child_process()`**: Limpia recursos específicos del proceso hijo ante terminación prematura (errores, señales).
- **`free_shell()`**: Libera la estructura principal `t_shell` incluyendo las listas de entorno, aliases, y cualquier otra estructura asociada.

---

## 3. Anexo: Funcionamiento del Globbing y Wildcards (`match_pattern`)

La expansión de wildcards (caracteres comodín como `*` y `?`) se realiza en la fase de validación de tokens mediante `expand_wildcards()`, que a su vez delega la lógica de validación a la función recursiva `match_pattern()`. Esta evalúa los strings letra por letra para determinar si un archivo local coincide con un patrón dado.

La función maneja de forma recursiva 6 casos fundamentales:

1. **El final perfecto (Éxito `1`)**: 
   `if (*pattern == '\0' && *str == '\0')`
   Ambos textos han llegado a su fin (`\0`) simultáneamente sin incompatibilidades previas. Significa que hubo coincidencia total.
   - *Ejemplo:* Terminaste de comprobar `"a"` contra `"a"` y ahora el paso final evalúa `pattern = ""` y `str = ""`.

2. **El comodín que espera texto imposible (Fallo `0`)**: 
   `if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')`
   El patrón requiere más caracteres después del `*`, pero el texto real (`str`) ya se acabó (es decir, está vacío). No puede coincidir.
   - *Ejemplo:* Buscas `pattern = "*c"` pero el texto se terminó antes de encontrar la 'c', resultando en `str = ""`.

3. **El comodín final absoluto (Éxito `1`)**: 
   `if (*pattern == '*' && *(pattern + 1) == '\0')`
   El patrón termina en `*`. Como el `*` absorbe cualquier cantidad de texto y no hay más requisitos detrás, todo el texto restante en `str` coincidirá automáticamente.
   - *Ejemplo:* Tienes `pattern = "*"` y el resto del texto a validar es `str = "cualquier_texto_largo.txt"`.

4. **Coincidencia exacta o Comodín de 1 carácter `?` (Avance paralelo)**: 
   `if (*pattern == '?' || *pattern == *str)`
   El carácter actual del patrón es idéntico al del texto, o es un comodín `?` (que acepta cualquier carácter individual). Se valida y se avanza simultáneamente 1 posición en ambos textos (`match_pattern(pattern + 1, str + 1)`).
   - *Ejemplo Exacto:* Si `pattern = "main.c"` y `str = "main.c"`. Como 'm' == 'm', avanza a evaluar `"ain.c"` contra `"ain.c"`.
   - *Ejemplo '?':* Si `pattern = "m?in.c"` y `str = "main.c"`. El `?` absorbe la 'a' y avanzan a evaluar `"in.c"` contra `"in.c"`.

5. **Bifurcaciones del Asterisco (Recursión Ramificada)**: 
   `if (*pattern == '*')`
   Al toparse con un `*` y existiendo todavía texto para procesar, el programa explora dos caminos paralelos usando recursividad combinada con OR (`||`):
   - **Camino A (El `*` actúa como vacío - 0 caracteres)**: Avanza el patrón pero ignora al `*` para el texto actual (`match_pattern(pattern + 1, str)`).
     - *Ejemplo de Éxito en Camino A (Asterisco obvia texto):* Si `pattern = "*hola"` y `str = "hola"`. El asterisco no necesita absorber nada porque la palabra ya está completa. Este camino avanzará a buscar `"hola"` dentro de `"hola"`, consiguiendo un éxito instantáneo (`1`) en la siguiente iteración. ¡Corta la evaluación del Camino B!
     - *Ejemplo de Fallo en Camino A:* Con `pattern = "*a"` y `str = "hola"`, este camino probará inmediatamente obviar el asterisco y buscar la `"a"` en `"hola"`. (Fallará al no coincidir la 'a' con la 'h', requiriendo evaluar el Camino B).
   - **Camino B (El `*` absorbe al menos 1 letra)**: El patrón se queda fijo en el `*`, pero se avanza 1 posición en el texto para consumirlo (`match_pattern(pattern, str + 1)`). Si el Camino A falla, el operador `||` obliga a la evaluación del Camino B.
     - *Ejemplo Camino B:* Con `pattern = "*a"` y `str = "hola"`, este camino mantendrá `"*a"` y avanzará el string a `"ola"`. Luego volverá a ramificarse recursivamente verificando la `"h"` eliminada, hasta llegar a evaluar `"*a"` contra `"a"`, momento donde el Camino A asociado a esa iteración dará éxito.

6. **Desajuste (Fallo por defecto `0`)**: 
   `return (0);`
   Se alcanza si los caracteres comparados son diferentes y no hay comodines en juego en esa posición, devolviendo que la ruta evaluada es un fracaso.
   - *Ejemplo:* Evaluando `pattern = "b"` contra `str = "a"`. Ambos son distintos y ninguno es un comodín.
