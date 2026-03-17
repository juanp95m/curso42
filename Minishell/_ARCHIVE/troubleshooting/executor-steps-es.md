# Pasos del Executor: Entendiendo la Ejecución de Comandos en Minishell

El executor es el corazón de cualquier shell, responsable de tomar los comandos parseados y darles vida. Este documento desglosa el intrincado proceso de ejecución de comandos, enfocándose en comandos externos, built-ins, redirección de E/S, y el papel crucial de los pipes.

## 1. Visión General del Flujo de Ejecución

Después de que el usuario escribe un comando y presiona Enter, Minishell pasa por varias fases:

1.  **Lexing:** La cadena de entrada se descompone en tokens significativos (palabras, operadores como `<`, `>`, `|`).
2.  **Parsing:** Estos tokens se estructuran en uno o más objetos `t_command`, representando comandos simples, pipelines y redirecciones.
3.  **Ejecución:** El executor toma estas estructuras `t_command` y realiza las llamadas al sistema necesarias para ejecutar los comandos, gestionar la E/S y manejar los procesos.

El executor debe distinguir entre:
*   **Comandos Built-in:** Comandos manejados directamente por el proceso del shell (ej., `cd`, `echo`).
*   **Comandos Externos:** Programas ubicados en el sistema de archivos (ej., `/bin/ls`, `/usr/bin/grep`). Estos requieren la creación de nuevos procesos.

## 2. Comandos Built-in

Los comandos built-in son funciones compiladas directamente en el ejecutable del shell. Se ejecutan dentro del proceso propio del shell.

**Características:**

*   **Normalmente sin `fork()`:** Generalmente no requieren crear un nuevo proceso hijo. Esto los hace más rápidos y eficientes.
*   **Modifican directamente el estado del shell:** Built-ins como `cd`, `export`, `unset` pueden cambiar el directorio de trabajo actual del shell o las variables de entorno. Un comando `cd` externo (si existiera) solo cambiaría el directorio de su proceso hijo, no el del shell.
*   **Redirección de E/S:** Aunque no hacen `fork`, los built-ins respetan las redirecciones de E/S. Sus flujos de entrada/salida estándar pueden cambiarse usando `dup2()`, pero estos cambios deben revertirse cuidadosamente después para evitar afectar operaciones posteriores del shell.

**Ejemplos en Minishell:**
`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

**Proceso de Ejecución para Built-ins:**

1.  Identificar si el comando es un built-in.
2.  Si lo es, guardar el `STDIN_FILENO` y `STDOUT_FILENO` actuales con `dup()` para poder restaurarlos después.
   `tmp_stdin = dup(STDIN_FILENO); tmp_stdout = dup(STDOUT_FILENO);`
3.  Aplicar cualquier redirección de E/S (usando `dup2()`).
   `dup2(fd_input_file, STDIN_FILENO); dup2(fd_output_file, STDOUT_FILENO);`
4.  Llamar a la función built-in correspondiente (ej., `ft_cd(args)`).
5.  Restaurar los `STDIN_FILENO` y `STDOUT_FILENO` originales (usando `dup2()` con los FDs guardados).
   `dup2(tmp_stdin, STDIN_FILENO); dup2(tmp_stdout, STDOUT_FILENO);`
7.  Establecer el estado de salida del shell.

## 3. Comandos Externos

Los comandos externos son programas ejecutables que se encuentran en la ruta de archivos del sistema. Ejecutarlos implica una serie de llamadas al sistema cruciales.

**La Tríada `fork`-`execve`-`waitpid`:**

Este es el patrón fundamental para ejecutar programas externos.

### `fork()`: Creando un Proceso Hijo

`pid_t fork(void);`

*   **Propósito:** Crea un nuevo proceso que es una copia casi exacta del proceso que lo llama (el padre).
*   **Valor de Retorno:**
    *   **En el padre:** Devuelve el ID de Proceso (PID) del nuevo proceso hijo.
    *   **En el hijo:** Devuelve `0`.
    *   **En caso de error:** Devuelve `-1`.

**Diagrama Conceptual:**

```
  Proceso Padre (Shell)
         |
         |  fork()
         V
  +-----------------+-----------------+
  |                 |                 |
  | Padre Continúa  | Proceso Hijo    |
  | (ej., espera)   | (copia del padre)|
  | PID = child_pid | PID = 0         |
  +-----------------+-----------------+
```

Después de `fork()`, tanto el proceso padre como el hijo se ejecutan concurrentemente, comenzando desde la línea inmediatamente después de la llamada a `fork()`. Tienen espacios de memoria separados.

### `execve()`: Reemplazando la Imagen del Hijo

`int execve(const char *pathname, char *const argv[], char *const envp[]);`

*   **Propósito:** Reemplaza la imagen del proceso actual con una nueva imagen de proceso especificada por `pathname`. Esto significa que el código, datos y pila del proceso que lo llama son sobrescritos.
*   **`pathname`:** La ruta al archivo ejecutable (ej., `/bin/ls`).
*   **`argv`:** Un array de cadenas representando los argumentos de línea de comandos para el nuevo programa (ej., `{"ls", "-l", NULL}`).
*   **`envp`:** Un array de cadenas representando las variables de entorno para el nuevo programa (ej., `{"PATH=/usr/bin:/bin", "USER=malj", NULL}`).
*   **Valor de Retorno:** `execve()` *solo retorna si ocurre un error*. Si tiene éxito, el nuevo programa comienza su ejecución desde su función `main()`.

**Encontrando `pathname` (Resolución de PATH):**
Si `pathname` no es una ruta absoluta (no comienza con `/`), el shell busca el ejecutable en los directorios listados en la variable de entorno `PATH`.

**Diagrama Conceptual (dentro del proceso hijo):**

```
  Proceso Hijo (copia del Shell)
         |
         |  Redirecciones de E/S (dup2)
         |
         |  execve("/bin/ls", {"ls", "-l"}, envp)
         V
  +-----------------+
  |                 |
  |  Nuevo Proceso  |
  |  (ej., 'ls -l') |
  |                 |
  +-----------------+
  (La imagen original del proceso hijo ya no existe)
