/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsclean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:00:55 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:07:35 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_and_exit(char *message)
{
	perror(message);
	exit(1);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	cleanup_base(t_pipex *data, int close_pipes)
{
	close_opened_files(data);
	if (close_pipes)
	{
		if (data->pipe_fd[0] >= 0)
			close(data->pipe_fd[0]);
		if (data->pipe_fd[1] >= 0)
			close(data->pipe_fd[1]);
	}
	free_split(data->cmd1_args);
	free_split(data->cmd2_args);
	free(data->cmd1_path);
	free(data->cmd2_path);
}

void	cleanup(t_pipex *data)
{
	cleanup_base(data, 0);
}

void	free_and_exit(t_pipex *data)
{
	cleanup_base(data, 1);
	exit(1);
}
