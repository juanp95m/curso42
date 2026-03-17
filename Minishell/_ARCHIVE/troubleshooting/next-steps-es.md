# Próximos Pasos: Implementaciones Esenciales para Minishell

Este documento describe dos características cruciales para un shell robusto: **Manejo de Señales** y **Redirección Heredoc**. Entender e implementar estas correctamente mejorará significativamente la funcionalidad y experiencia de usuario de tu Minishell.

## 1. Manejo de Señales

Las señales son interrupciones de software enviadas a un programa para indicar que ha ocurrido un evento importante. Son una parte fundamental de los sistemas operativos tipo Unix y son vitales para el comportamiento interactivo del shell.

### ¿Qué son las Señales?

Imagina que estás ejecutando un programa en tu terminal. ¿Qué pasa si presionas `Ctrl-C`? El programa normalmente se detiene. Esto es porque `Ctrl-C` envía un `SIGINT` (Señal de Interrupción) al proceso en primer plano. Las señales pueden usarse para:

*   **Interrumpir un proceso:** `SIGINT` (Ctrl-C)
*   **Terminar un proceso:** `SIGTERM`, `SIGKILL`
*   **Pausar/Reanudar un proceso:** `SIGSTOP`, `SIGCONT`
*   **Indicar un error:** `SIGSEGV` (Fallo de Segmentación), `SIGFPE` (Excepción de Punto Flotante)
*   **Manejar cambios de estado de procesos hijos:** `SIGCHLD`

En un shell, necesitamos manejar señales específicamente para prevenir que el shell mismo termine cuando un proceso hijo es interrumpido, y para proporcionar una gestión adecuada del prompt.

### Señales Comunes en un Shell

*   **`SIGINT` (Interrupción):** Enviada por `Ctrl-C`.
    *   **Shell (proceso padre):** Normalmente debería ignorar `SIGINT` cuando un proceso hijo está ejecutándose, para evitar terminar el shell mismo. Cuando el shell está esperando entrada (ej., `readline`), `SIGINT` normalmente debería mostrar un nuevo prompt en una nueva línea.
    *   **Procesos hijos:** Normalmente deberían terminar al recibir `SIGINT` (comportamiento por defecto).
*   **`SIGQUIT` (Salir):** Enviada por `Ctrl-\`.
    *   **Shell (proceso padre):** Generalmente debería ignorar `SIGQUIT`.
*   **`SIGTERM` (Terminar):** Una solicitud para terminar un proceso de forma elegante.
*   **`SIGCHLD` (Hijo Detenido o Terminado):** Enviada al proceso padre cuando un proceso hijo se detiene o termina. Esto es crucial para que el padre limpie los recursos del proceso hijo (ej., esperarlos).

### `signal()` vs. `sigaction()`

Históricamente, `signal()` se usaba para el manejo de señales. Sin embargo, `sigaction()` es el método preferido y más robusto por varias razones, principalmente su control más preciso sobre la semántica de señales y la reentrada.

*   **`signal()`:** Más simple, pero tiene problemas de portabilidad y no garantiza comportamiento reentrante (lo que significa que el manejador de señales puede llamar de forma segura funciones que podrían ser interrumpidas por otra señal).
*   **`sigaction()`:** Proporciona un control más fino, incluyendo si las llamadas al sistema se reinician, y permite bloquear otras señales dentro del manejador. Es el estándar POSIX.

Para Minishell, se recomienda `sigaction()`.

### Pasos de Implementación para el Manejo de Señales

La clave es establecer diferentes manejadores de señales para el proceso del shell mismo y para cualquier proceso hijo que forkee para ejecutar comandos.

#### 1. Definir una Función Manejadora de Señales

Una función manejadora de señales típicamente toma un argumento entero (el número de señal).

```c
#include <signal.h>
#include <stdio.h> // Para perror, printf
#include <readline/readline.h> // Para rl_on_new_line, rl_replace_line, rl_redisplay

// Flag global para indicar si se recibió una señal (opcional, para lógica específica)
volatile sig_atomic_t g_signal_received = 0;

void    handle_sigint_main(int sig)
{
    (void)sig; // Evitar warning de parámetro no usado
    g_signal_received = 1; // Establecer flag si se necesita
    printf("\n"); // Mover a una nueva línea
    rl_on_new_line(); // Decirle a readline que estamos en una nueva línea
    rl_replace_line("", 0); // Limpiar el buffer de entrada actual
    rl_redisplay(); // Mostrar el nuevo prompt
}

