/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:53 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/02 18:47:32 by jperez-m         ###   ########.fr       */
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


// En processes.c, añade esta nueva función

void execute_child_two(t_pipex data)
{
    // 1. Redirigimos la entrada estándar (0) para que lea de la pipe.
    // Ahora, el comando leerá de la salida del comando1.
    if (dup2(data.pipe_fd[0], STDIN_FILENO) == -1)
        perror_and_exit("dup2 pipe read");

    // 2. Redirigimos la salida estándar (1) para que escriba en el outfile.
    // El resultado final del comando irá al archivo de salida.
    if (dup2(data.outfile_fd, STDOUT_FILENO) == -1)
        perror_and_exit("dup2 outfile");

    // 3. Cerramos los descriptores que ya no son necesarios en ESTE proceso.
    // Cerramos el extremo de escritura de la pipe, este hijo solo lee.
    close(data.pipe_fd[1]);
    // Cerramos el extremo de lectura original, ya que lo hemos duplicado en stdin.
    close(data.pipe_fd[0]);
    // Cerramos los ficheros originales.
    close(data.infile_fd);
    close(data.outfile_fd);

    // 4. Ejecutamos el segundo comando.
    execve(data.cmd2_path, data.cmd2_args, data.envp);

    // 5. Si execve falla, salimos con error.
    perror_and_exit("execve cmd2");
}
// En processes.c

// (Aquí ya tienes execute_child_one y execute_child_two)

void execute_processes(t_pipex *data)
{
    // 1. Creamos el primer proceso hijo (pid1)
    data->pid1 = fork();
    if (data->pid1 < 0)
        perror_and_exit("fork 1");

    // Si somos el primer hijo, ejecutamos nuestra función y terminamos.
    // El código de abajo no lo ejecutará este hijo.
    if (data->pid1 == 0)
        execute_child_one(*data);

    // 2. Creamos el segundo proceso hijo (pid2)
    // Solo el proceso padre original llega a esta línea.
    data->pid2 = fork();
    if (data->pid2 < 0)
        perror_and_exit("fork 2");

    // Si somos el segundo hijo, ejecutamos nuestra función y terminamos.
    if (data->pid2 == 0)
        execute_child_two(*data);

    // 3. El padre cierra los dos extremos de la pipe.
    // Esto es MUY importante. Si el padre no los cierra, la pipe nunca
    // se cerrará del todo y el segundo hijo podría quedarse esperando para siempre.
    close(data->pipe_fd[0]);
    close(data->pipe_fd[1]);

    // 4. El padre espera a que sus hijos terminen.
    waitpid(data->pid1, NULL, 0);
    waitpid(data->pid2, NULL, 0);
}
