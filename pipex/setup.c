/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:42 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/02 19:05:01 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Esta función se encarga solo de los comandos
static void init_commands(t_pipex *data, char **argv, char **envp)
{
    data->cmd1_args = ft_split(argv[2], ' ');
    if (!data->cmd1_args)
        perror_and_exit("Error: Failed to split cmd1");
        
    data->cmd1_path = find_command_path(data->cmd1_args[0], envp);
    if (!data->cmd1_path)
        perror_and_exit("cmd1: command not found");

    data->cmd2_args = ft_split(argv[3], ' ');
    if (!data->cmd2_args)
        perror_and_exit("Error: Failed to split cmd2");
        
    data->cmd2_path = find_command_path(data->cmd2_args[0], envp);
    if (!data->cmd2_path)
        perror_and_exit("cmd2: command not found");
}

//función principal de inicialización
void init_pipex_data(t_pipex *data, char **argv, char **envp)
{
    data->infile_fd = open(argv[1], O_RDONLY);
    if (data->infile_fd < 0)
        perror_and_exit("infile"); // Una función de error personalizada

    data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (data->outfile_fd < 0)
    {
        close(data->infile_fd); // Cerramos lo que ya abrimos
        perror_and_exit("outfile");
    }

    if (pipe(data->pipe_fd) == -1)
        perror_and_exit("pipe");
    
    data->envp = envp;
    init_commands(data, argv, envp);
}
