#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2]; // Array para guardar los dos extremos de la tubería
    pid_t pid;

    // 1. Verificaciones de seguridad:
    // Si no hay archivo, ni argumentos, o el tipo no es 'r' ni 'w', error.
    if(!file || !argv || (type != 'r' && type != 'w'))
        return(-1);
    
    // 2. Crear la tubería (Pipe):
    // fd[0] será para LEER, fd[1] será para ESCRIBIR.
    // Es vital hacerlo ANTES del fork para que ambos procesos la tengan.
    if(pipe(fd) == -1)
        return(-1);

    // 3. Crear el proceso hijo:
    pid = fork();
    
    // Si fork falla (-1), cerramos la tubería que abrimos (limpieza) y error.
    if(pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return(-1);
    }

    // --- CÓDIGO DEL HIJO ---
    if(pid == 0)
    {
        // 4. Configuración si el modo es 'r' (Padre quiere LEER):
        if(type == 'r')
        {
            // El hijo debe enviar su salida a la tubería para que el padre la lea.
            // dup2 copia el extremo de escritura (fd[1]) en STDOUT (1).
            // Ahora, cuando el hijo haga printf, se irá al tubo.
            if(dup2(fd[1], STDOUT_FILENO) == -1)
                exit(1);
        }
        // 5. Configuración si el modo es 'w' (Padre quiere ESCRIBIR):
        else
        {
            // El hijo debe recibir datos desde la tubería.
            // dup2 copia el extremo de lectura (fd[0]) en STDIN (0).
            // Ahora, cuando el hijo haga scanf o lea, leerá del tubo.
            if(dup2(fd[0], STDIN_FILENO) == -1)
                exit(1); // OJO: El código original tenía fd[0] aquí, lo cual es correcto para 'w'.
        }
        
        // 6. Limpieza en el hijo:
        // Una vez duplicados (dup2), cerramos los descriptores originales del pipe
        // para no dejar basura abierta.
        close(fd[0]);
        close(fd[1]);

        // 7. Mutación:
        // El hijo se convierte en el programa nuevo (ej: "ls").
        execvp(file, argv);
        
        // Si execvp falla, matamos al hijo con error.
        exit(1);
    }
    // --- CÓDIGO DEL PADRE ---
    else
    {
        // 8. Configuración del padre:
        // Aquí decidimos qué "enchufe" le devolvemos al usuario.
        
        if(type == 'r') // Si el usuario quiere LEER
        {
            close(fd[1]); // Cerramos escritura (el padre solo lee).
            return(fd[0]); // Devolvemos el enchufe de lectura.
        }
        else // Si el usuario quiere ESCRIBIR
        {
            close(fd[0]); // Cerramos lectura (el padre solo escribe).
            return(fd[1]); // Devolvemos el enchufe de escritura.
        }
    }
}