void    handle_sigint_child(int sig)
{
    (void)sig;
    // En un proceso hijo, SIGINT normalmente debería terminar el proceso.
    // El comportamiento por defecto es normalmente suficiente aquí, pero si quieres
    // limpieza personalizada antes de salir, podrías añadirla.
    // Por ahora, simplemente salimos con un estado específico.
    exit(128 + SIGINT); // 128 + número_de_señal es una convención común
}

void    handle_sigquit_ignore(int sig)
{
    (void)sig;
    // SIGQUIT (Ctrl-\) normalmente debería ser ignorada por el proceso del shell.
    // Para procesos hijos, podrías querer restaurar el comportamiento por defecto o también ignorar.
    printf("Quit: %d\n", sig); // O simplemente no hacer nada, dependiendo del comportamiento deseado
}

// Manejador más genérico para cuando no hay hijo ejecutándose, pero readline no está activo
void    handle_sigint_waiting(int sig)
{
    (void)sig;
    g_signal_received = 1;
    // No hacer nada, dejar que la función que llama maneje la salida o el bucle.
    // Esto podría ser útil si estás en un bucle esperando algo,
    // y SIGINT debería romper ese bucle.
}
```

#### 2. Configurar `sigaction`

Necesitarás una función para configurar tus manejadores de señales. Esta función se llamará en diferentes puntos del ciclo de vida de tu shell.

```c
#include <signal.h>
#include <errno.h> // Para errno

