/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:42 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/03 20:08:37 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Flujo de inicialización (setup):
 1) init_defaults      -> Inicializa la struct con valores seguros (fds=-1, punteros=NULL)
 2) open_files         -> Abre infile (lectura) y outfile (escritura/crea/trunca)
 3) create_pipe_or_fail-> Crea el pipe; si falla, cierra fds y aborta
 4) data->envp = envp   -> Guarda el puntero al entorno para uso posterior
 5) init_commands       -> Prepara args y rutas ejecutables de cmd1 y cmd2
*/

// Inicializa la estructura con valores por defecto seguros
static void init_defaults(t_pipex *data)
{
    data->infile_fd = -1;
    data->outfile_fd = -1;
    data->pipe_fd[0] = -1;
    data->pipe_fd[1] = -1;
    data->cmd1_args = NULL;
    data->cmd2_args = NULL;
    data->cmd1_path = NULL;
    data->cmd2_path = NULL;
}

// Abre infile y outfile; en error libera lo ya abierto y sale
static void open_files(t_pipex *data, char **argv)
{
    data->infile_fd = open(argv[1], O_RDONLY);
    if (data->infile_fd < 0)
        perror_and_exit("infile");
    data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (data->outfile_fd < 0)
    {
        if (data->infile_fd >= 0)
            close(data->infile_fd);
        perror_and_exit("outfile");
    }
}

// Crea el pipe; si falla, cierra fds previos y sale con error
static void create_pipe_or_fail(t_pipex *data)
{
    if (pipe(data->pipe_fd) == -1)
    {
        if (data->infile_fd >= 0)
            close(data->infile_fd);
        if (data->outfile_fd >= 0)
            close(data->outfile_fd);
        perror_and_exit("pipe");
    }
}

// Separa los comandos en argv y resuelve sus rutas usando PATH
static void init_commands(t_pipex *data, char **argv, char **envp)
{
    data->cmd1_args = ft_split(argv[2], ' ');
    if (!data->cmd1_args)
        free_and_exit(data);
    data->cmd1_path = find_command_path(data->cmd1_args[0], envp);
    if (!data->cmd1_path)
        free_and_exit(data);
    data->cmd2_args = ft_split(argv[3], ' ');
    if (!data->cmd2_args)
        free_and_exit(data);
    data->cmd2_path = find_command_path(data->cmd2_args[0], envp);
    if (!data->cmd2_path)
        free_and_exit(data);
}

// función principal
// Orquesta la inicialización completa del programa pipex
void init_pipex_data(t_pipex *data, char **argv, char **envp)
{
    init_defaults(data);
    open_files(data, argv);
    create_pipe_or_fail(data);
    data->envp = envp;
    init_commands(data, argv, envp);
}
