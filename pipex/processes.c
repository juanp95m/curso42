/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:53 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/08 19:45:50 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child_one(t_pipex data)
{
	if (dup2(data.infile_fd, STDIN_FILENO) == -1)
		perror_and_exit("dup2 infile");
	if (dup2(data.pipe_fd[1], STDOUT_FILENO) == -1)
		perror_and_exit("dup2 pipe write");
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	close_opened_files(&data);
	execve(data.cmd1_path, data.cmd1_args, data.envp);
	perror_and_exit("execve cmd1");
}

void	execute_child_two(t_pipex data)
{
	if (dup2(data.pipe_fd[0], STDIN_FILENO) == -1)
		perror_and_exit("dup2 pipe read");
	if (dup2(data.outfile_fd, STDOUT_FILENO) == -1)
		perror_and_exit("dup2 outfile");
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	close_opened_files(&data);
	execve(data.cmd2_path, data.cmd2_args, data.envp);
	perror_and_exit("execve cmd2");
}

void	execute_processes(t_pipex *data)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		perror_and_exit("fork 1");
	if (data->pid1 == 0)
		execute_child_one(*data);
	data->pid2 = fork();
	if (data->pid2 < 0)
		perror_and_exit("fork 2");
	if (data->pid2 == 0)
		execute_child_two(*data);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}