```

### `waitpid()`: El Padre Esperando al Hijo

`pid_t waitpid(pid_t pid, int *wstatus, int options);`

*   **Propósito:** El proceso padre usa `waitpid()` para esperar a que un proceso hijo específico (`pid`) cambie de estado (ej., termine, se detenga o se reanude).
*   **`pid`:**
    *   `> 0`: Esperar al hijo con el PID especificado.
    *   `-1`: Esperar a cualquier proceso hijo.
    *   `0`: Esperar a cualquier proceso hijo en el mismo grupo de procesos que el llamante.
*   **`wstatus`:** Un puntero a un entero donde se almacena información sobre el estado de terminación del hijo. Se usan macros como `WIFEXITED()`, `WEXITSTATUS()`, `WIFSIGNALED()`, `WTERMSIG()` para interpretar este valor.
*   **`options`:** `WNOHANG` (no bloquear), `WUNTRACED` (retornar si el hijo está detenido).

**Diagrama Conceptual:**

```
  Proceso Padre (Shell)           Proceso Hijo (ls -l)
         |                                |
         | fork()                         |
         |--------------------------------|
         |                                |
         | waitpid(child_pid, &status, 0) | (ejecuta 'ls -l')
         | (bloqueado)                    |
         |                                |
         |                                |
         |                                | (termina)
         |<-------------------------------|
         | (desbloqueado)                 |
         |                                |
         | Interpreta status              |
```

## 4. Redirección de E/S

Un shell permite a los usuarios cambiar de dónde un comando lee su entrada (stdin) o hacia dónde envía su salida (stdout, stderr). Esto se gestiona usando descriptores de archivo y la llamada al sistema `dup2()`.

### Descriptores de Archivo (FDs)

En sistemas tipo Unix, todo es un archivo. Esto incluye dispositivos, sockets y pipes. Cuando un proceso abre un archivo o crea un pipe, obtiene un entero pequeño llamado descriptor de archivo.

*   `0`: **STDIN_FILENO** (Entrada Estándar) - Por defecto: teclado.
*   `1`: **STDOUT_FILENO** (Salida Estándar) - Por defecto: pantalla del terminal.
*   `2`: **STDERR_FILENO** (Error Estándar) - Por defecto: pantalla del terminal.

### Llamadas al Sistema `dup()` y `dup2()`

Estas funciones se usan para duplicar descriptores de archivo, permitiendo efectivamente redirigir la E/S.

#### `int dup(int oldfd);`
*   **Propósito:** Crea un *nuevo* descriptor de archivo que se refiere a la misma descripción de archivo abierto que `oldfd`. El nuevo FD será el número más bajo disponible. Normalmente se usa cuando quieres guardar una copia de un FD existente antes de redirigirlo. En este proyecto, dup se usa en los comandos built-in para guardar el STDIN y STDOUT originales antes de aplicar redirecciones, para poder restaurarlos después. ¿Por qué solo en built-ins? Porque los built-ins se ejecutan en el proceso del shell mismo, así que necesitan restaurar los FDs originales después de la ejecución. Los comandos externos se ejecutan en procesos hijos, así que no necesitan restaurar FDs ya que el proceso hijo será reemplazado por `execve()`.
*   **Ejemplo:** `new_fd = dup(old_fd);`

#### `int dup2(int oldfd, int newfd);`
*   **Propósito:** Duplica `oldfd` en `newfd`. Si `newfd` ya está abierto, primero se cierra. Luego `newfd` se hace referir a la misma descripción de archivo abierto que `oldfd`.
*   **Clave para la Redirección:** Esta es la función principal para la redirección porque puedes forzar a que un archivo específico (ej., `output.txt`) se convierta en `STDIN_FILENO`, `STDOUT_FILENO` o `STDERR_FILENO`.

**Diagrama Conceptual de `dup2(fd_file, STDOUT_FILENO)`:**

```
ANTES de dup2:
  Tabla de FD del Proceso:
  0 (STDIN)  -> Teclado
  1 (STDOUT) -> Pantalla del Terminal
  2 (STDERR) -> Pantalla del Terminal
  3 (fd_file)-> "output.txt" (abierto para escritura)

DESPUÉS de dup2(fd_file, STDOUT_FILENO):
  Tabla de FD del Proceso:
  0 (STDIN)  -> Teclado
  1 (STDOUT) -> "output.txt"  <-- ¡Ahora apunta al archivo!
  2 (STDERR) -> Pantalla del Terminal
  3 (fd_file)-> "output.txt"  <-- El FD antiguo del archivo sigue existiendo,
                                   debe cerrarse si ya no se necesita.