void    setup_signal_handlers(int mode)
{
    struct sigaction sa;

    // Limpiar sa para asegurar que no hay valores basura
    ft_bzero(&sa, sizeof(sa)); // Asumiendo ft_bzero de libft

    // SA_RESTART intenta reiniciar las llamadas al sistema interrumpidas
    sa.sa_flags = SA_RESTART;
    // Sigemptyset inicializa un conjunto de señales vacío, sin bloquear señales
    sigemptyset(&sa.sa_mask);

    if (mode == 0) // Proceso principal del shell, esperando entrada (readline)
    {
        sa.sa_handler = &handle_sigint_main;
        if (sigaction(SIGINT, &sa, NULL) == -1)
            perror("sigaction SIGINT main");

        sa.sa_handler = SIG_IGN; // Ignorar SIGQUIT
        if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction SIGQUIT main");
    }
    else if (mode == 1) // Proceso principal del shell, un comando hijo está ejecutándose
    {
        sa.sa_handler = SIG_IGN; // Ignorar SIGINT (para que solo afecte al hijo)
        if (sigaction(SIGINT, &sa, NULL) == -1)
            perror("sigaction SIGINT durante ejecución hijo");

        sa.sa_handler = SIG_IGN; // Ignorar SIGQUIT
        if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction SIGQUIT durante ejecución hijo");
    }
    else if (mode == 2) // Proceso hijo (comando siendo ejecutado)
    {
        sa.sa_handler = SIG_DFL; // Restaurar comportamiento por defecto de SIGINT (terminar)
        if (sigaction(SIGINT, &sa, NULL) == -1)
            perror("sigaction SIGINT hijo");

        sa.sa_handler = SIG_DFL; // Restaurar comportamiento por defecto de SIGQUIT (terminar + core dump)
        if (sigaction(SIGQUIT, &sa, NULL) == -1)
            perror("sigaction SIGQUIT hijo");
    }
    // También podrías necesitar un modo para restaurar valores por defecto o establecer manejadores específicos para builtins
}
```

#### 3. Integrar en `main` y `executor`

*   **`main.c`:**
    *   Al inicio de tu bucle `main`, antes de `readline()`, llama a `setup_signal_handlers(0)` para establecer manejadores para el estado de espera de entrada.
    *   Cuando forkeas un proceso hijo para ejecutar un comando externo:
        *   **Padre:** Antes de `waitpid()`, llama a `setup_signal_handlers(1)` para ignorar temporalmente `SIGINT`/`SIGQUIT` mientras espera. Después de `waitpid()`, restaura `setup_signal_handlers(0)`.
        *   **Hijo:** Inmediatamente después de `fork()`, pero antes de `execve()`, llama a `setup_signal_handlers(2)` para restaurar los comportamientos de señal por defecto para el comando que se está ejecutando.

```c
// Extracto de main.c
int main(int argc, char **argv, char **envp)
{
    // ... configuración inicial ...
    g_shell = init_shell(envp); // Ejemplo de inicialización de struct del shell

    while (1)
    {
        setup_signal_handlers(0); // Establecer manejadores para readline
        char *line = readline("minishell> ");
        g_signal_received = 0; // Resetear flag de señal

        if (!line) // EOF (Ctrl-D)
        {
            printf("exit\n");
            break;
        }
        if (line[0] == '\0') // Línea vacía
        {
            free(line);
            continue;
        }
        add_history(line);

        // ... lexing, parsing ...
        t_command *cmds = parse_input(line);

        // Para comandos externos:
        if (is_external_command(cmds)) // Pseudo-código
        {
            pid_t pid = fork();
            if (pid == -1)
                perror("fork");
            else if (pid == 0) // Proceso hijo
            {
                setup_signal_handlers(2); // Restaurar valores por defecto para hijo
                execute_command(cmds); // execve() reemplazará este proceso
                exit(1); // No debería llegar aquí si execve tiene éxito
            }
            else // Proceso padre
            {
                setup_signal_handlers(1); // Ignorar SIGINT/SIGQUIT mientras espera
                int status;
                waitpid(pid, &status, 0);
                // Actualizar g_shell->last_exit_status basado en WEXITSTATUS/WTERMSIG
            }
        }
        else // Comando built-in u otra lógica interna
        {
            execute_builtin(cmds);
        }

        free(line);
        // ... liberar estructura cmds ...
    }
    // ... limpieza ...
    return (0);
}
```

Esto asegura que el shell permanezca receptivo a `Ctrl-C` cuando espera entrada pero no muera cuando un proceso hijo recibe `Ctrl-C`.

## 2. Implementación de Heredoc (`<<`)

Heredoc (here document) es una forma de redirección de E/S que permite alimentar múltiples líneas de entrada a un comando hasta que se encuentra una cadena delimitadora especificada. Se ve comúnmente con comandos como `cat << EOF`.

### ¿Qué es un Heredoc?

Un heredoc toma entrada de las líneas inmediatamente posteriores al comando hasta que encuentra una línea que contiene solo el delimitador especificado. Esta entrada se redirige entonces a la entrada estándar del comando.

**Ejemplo:**
```bash
cat << END_OF_FILE
Hola,
Esta es una entrada
multilínea para cat.
END_OF_FILE
```
El comando `cat` recibirá "Hola,\nEsta es una entrada\nmultilínea para cat.\n" como su entrada estándar.

### Cómo Funciona (Conceptual)

1.  **Parsing:** Cuando el lexer/parser encuentra `<<`, lo reconoce como un operador heredoc. El token siguiente es el `delimitador`.
2.  **Recolección de Entrada:** Antes de ejecutar el comando principal, el shell necesita leer líneas de su propia entrada estándar hasta encontrar el delimitador.
3.  **Almacenamiento Temporal:** Las líneas recolectadas se almacenan en algún lugar del que el comando destino pueda leerlas. Esto típicamente se hace usando:
    *   Un **archivo temporal:** El enfoque más común. La entrada recolectada se escribe en un archivo, y luego el stdin del comando se redirige desde este archivo.
    *   Un **pipe:** Menos común para un solo heredoc, pero factible. La entrada se escribe en un extremo del pipe, y el comando lee del otro.
4.  **Redirección:** La entrada estándar del comando destino se redirige entonces a este almacenamiento temporal.
5.  **Limpieza:** Después de que el comando termine, el archivo temporal (si se usó) debe eliminarse.

### Pasos de Implementación para Heredoc

#### 1. Parsing e Identificación de Heredocs

Tu parser necesita identificar `<<` y extraer el delimitador. El delimitador puede estar entre comillas, lo que afecta cómo se expanden las variables dentro del contenido del heredoc. Si el delimitador está entre comillas, la expansión de variables (`$VAR`) no ocurre dentro del contenido del heredoc.

```c
// La estructura t_command de ejemplo podría incluir:
typedef struct s_redir
{
    t_redir_type    type; // ej., REDIR_IN, REDIR_OUT, REDIR_HEREDOC
    char            *file; // Para REDIR_HEREDOC, este sería el delimitador
    // ... otros miembros ...
}   t_redir;

