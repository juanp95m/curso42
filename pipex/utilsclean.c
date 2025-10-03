/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsclean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:00:55 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/03 20:04:23 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Utilidades de error y limpieza:
 - perror_and_exit: imprime error del sistema y termina con código 1
 - command_not_found: mensaje claro y termina con 127
 - free_split: libera un array de strings terminado en NULL
 - cleanup: cierre/liberación en el flujo normal del padre
 - free_and_exit: cierre/liberación agresiva para errores durante setup
*/

// Imprime mensaje con strerror(errno) y aborta con código 1
void perror_and_exit(char *message)
{
    perror(message); // Imprime tu mensaje seguido del error del sistema
    exit(1);         // Cierra el programa con un código de error
}

// Mensaje específico para 'command not found' sin usar perror
// Salida estándar de error y código 127 (convención de shells)
// Mensaje específico de comando no encontrado y salida con código 127
void command_not_found(const char *cmd_label, const char *cmd)
{
    if (cmd_label && cmd)
        fprintf(stderr, "%s: %s: command not found\n", cmd_label, cmd); //cambiar printf por write
    else if (cmd)
        fprintf(stderr, "%s: command not found\n", cmd);
    else
        fprintf(stderr, "command not found\n");
    exit(127);
}
// Libera array de punteros a char (terminado en NULL)
void free_split(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Ahora la función principal de limpieza
// Limpieza para el flujo normal: cierra fds y libera paths/args
void cleanup(t_pipex *data)
{
    // Cierra todos los descriptores de fichero que puedan estar abiertos
    if (data->infile_fd >= 0)
        close(data->infile_fd);
    if (data->outfile_fd >= 0)
        close(data->outfile_fd);

    // Libera la memoria de los comandos
    free_split(data->cmd1_args);
    free_split(data->cmd2_args);
    free(data->cmd1_path);
    free(data->cmd2_path);
}

// Libera de forma segura lo que haya y sale con código de error genérico 1
// Útil si falla algo después de reservar memoria pero antes de ejecutar procesos
// Limpieza en error: cierra todo lo que exista y sale con código 1
void free_and_exit(t_pipex *data)
{
    if (data->infile_fd >= 0)
        close(data->infile_fd);
    if (data->outfile_fd >= 0)
        close(data->outfile_fd);
    if (data->pipe_fd[0] >= 0)
        close(data->pipe_fd[0]);
    if (data->pipe_fd[1] >= 0)
        close(data->pipe_fd[1]);
    free_split(data->cmd1_args);
    free_split(data->cmd2_args);
    free(data->cmd1_path);
    free(data->cmd2_path);
    exit(1);
}