```

### Tipos de Redirección e Implementación:

**Pasos Generales para cualquier Redirección:**

1.  Abrir el archivo destino (llamada al sistema `open()`).
2.  Si es una redirección de entrada (`<`), `dup2(fd_file, STDIN_FILENO)`.
3.  Si es una redirección de salida (`>` o `>>`), `dup2(fd_file, STDOUT_FILENO)`.
4.  Cerrar el descriptor de archivo original del archivo (`close(fd_file)`). Ya no se necesita porque `STDIN_FILENO`/`STDOUT_FILENO` ahora apuntan a él.

#### `<` (Redirección de Entrada)
`command < input.txt`

*   Abre `input.txt` para lectura.
*   Hace que `STDIN_FILENO` (0) apunte a `input.txt`.

**Ejemplo de Código (Conceptual, dentro del hijo antes de `execve`):**
```c
int fd_in = open("input.txt", O_RDONLY);
if (fd_in == -1) { /* manejo de error */ }
dup2(fd_in, STDIN_FILENO); // Redirigir stdin a input.txt
close(fd_in);             // Cerrar fd_in original (fd_in == STDIN_FILENO ahora)
// execve(...)
```

#### `>` (Redirección de Salida - Truncar)
`command > output.txt`

*   Abre `output.txt` para escritura, creándolo si no existe, y truncándolo si existe.
*   Hace que `STDOUT_FILENO` (1) apunte a `output.txt`.

**Ejemplo de Código:**
```c
int fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd_out == -1) { /* manejo de error */ }
dup2(fd_out, STDOUT_FILENO); // Redirigir stdout a output.txt
close(fd_out);
// execve(...)
```

#### `>>` (Redirección de Salida - Añadir)
`command >> append.txt`

*   Abre `append.txt` para escritura, creándolo si no existe, y añadiendo al final si existe.
*   Hace que `STDOUT_FILENO` (1) apunte a `append.txt`.

**Ejemplo de Código:**
```c
int fd_append = open("append.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
if (fd_append == -1) { /* manejo de error */ }
dup2(fd_append, STDOUT_FILENO); // Redirigir stdout a append.txt
close(fd_append);
// execve(...)
```

#### `2>` (Redirección de Error Estándar)
`command 2> error.log`

*   Similar a `>` pero redirige `STDERR_FILENO` (2).

**Ejemplo de Código:**
```c
int fd_err = open("error.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd_err == -1) { /* manejo de error */ }
dup2(fd_err, STDERR_FILENO); // Redirigir stderr a error.log
close(fd_err);
// execve(...)
```
También puedes redirigir `stderr` a `stdout` usando `2>&1`. Esto implica `dup2(STDOUT_FILENO, STDERR_FILENO);`.

### Ejercicio Ejemplo: Redirección

**Comando:** `echo "Hello World" > output.txt`
**Pasos:**
1.  El shell hace fork.
2.  Proceso hijo:
    a.  Abre `output.txt` en modo `O_WRONLY | O_CREAT | O_TRUNC`. Digamos que `fd_out = 3`.
    b.  `dup2(3, 1)` (redirige `STDOUT_FILENO` a `output.txt`).
    c.  Cierra `fd_out` (3).
    d.  `execve("/bin/echo", {"echo", "Hello World"}, envp)`.
3.  El comando `echo` escribe "Hello World" en su `STDOUT_FILENO`, que ahora es `output.txt`.
4.  El proceso padre espera al hijo.

## 5. Pipes (`|`)

Los pipes son una forma de comunicación entre procesos (IPC) que permite que la salida de un comando se use como la entrada de otro. `command1 | command2`

### ¿Qué son los Pipes?

Un pipe es un canal de datos unidireccional. Los datos escritos en un extremo del pipe pueden leerse desde el otro extremo.

### Llamada al Sistema `pipe()`

`int pipe(int pipefd[2]);`

*   **Propósito:** Crea un pipe y devuelve dos descriptores de archivo en el array `pipefd`:
    *   `pipefd[0]`: El extremo de lectura del pipe.
    *   `pipefd[1]`: El extremo de escritura del pipe.
*   **Valor de Retorno:** `0` en caso de éxito, `-1` en caso de error.

**Diagrama Conceptual de `pipe()`:**

```
pipefd[0] <--- LEER DEL PIPE ---|-----|--- ESCRIBIR EN PIPE ---> pipefd[1]
                                Buffer del Pipe
```

### Conectando Comandos con Pipes

Para un pipeline como `cmd1 | cmd2 | cmd3`, necesitas un par de pipes entre cada comando.

**Pasos de Ejecución para `command1 | command2`:**

1.  **Crear un pipe:** El shell padre llama a `pipe(pipefd)`.
    *   `pipefd[0]` (extremo de lectura)
    *   `pipefd[1]` (extremo de escritura)
2.  **Fork para `command1`:**
    *   **Hijo 1 (para `command1`):**
        *   Cierra `pipefd[0]` (extremo de lectura, ya que `command1` solo escribe en el pipe).
        *   `dup2(pipefd[1], STDOUT_FILENO)`: Redirige el `stdout` de `command1` al extremo de escritura del pipe.
        *   Cierra `pipefd[1]`.
        *   Aplica cualquier otra redirección para `command1`.
        *   `execve("command1", ...)`.
    *   **Padre:** No cierra nada aún. Hará fork de nuevo para `command2`.
3.  **Fork para `command2`:**
    *   **Hijo 2 (para `command2`):**
        *   Cierra `pipefd[1]` (extremo de escritura, ya que `command2` solo lee del pipe).
        *   `dup2(pipefd[0], STDIN_FILENO)`: Redirige el `stdin` de `command2` al extremo de lectura del pipe.
        *   Cierra `pipefd[0]`.
        *   Aplica cualquier otra redirección para `command2`.
        *   `execve("command2", ...)`.
    *   **Padre:** Ahora, el padre ha hecho fork de ambos hijos. Debe `close(pipefd[0])` y `close(pipefd[1])` para asegurar que el pipe se gestione correctamente. Si el padre mantiene los extremos del pipe abiertos, los hijos podrían no recibir EOF correctamente.
4.  **El padre llama a `waitpid()` para ambos hijos.**

**Diagrama Conceptual: `cmd1 | cmd2`**

```
                       pipefd[0] <--- EXTREMO DE LECTURA
                       pipefd[1] ---> EXTREMO DE ESCRITURA

        Proceso Shell
             |
             | pipe() (crea pipefd[0], pipefd[1])
             |
             | fork() para cmd1
             +--------------------+---------------------+
             | Hijo 1 (para cmd1) |     Shell Padre     |
             |--------------------|                     |
             | close(pipefd[0])   |  fork() para cmd2   |
             | dup2(pipefd[1], 1) |---------------------+-------------------+
             | close(pipefd[1])   | Hijo 2 (para cmd2)  |   Shell Padre     |
             | (execve cmd1)      |---------------------|                   |
             |                    | close(pipefd[1])    | close(pipefd[0])  |
             |                    | dup2(pipefd[0], 0)  | close(pipefd[1])  |
             |                    | close(pipefd[0])    | waitpid(hijo1)    |
             |                    | (execve cmd2)       | waitpid(hijo2)    |
             |                    |                     |                   |
             V                    V                     V                   V
      cmd1 escribe en pipe      cmd2 lee del pipe       Shell continúa
```

### Ejercicio Ejemplo: Pipe

**Comando:** `ls -l | grep "minishell"`
**Pasos:**
1.  El shell crea un pipe: `pipefd[0]` (lectura), `pipefd[1]` (escritura).
2.  El shell hace fork para `ls -l`.
    a.  Hijo (LS): Cierra `pipefd[0]`. `dup2(pipefd[1], STDOUT_FILENO)`. Cierra `pipefd[1]`. `execve("/bin/ls", {"ls", "-l"}, envp)`.
3.  El shell hace fork para `grep "minishell"`.
    a.  Hijo (GREP): Cierra `pipefd[1]`. `dup2(pipefd[0], STDIN_FILENO)`. Cierra `pipefd[0]`. `execve("/bin/grep", {"grep", "minishell"}, envp)`.
4.  Padre: Cierra `pipefd[0]` y `pipefd[1]`. Espera a ambos hijos.
5.  `ls -l` escribe su salida en el pipe. `grep "minishell"` lee del pipe y filtra las líneas, imprimiendo las que coinciden en su `STDOUT_FILENO` (que sigue siendo el terminal).

## 6. Combinando Redirecciones y Pipes

Cuando un comando tiene tanto redirecciones como es parte de un pipeline, las redirecciones se aplican *después* de la conexión del pipe. Esto significa que una redirección sobrescribirá la entrada/salida estándar del pipe.

**Ejemplo:** `cat < in.txt | grep "word" > out.txt`

1.  `cat < in.txt`: El `stdin` de `cat` viene de `in.txt`. Su `stdout` va al pipe.
2.  `grep "word" > out.txt`: El `stdin` de `grep` viene del pipe. Su `stdout` va a `out.txt`.

**Orden de Operaciones (dentro de un proceso hijo):**
1.  Cerrar extremos no usados del pipe.
2.  `dup2()` para conexiones de pipe (ej., `dup2(pipe_read_end, STDIN_FILENO)` para el lado derecho de un pipe).
3.  Aplicar redirecciones explícitas de archivo (ej., `dup2(fd_input_file, STDIN_FILENO)`). Esto sobrescribirá el `dup2` del pipe si ambos están presentes para `STDIN`.
4.  Cerrar cualquier descriptor de archivo original restante.
5.  `execve()`.

## 7. Manejo de Errores y Estado de Salida

Un manejo robusto de errores es crítico para un shell.

*   **Comprobar Valores de Retorno:** Siempre comprueba los valores de retorno de las llamadas al sistema (`fork`, `pipe`, `open`, `dup2`, `execve`). Si una llamada falla, `perror()` puede imprimir un mensaje de error descriptivo.
*   **Estado de Salida del Proceso Hijo:** Cuando un proceso hijo termina, su estado de salida se pasa de vuelta al padre via `waitpid()`.
    *   `WIFEXITED(status)`: Verdadero si el hijo salió normalmente.
    *   `WEXITSTATUS(status)`: El código de salida real (0 para éxito, distinto de cero para error).
    *   `WIFSIGNALED(status)`: Verdadero si el hijo fue terminado por una señal.
    *   `WTERMSIG(status)`: El número de señal que terminó al hijo.
*   **Variable de Estado de Salida del Shell `($?)`:** El shell almacena el estado de salida del último comando en primer plano en la variable especial `$?`. Tu shell debe actualizar esto después de cada ejecución de comando.

## 8. Consejos de Aprendizaje Visual

Entender la creación de procesos, descriptores de archivo y pipes puede ser abstracto.

*   **Dibuja Diagramas:** Siempre dibuja las tablas de descriptores de archivo para el padre y cada proceso hijo, y cómo `dup2()` las cambia. Dibuja los pipes como conexiones físicas.
*   **Usa `strace`:** El comando `strace` (en Linux) es una herramienta invaluable. Rastrea las llamadas al sistema hechas por un proceso.
    *   `strace -f -o output.txt minishell` ejecutará tu shell y registrará todas las llamadas al sistema (incluyendo las de los hijos forkeados gracias a `-f`). Analiza `output.txt` para ver las llamadas a `fork`, `pipe`, `open`, `dup2`, `execve`, `waitpid` en acción.
    *   `strace -e open,dup2,pipe,fork,execve ls -l | grep "minishell"`: Puedes filtrar `strace` para mostrar solo llamadas al sistema específicas para un comando.

Trabajando diligentemente estos pasos y utilizando ayudas visuales y herramientas de depuración, obtendrás una comprensión profunda de cómo tu Minishell ejecuta comandos.

Por ejemplo:
```
$ strace -f -e open,dup2,pipe,fork,execve ls -l | grep "minishell"
```

```
open("/bin/ls", O_RDONLY) = 3 
pipe([4, 5]) = 0 
fork() = 12345 (child process) 
[Child Process] 
dup2(5, 1) = 1 
close(4) 
close(5) 
execve("/bin/ls", ["ls", "-l"], envp) = 0 
[Parent Process] close(5) waitpid(12345, &status, 0) = 12345
close(5) 
waitpid(12345, &status, 0) = 12345
```
Esta salida muestra al proceso padre creando un pipe, forkeando un hijo, el hijo redirigiendo su `stdout` al pipe, y ejecutando `ls -l`. El padre espera a que el hijo termine.


## Ejemplos Mínimos para entender Pipes

**Ejemplo 1: `ls -l | grep "minishell"`**
1.  El shell crea un pipe: `pipefd[0]` (lectura), `pipefd[1]` (escritura).
2.  El shell hace fork para `ls -l`.
3.  Hijo (LS): Cierra `pipefd[0]`. `dup2(pipefd[1], STDOUT_FILENO)`. Cierra `pipefd[1]`. `execve("/bin/ls", {"ls", "-l"}, envp)`.
4.  El shell hace fork para `grep "minishell"`.
5.  Hijo (GREP): Cierra `pipefd[1]`. `dup2(pipefd[0], STDIN_FILENO)`.
6.  Cierra `pipefd[0]`. `execve("/bin/grep", {"grep", "minishell"}, envp)`.
7.  Padre: Cierra `pipefd[0]` y `pipefd[1]`. Espera a ambos hijos.

**Ejemplo 2: `cat < in.txt | grep "word" > out.txt`**
1. El shell crea un pipe: `pipefd[0]` (lectura), `pipefd[1]` (escritura).
2. El shell hace fork para `cat < in.txt`.
3. Hijo (CAT): Abre `in.txt`, `dup2(fd_in, STDIN_FILENO)`, cierra `fd_in`. Cierra `pipefd[0]`. `dup2(pipefd[1], STDOUT_FILENO)`. Cierra `pipefd[1]`. Ejecuta `cat`.
4. El shell hace fork para `grep "word" > out.txt`.
5. Hijo (GREP): Abre `out.txt`, `dup2(fd_out, STDOUT_FILENO)`, cierra `fd_out`. Cierra `pipefd[1]`. `dup2(pipefd[0], STDIN_FILENO)`. Cierra `pipefd[0]`. Ejecuta `grep`.
6. Padre: Cierra ambos extremos del pipe y espera a los hijos.

**Ejemplo 3: `echo "Hello World" > output.txt`**
1. El shell hace fork para `echo`.
2. Hijo (ECHO): Abre `output.txt` en modo escritura, `dup2(fd_out, STDOUT_FILENO)`, cierra `fd_out`. Ejecuta `echo`.
3. El padre espera al hijo.


# Ejercicios para entender Pipes y Redirecciones

Estos son programas C independientes que puedes compilar y ejecutar para construir intuición sobre cómo `pipe()`, `fork()` y `dup2()` trabajan juntos.

## Ejercicio 1: Pipe básico — el padre escribe, el hijo lee

El pipe más simple posible: el padre envía una cadena a través del pipe, y el hijo la lee e imprime.

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid;
    char    buf[100];

    pipe(pipefd);               // pipefd[0] = extremo lectura, pipefd[1] = extremo escritura
    pid = fork();
    if (pid == 0)               // HIJO: lee del pipe
    {
        close(pipefd[1]);       // cerrar extremo de escritura (el hijo solo lee)
        read(pipefd[0], buf, sizeof(buf));
        printf("Hijo recibió: %s\n", buf);
        close(pipefd[0]);
    }
    else                        // PADRE: escribe en el pipe
    {
        close(pipefd[0]);       // cerrar extremo de lectura (el padre solo escribe)
        write(pipefd[1], "hola desde el padre", 20);
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex1 ex1.c && ./ex1`

**Qué observar:**
- El hijo imprime `hola desde el padre` aunque no hubo ningún archivo involucrado — los datos viajaron a través del pipe en memoria.
- Cada lado cierra el extremo que no usa. Esto es **crítico** — si el hijo no cierra el extremo de escritura, `read()` nunca recibirá EOF.

---

## Ejercicio 2: Pipe + `dup2` — redirigir stdout al pipe

Ahora hacemos que el hijo redirija su `stdout` al pipe, para que el padre pueda capturar lo que el hijo "imprime".

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid;
    char    buf[100];
    int     n;

    pipe(pipefd);
    pid = fork();
    if (pid == 0)               // HIJO: redirigir stdout → pipe, luego escribir
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);  // stdout ahora va al pipe
        close(pipefd[1]);
        printf("¡Soy el hijo!\n");       // esto va al pipe, no al terminal
    }
    else                        // PADRE: leer del pipe
    {
        close(pipefd[1]);
        n = read(pipefd[0], buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Padre capturó: %s", buf);
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex2 ex2.c && ./ex2`

**Qué observar:**
- El `printf` del hijo no aparece en el terminal — va al pipe.
- El padre lo lee e imprime `Padre capturó: ¡Soy el hijo!`.
- Esto es exactamente lo que pasa en `cmd1 | cmd2`: el stdout de cmd1 se redirige al pipe.

---

## Ejercicio 3: Simulando `ls | grep` con `execve`

Esto es lo real — dos procesos hijos conectados por un pipe, cada uno reemplazado por un programa externo via `execve`.

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid1;
    pid_t   pid2;

    pipe(pipefd);

    // --- Hijo 1: ejecuta "ls -l", stdout → pipe ---
    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]);                        // no necesita extremo de lectura
        dup2(pipefd[1], STDOUT_FILENO);          // stdout → pipe
        close(pipefd[1]);
        char *argv[] = {"ls", "-l", NULL};
        char *envp[] = {NULL};
        execve("/bin/ls", argv, envp);
        perror("execve ls");                     // solo se alcanza si hay error
    }

    // --- Hijo 2: ejecuta "grep Makefile", stdin ← pipe ---
    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]);                        // no necesita extremo de escritura
        dup2(pipefd[0], STDIN_FILENO);           // stdin ← pipe
        close(pipefd[0]);
        char *argv[] = {"grep", "Makefile", NULL};
        char *envp[] = {NULL};
        execve("/usr/bin/grep", argv, envp);
        perror("execve grep");
    }

    // --- Padre: cerrar ambos extremos y esperar ---
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex3 ex3.c && ./ex3`

**Qué observar:**
- La salida es la misma que ejecutar `ls -l | grep Makefile` en bash.
- El padre **debe** cerrar ambos extremos del pipe — de lo contrario `grep` nunca recibe EOF y se cuelga para siempre.
- Cada hijo cierra el extremo del pipe que no usa **antes** de llamar a `execve`.

---

---

## Ejercicio 4: Redirección de salida `>` — escribir en un archivo (truncar)

Simula `echo "Hello World" > output.txt`. El hijo redirige su stdout a un archivo, luego ejecuta un comando que escribe en stdout.

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    pid = fork();
    if (pid == 0)               // HIJO
    {
        int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (perror("open"), 1);
        dup2(fd, STDOUT_FILENO);    // stdout → output.txt
        close(fd);
        char *argv[] = {"echo", "Hello World", NULL};
        char *envp[] = {NULL};
        execve("/bin/echo", argv, envp);
        perror("execve");
    }
    else                        // PADRE
        waitpid(pid, NULL, 0);
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex4 ex4.c && ./ex4 && cat output.txt`

**Qué observar:**
- Nada se imprime en el terminal — la salida fue a `output.txt`.
- `cat output.txt` muestra `Hello World`.
- `O_TRUNC` significa que el archivo se vacía primero. Ejecútalo dos veces — el archivo siempre tiene exactamente una línea.

---

## Ejercicio 5: Redirección de añadir `>>` — escribir en un archivo (añadir)

Simula `echo "line N" >> log.txt`. Igual que el Ejercicio 4 pero con `O_APPEND` en vez de `O_TRUNC`.

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    pid = fork();
    if (pid == 0)               // HIJO
    {
        int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (perror("open"), 1);
        dup2(fd, STDOUT_FILENO);    // stdout → log.txt (añadir)
        close(fd);
        char *argv[] = {"echo", "otra línea", NULL};
        char *envp[] = {NULL};
        execve("/bin/echo", argv, envp);
        perror("execve");
    }
    else                        // PADRE
        waitpid(pid, NULL, 0);
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex5 ex5.c && ./ex5 && ./ex5 && ./ex5 && cat log.txt`

**Qué observar:**
- Ejecútalo varias veces — cada ejecución **añade** una línea en vez de sobrescribir el archivo.
- `cat log.txt` muestra tres líneas de `otra línea`.
- La única diferencia con el Ejercicio 4 es `O_APPEND` vs `O_TRUNC`.

---

## Ejercicio 6: Heredoc `<<` — alimentar texto en línea como stdin

Simula `cat << EOF`. El padre escribe texto literal en un pipe, y el hijo lo lee como stdin. Así es como un shell implementa heredocs sin archivos temporales.

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int     pipefd[2];
    pid_t   pid;

    // El contenido del "heredoc" — lo que el usuario escribiría entre << EOF y EOF
    char *heredoc = "primera línea\nsegunda línea\ntercera línea\n";

    pipe(pipefd);
    pid = fork();
    if (pid == 0)               // HIJO: stdin ← pipe, luego ejecutar cat
    {
        close(pipefd[1]);                       // no necesita extremo de escritura
        dup2(pipefd[0], STDIN_FILENO);          // stdin ← pipe
        close(pipefd[0]);
        char *argv[] = {"cat", NULL};
        char *envp[] = {NULL};
        execve("/bin/cat", argv, envp);
        perror("execve");
    }
    else                        // PADRE: escribir contenido heredoc en el pipe
    {
        close(pipefd[0]);                       // no necesita extremo de lectura
        write(pipefd[1], heredoc, strlen(heredoc));
        close(pipefd[1]);                       // señalar EOF al hijo
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex6 ex6.c && ./ex6`

**Qué observar:**
- `cat` imprime las tres líneas en el terminal, aunque no existe ningún archivo — los datos vinieron del pipe.
- El padre escribe el contenido del heredoc en el pipe y luego **cierra** el extremo de escritura — esto envía EOF para que `cat` sepa cuándo parar.
- Así es exactamente como minishell puede implementar `<< DELIMITADOR`: leer líneas del usuario hasta `DELIMITADOR`, escribirlas en un pipe, y conectar el pipe al stdin del comando.

---

## Ejercicio 7: Heredoc interactivo `<<` — leer del usuario hasta el delimitador

Esto es lo real. Simula `cat << EOF` exactamente como bash: pide al usuario entrada línea por línea, se detiene cuando se escribe el delimitador, y alimenta todo al stdin del comando.

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Lee líneas del usuario hasta que se escribe `delimiter`, las escribe en write_fd
void	read_heredoc(int write_fd, const char *delimiter)
{
    char	*line;
    size_t	len;
    ssize_t	nread;

    line = NULL;
    len = 0;
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);          // prompt, igual que bash
        nread = getline(&line, &len, stdin);
        if (nread == -1)                        // Ctrl+D (EOF)
            break ;
        // Eliminar salto de línea final para comparación
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';
        if (strcmp(line, delimiter) == 0)        // delimitador encontrado → parar
            break ;
        // Restaurar el salto de línea y escribir al pipe
        line[strlen(line)] = '\n';
        write(write_fd, line, strlen(line) + 1);
    }
    free(line);
}

int main(void)
{
    int     pipefd[2];
    pid_t   pid;
    char    *delimiter;

    delimiter = "EOF";                          // cambia esto para probar otros delimitadores
    printf("heredoc> Escribe líneas, luego escribe '%s' para terminar:\n", delimiter);

    pipe(pipefd);

    // Leer toda la entrada del heredoc ANTES de hacer fork (como hace bash)
    read_heredoc(pipefd[1], delimiter);
    close(pipefd[1]);                           // terminamos de escribir → enviar EOF al pipe

    pid = fork();
    if (pid == 0)               // HIJO: stdin ← pipe, luego ejecutar cat
    {
        close(pipefd[1]);                       // ya cerrado, pero buena costumbre
        dup2(pipefd[0], STDIN_FILENO);          // stdin ← pipe
        close(pipefd[0]);
        char *argv[] = {"cat", "-n", NULL};     // -n para numerar líneas
        char *envp[] = {NULL};
        execve("/bin/cat", argv, envp);
        perror("execve");
    }
    else                        // PADRE
    {
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}
```

Compilar y ejecutar: `gcc -o ex7 ex7.c && ./ex7`

**Sesión de ejemplo:**
```
heredoc> Escribe líneas, luego escribe 'EOF' para terminar:
> hola mundo
> esto es un heredoc
> igual que en bash
> EOF
     1	hola mundo
     2	esto es un heredoc
     3	igual que en bash
```

**Qué observar:**
- El programa muestra `> ` por cada línea, igual que hace bash con los heredocs.
- Cuando escribes `EOF` (el delimitador), la entrada se detiene y `cat -n` imprime todas las líneas recopiladas con números de línea.
- Presionar `Ctrl+D` en vez de escribir el delimitador también detiene la entrada (EOF en stdin).
- El heredoc se lee **antes** de hacer fork — esto es importante porque en minishell, si tienes múltiples heredocs, todos deben recopilarse antes de que cualquier comando se ejecute.
- La idea clave: un heredoc es simplemente un pipe donde el **shell mismo** es el escritor en vez de otro comando.

---

### Puntos clave de los ejercicios

| Regla | Por qué |
|---|---|
| Siempre cerrar extremos de pipe no usados | De lo contrario `read()` se bloquea para siempre esperando EOF |
| `dup2` antes de `execve` | El nuevo programa hereda los FDs redirigidos |
| El padre cierra ambos extremos después de hacer fork | El padre no es parte del flujo de datos |
| `waitpid` por cada hijo | Evitar procesos zombie |
| `O_TRUNC` para `>`, `O_APPEND` para `>>` | La única diferencia entre redirección truncar y añadir |
| Heredoc usa un pipe, no un archivo | El padre escribe contenido → pipe → el hijo lee como stdin |



# Preguntas Frecuentes

**P: ¿Necesito cerrar uno de los pipes[0] o pipes[1] después de crearlo con `pipe()`?** Sí, deberías cerrar el extremo del pipe que no usas en cada proceso porque podría llevar a fugas de recursos y comportamiento no deseado. Por ejemplo, si un proceso hijo solo escribe en el pipe, debería cerrar el extremo de lectura (`pipes[0]`). Si un proceso hijo solo lee del pipe, debería cerrar el extremo de escritura (`pipes[1]`). Esto es importante porque si ambos extremos se dejan abiertos, el proceso lector nunca recibirá una señal EOF y se bloqueará indefinidamente.

**¿Pero qué pasa si dejo ambos abiertos hasta que cierre ambos después de usarlos?**
La regla es sobre extremos abiertos por proceso, no sobre el momento.
El kernel cuenta cuántos descriptores de archivo abiertos apuntan a cada extremo del pipe a través de todos los procesos. `read()` devuelve EOF solo cuando el conteo de referencias del extremo de escritura cae a cero — lo que significa que cada proceso que lo tenía abierto lo ha cerrado.

Qué pasa después de fork()
```
Después de pipe() + fork():

Padre tiene:  pipefd[0] (lectura),  pipefd[1] (escritura)
Hijo tiene:   pipefd[0] (lectura),  pipefd[1] (escritura)    ← copias heredadas

Conteo de referencias del extremo de escritura = 2  (padre + hijo)
```

Escenario: el hijo es el lector, pero no cierra pipefd[1]

```
Padre cierra pipefd[1]  →  refcount extremo escritura = 1 (el hijo aún lo tiene)
Padre cierra pipefd[0]  →  (bien)

Hijo llama read(pipefd[0], ...)
  → Kernel comprueba: ¿refcount extremo escritura == 0?  NO (el hijo mismo lo tiene)
  → read() se bloquea PARA SIEMPRE
  → DEADLOCK — el hijo está esperando EOF de sí mismo
```

Escenario: el padre mantiene ambos extremos abiertos hasta después de waitpid()
```
Hijo 1 (escritor):  cierra pipefd[0], escribe, cierra pipefd[1], sale ✓
Hijo 2 (lector):    cierra pipefd[1], lee...

  → Kernel comprueba refcount del extremo de escritura:
      Hijo 1 lo cerró  →  refcount decrementado
      Padre TODAVÍA lo tiene abierto  →  refcount ≥ 1
  → El read() del Hijo 2 NUNCA recibe EOF
  → Hijo 2 se cuelga para siempre
  → El waitpid() del Padre para Hijo 2 se cuelga para siempre
  → DEADLOCK
```

**P: ¿Por qué los built-ins necesitan guardar y restaurar descriptores de archivo, pero los comandos externos no?**
Los built-ins se ejecutan en el proceso propio del shell, así que cualquier cambio que hagan a los descriptores de archivo (como redirigir `stdout`) afectará al shell mismo. Para prevenir esto, guardan los FDs originales antes de la redirección y los restauran después. Los comandos externos se ejecutan en procesos hijos creados por `fork()`. Cuando el proceso hijo ejecuta `execve()`, reemplaza todo su espacio de memoria con el nuevo programa. Esto significa que cualquier cambio a los descriptores de archivo en el proceso hijo no afecta al shell padre, así que no hay necesidad de guardar y restaurar FDs para comandos externos.

**P: ¿Qué pasa si un proceso hijo falla al ejecutar `execve()`?**
Si `execve()` falla (ej., el ejecutable no se encuentra, o hay problemas de permisos), retorna `-1` y establece `errno`. El proceso hijo debería manejar este error, típicamente imprimiendo un mensaje de error y saliendo con un estado distinto de cero. El proceso padre entonces recibirá este estado de salida cuando llame a `waitpid()`, permitiendo al shell establecer el estado de salida apropiado para el usuario.

**P: ¿Puedo tener múltiples pipes en una sola línea de comandos?**
Sí, puedes tener múltiples pipes. Por ejemplo, `cmd1 | cmd2 | cmd3` crea un pipeline donde la salida de `cmd1` va a `cmd2`, y la salida de `cmd2` va a `cmd3`. Cada comando en el pipeline requerirá su propio conjunto de pipes y gestión cuidadosa de descriptores de archivo para asegurar que los datos fluyan correctamente entre ellos.

**P: Caso `cat | cat | echo hola`**
En este caso, el primer `cat` leerá de `stdin` (que es el terminal) y escribirá al pipe. El segundo `cat` leerá del pipe y escribirá en su `stdout`, que también es el terminal. El comando `echo hola` se ejecutará después del pipeline, e imprimirá "hola" en el terminal. Los dos primeros comandos `cat` no producirán ninguna salida visible a menos que escribas algo en el terminal mientras se están ejecutando, en cuyo caso esa entrada pasaría a través de ambos comandos `cat` antes de que se imprima "hola". Pero será necesario presionar Enter por cada comando cat, así que el primer `cat` leerá la entrada y la pasará al segundo `cat`, que luego la pasará al terminal. Después de eso, `echo hola` imprimirá "hola". Si simplemente ejecutas `cat | cat | echo hola` sin escribir nada, solo verás "hola" impreso, y los dos primeros comandos `cat` estarán esperando entrada. Un comando similar para ver qué se pasa de cat es `cat | cat | cat`, donde puedes escribir algo y verlo pasar a través de los tres comandos `cat` antes de que se imprima en el terminal, pero quedará atrapado en un bucle infinito si no presionas Ctrl+D para señalar EOF, porque el último `cat` estará esperando entrada del terminal, y el primer `cat` estará esperando entrada del terminal también, creando un deadlock.
