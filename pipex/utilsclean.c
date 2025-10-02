/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsclean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:00:55 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/02 19:02:08 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void perror_and_exit(char *message)
{
    perror(message); // Imprime tu mensaje seguido del error del sistema
    exit(1);         // Cierra el programa con un código de error
}
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
// Puedes añadirla a utils.c también
void cleanup(t_pipex *data)
{
    // Cierra todos los descriptores de fichero que puedan estar abiertos
    close(data->infile_fd);
    close(data->outfile_fd);

    // Libera la memoria de los comandos
    free_split(data->cmd1_args);
    free_split(data->cmd2_args);
    free(data->cmd1_path);
    free(data->cmd2_path);
}
