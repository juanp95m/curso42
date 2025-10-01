/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:53 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/01 17:01:56 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_child_one(t_pipex data)
{
    // 1. Redirigimos la entrada estándar (0) para que lea del infile.
    // A partir de ahora, cuando el comando lea de stdin, leerá del archivo.
    if (dup2(data.infile_fd, STDIN_FILENO) == -1)
        perror_and_exit("dup2 infile");

    // 2. Redirigimos la salida estándar (1) para que escriba en la pipe.
    // Ahora, cuando el comando escriba en stdout, enviará los datos a la pipe.
    if (dup2(data.pipe_fd[1], STDOUT_FILENO) == -1)
        perror_and_exit("dup2 pipe write");

    // 3. Cerramos los descriptores que ya no son necesarios en ESTE proceso.
    // Cerramos el extremo de lectura de la pipe, este hijo solo escribe.
    close(data.pipe_fd[0]);
    // Cerramos el extremo de escritura original, ya que lo hemos duplicado en stdout.
    close(data.pipe_fd[1]);
    // Cerramos los ficheros originales.
    close(data.infile_fd);
    close(data.outfile_fd);

    // 4. Ejecutamos el comando.
    // Si execve tiene éxito, este proceso se convierte en el comando
    // y nunca llegará a la línea siguiente.
    execve(data.cmd1_path, data.cmd1_args, data.envp);

    // 5. Si execve falla, la línea de abajo se ejecutará.
    perror_and_exit("execve cmd1");
}
