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

// Función base de limpieza común (sin exit)
static void cleanup_base(t_pipex *data, int close_pipes)
{
    // Cierra archivos de entrada y salida
    if (data->infile_fd >= 0)
        close(data->infile_fd);
    if (data->outfile_fd >= 0)
        close(data->outfile_fd);
    
    // Cierra pipes solo si se solicita
    if (close_pipes)
    {
        if (data->pipe_fd[0] >= 0)
            close(data->pipe_fd[0]);
        if (data->pipe_fd[1] >= 0)
            close(data->pipe_fd[1]);
    }

    // Libera la memoria de los comandos
    free_split(data->cmd1_args);
    free_split(data->cmd2_args);
    free(data->cmd1_path);
    free(data->cmd2_path);
}

// Limpieza para el flujo normal (no cierra pipes, no hace exit)
void cleanup(t_pipex *data)
{
    cleanup_base(data, 0); // 0 = no cerrar pipes
}

// Limpieza para errores (cierra todo y hace exit con código 1)
void free_and_exit(t_pipex *data)
{
    cleanup_base(data, 1); // 1 = cerrar pipes también
    exit(1);
}
