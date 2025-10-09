/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:38:01 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/09 12:05:36 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*check_paths(char **all_paths, char *command)
{
	char	*temp_path;
	char	*full_path;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *command, char **envp)
{
	char	*path_variable;
	char	**all_paths;
	char	*executable_path;

	path_variable = get_path_variable(envp);
	if (!path_variable)
		return (NULL);
	all_paths = ft_split(path_variable, ':');
	if (!all_paths)
		return (NULL);
	executable_path = check_paths(all_paths, command);
	free_split(all_paths);
	return (executable_path);
}

void	close_opened_files(t_pipex *data)
{
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	if (data->outfile_fd >= 0)
		close(data->outfile_fd);
}

void	command_not_found(const char *cmd_label, const char *cmd)
{
	if (cmd_label && cmd)
		ft_printf("%s: %s: command not found\n", cmd_label, cmd);
	else if (cmd)
		ft_printf("%s: command not found\n", cmd);
	else
		ft_printf("command not found\n");
}