typedef struct s_command
{
    char            **args;
    t_list          *redirections; // Lista de t_redir
    // ... otros miembros ...
}   t_command;

// En tu parser:
if (current_token->type == TOKEN_HEREDOC) // Asumiendo que el lexer identifica <<
{
    t_redir *redir = malloc(sizeof(t_redir));
    redir->type = REDIR_HEREDOC;
    // El siguiente token es el delimitador
    current_token = get_next_token();
    redir->file = ft_strdup(current_token->value); // Almacenar delimitador
    // Manejar comillas en delimitador: si está entre comillas, las variables no se expandirán en el heredoc
    // Podrías necesitar un flag en t_redir para 'expand_vars_in_heredoc'
    ft_lstadd_back(&cmd->redirections, ft_lstnew(redir));
}
```

#### 2. Creando un Archivo Temporal

Necesitarás un nombre de archivo temporal único. `mkstemp()` es una forma segura de hacer esto.

```c
#include <unistd.h> // Para close, unlink
#include <fcntl.h>  // Para O_WRONLY, O_CREAT
#include <stdio.h>  // Para dprintf, remove
#include <readline/readline.h> // Para readline

char    *create_temp_heredoc_file(void)
{
    char    *filename;
    int     fd;

    // Reservar espacio para un nombre de plantilla, ej., "/tmp/minishell_heredoc_XXXXXX"
    filename = ft_strdup("/tmp/minishell_heredoc_XXXXXX");
    if (!filename)
    {
        perror("ft_strdup para nombre de archivo heredoc");
        return (NULL);
    }
    // mkstemp reemplaza XXXXXX con una cadena única y crea el archivo con permisos 0600
    fd = mkstemp(filename);
    if (fd == -1)
    {
        perror("mkstemp para heredoc");
        free(filename);
        return (NULL);
    }
    close(fd); // Cerrar el descriptor de archivo, solo necesitamos el nombre por ahora
    return (filename);
}
```

#### 3. Leyendo Entrada y Escribiendo al Archivo Temporal

Esta parte típicamente se hace en un **proceso hijo** para evitar bloquear el proceso principal del shell y para manejar correctamente las señales durante la entrada del heredoc.

```c
#include <sys/wait.h> // Para waitpid
#include <string.h>   // Para strcmp
#include <stdlib.h>   // Para exit

// Función para manejar el bucle de entrada del heredoc
void    read_heredoc_input(const char *delimiter, int fd_temp_file, int expand_vars)
{
    char    *line;

    while (1)
    {
        line = readline("> "); // Prompt para entrada de heredoc
        if (!line) // EOF (Ctrl-D) durante entrada de heredoc
        {
            // Opcionalmente imprimir una advertencia sobre EOF inesperado
            dprintf(STDERR_FILENO, "minishell: advertencia: here-document delimitado por fin de archivo (se esperaba `%s')\n", delimiter);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0) // Delimitador encontrado
        {
            free(line);
            break;
        }
        if (expand_vars)
            line = expand_variables(line); // Implementar tu expansión de variables
        dprintf(fd_temp_file, "%s\n", line); // Escribir línea al archivo temporal
        free(line);
    }
    close(fd_temp_file);
    exit(0); // El proceso hijo sale después de recolectar entrada
}

// Lógica principal para procesar un heredoc antes de la ejecución del comando
char    *process_heredoc(const char *delimiter, int expand_vars)
{
    char    *temp_filename;
    pid_t   pid;
    int     status;
    int     fd_temp_file;

    temp_filename = create_temp_heredoc_file();
    if (!temp_filename)
        return (NULL);

    fd_temp_file = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd_temp_file == -1)
    {
        perror("abrir archivo temporal heredoc");
        free(temp_filename);
        return (NULL);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork heredoc");
        close(fd_temp_file);
        unlink(temp_filename); // Limpiar archivo temporal
        free(temp_filename);
        return (NULL);
    }
    else if (pid == 0) // Proceso hijo: recolecta entrada del heredoc
    {
        // Establecer manejadores de señales específicos para el hijo del heredoc para evitar
        // afectar el readline del shell padre, ej., ignorar SIGINT.
        // O terminar limpiamente. Un simple exit(1) con SIGINT podría ser deseado.
        // setup_signal_handlers_heredoc_child(); // Configuración de señales personalizada para hijo del heredoc
        read_heredoc_input(delimiter, fd_temp_file, expand_vars);
    }
    else // Proceso padre: espera a que el hijo termine
    {
        close(fd_temp_file); // El padre cierra su copia del fd
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status))
        {
            // El hijo fue terminado por una señal (ej., Ctrl-C durante entrada del heredoc)
            // Manejar esto elegantemente, potencialmente retornando NULL o un error.
            unlink(temp_filename);
            free(temp_filename);
            return (NULL);
        }
    }
    return (temp_filename); // Retornar la ruta al archivo temporal
}
```

#### 4. Integrando con la Ejecución y Limpieza

Antes de ejecutar cualquier comando (incluyendo built-ins), deberías comprobar si hay heredocs. Si existe uno, procésalo para obtener el nombre del archivo temporal. Luego, durante la configuración de redirección de E/S para el comando, usa este archivo temporal como `stdin`.

```c
// En tu función executor, antes de execve o ejecución de builtin:
// Iterar a través de command->redirections
t_list *current_redir = cmd->redirections;
char *heredoc_file = NULL;

