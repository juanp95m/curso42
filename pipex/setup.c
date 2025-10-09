/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:42 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:07:52 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_defaults(t_pipex *data)
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

static void	open_files(t_pipex *data, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		perror_and_exit("infile");
	data->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
	{
		close_opened_files(data);
		perror_and_exit("outfile");
	}
}

static void	create_pipe_or_fail(t_pipex *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		close_opened_files(data);
		perror_and_exit("pipe");
	}
}

static void	init_commands(t_pipex *data, char **argv, char **envp)
{
	data->cmd1_args = ft_split(argv[2], ' ');
	if (!data->cmd1_args)
		free_and_exit(data);
	data->cmd1_path = find_command_path(data->cmd1_args[0], envp);
	if (!data->cmd1_path)
	{
		command_not_found("pipex", data->cmd1_args[0]);
		free_and_exit(data);
	}
	data->cmd2_args = ft_split(argv[3], ' ');
	if (!data->cmd2_args)
		free_and_exit(data);
	data->cmd2_path = find_command_path(data->cmd2_args[0], envp);
	if (!data->cmd2_path)
	{
		command_not_found("pipex", data->cmd2_args[0]);
		free_and_exit(data);
	}
}

void	init_pipex_data(t_pipex *data, char **argv, char **envp)
{
	init_defaults(data);
	open_files(data, argv);
	create_pipe_or_fail(data);
	data->envp = envp;
	init_commands(data, argv, envp);
}