while (current_redir)
{
    t_redir *redir = (t_redir *)current_redir->content;
    if (redir->type == REDIR_HEREDOC)
    {
        // Si hay múltiples heredocs, solo el último tiene efecto.
        // Liberar heredoc_file anterior si ya estaba establecido
        if (heredoc_file)
        {
            unlink(heredoc_file); // Eliminar archivo temporal anterior
            free(heredoc_file);
        }
        // Asumir que expand_vars se determina por las comillas del delimitador
        int expand_vars = !is_delimiter_quoted(redir->file); // Implementar esta comprobación
        heredoc_file = process_heredoc(redir->file, expand_vars);
        if (!heredoc_file)
        {
            // Manejar error, ej., señal durante entrada del heredoc
            return (1); // Error
        }
    }
    current_redir = current_redir->next;
}

// Después, durante la configuración de redirección para el comando:
int     in_fd = STDIN_FILENO;
if (heredoc_file)
{
    in_fd = open(heredoc_file, O_RDONLY);
    if (in_fd == -1)
    {
        perror("abrir heredoc_file para comando");
        unlink(heredoc_file);
        free(heredoc_file);
        return (1);
    }
    // Ahora, si este es el comando final en un pipe o ejecutado directamente:
    // dup2(in_fd, STDIN_FILENO);
    // close(in_fd);
    // Ten cuidado con dup2 en padre vs hijo, y cuándo cerrar fds.
}
// ...
// Después de que el comando (o pipeline completo) haya terminado de ejecutarse:
if (heredoc_file)
{
    unlink(heredoc_file); // Eliminar el archivo temporal
    free(heredoc_file);
}
```

### Consideraciones Clave para Heredoc

*   **Manejo de Señales durante Entrada de Heredoc:** Cuando `readline` está pidiendo entrada del heredoc, `SIGINT` (Ctrl-C) debería terminar la entrada del heredoc y potencialmente cancelar el comando, pero *no* terminar el shell principal. Esto requiere un manejador de señales específico para el proceso hijo que lee la entrada del heredoc.
*   **Múltiples Heredocs:** Si un comando tiene múltiples heredocs (ej., `cmd << UNO << DOS`), solo el contenido del *último* se usa. Los anteriores se procesan pero su contenido se descarta.
*   **Expansión de Variables:** Como se mencionó, si el delimitador está entre comillas (ej., `cmd << 'EOF'`), la expansión de variables (`$VAR`) dentro del contenido del heredoc *no* debería ocurrir. Si el delimitador no está entre comillas (`cmd << EOF`), entonces la expansión de variables *debería* ocurrir. Esto necesita un manejo cuidadoso durante la fase de `read_heredoc_input`.
*   **Manejo de Errores:** ¿Qué pasa si se presiona `Ctrl-D` antes del delimitador? El shell normalmente emite una advertencia y luego procede como si el delimitador se hubiera encontrado al EOF.
*   **Permisos del Archivo Temporal:** Asegurar que el archivo temporal se cree con permisos seguros (ej., `0600`) y se elimine rápidamente después de su uso.
*   **Gestión de Recursos:** Recuerda hacer `free` de toda la memoria reservada (nombres de archivo, líneas) y `close` de todos los descriptores de archivo.

Implementando cuidadosamente estos pasos, añadirás un manejo robusto de señales y funcionalidad heredoc potente a tu Minishell.
