#include "minishell.h"

/**
 * @brief Handle input redirections for a command, including infile and heredoc.
 * @param cmd The command struct containing redirection information
 * @return 0 on success, non-zero on error
 */
int	handle_input_redirections(t_command *cmd)
{
	int	fd;
	int	fd_heredoc;

	fd_heredoc = cmd->heredoc_fd;
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			ms_perror(cmd->infile, NULL);
			if (fd_heredoc != -1)
				close(fd_heredoc);
			cmd->heredoc_fd = -1;
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (fd_heredoc != -1)
	{
		dup2(fd_heredoc, STDIN_FILENO);
		close(fd_heredoc);
		cmd->heredoc_fd = -1;
	}
	return (0);
}

/**
 * @brief Handle output redirections for a command, including > and >>.
 * @param cmd The command struct containing redirection information
 * @return 0 on success, non-zero on error
 */
int	handle_output_redirections(t_command *cmd)
{
	int	fd;
	int	i;

	if (cmd->outfile_count == 0)
		return (0);
	i = 0;
	while (i < cmd->outfile_count)
	{
		if (cmd->append_modes[i])
			fd = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ms_perror(cmd->outfiles[i], NULL);
			return (1);
		}
		if (i == cmd->outfile_count - 1)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

/**
 * @brief Set up all redirections for a command by handling both input
 * and output redirections. This function is called in the child process before
 * executing an external command.
 * @param cmd The command struct containing all redirection information
 * @return 0 on success, non-zero on error
 */
int	setup_redirections(t_command *cmd)
{
	int	ret;

	ret = handle_input_redirections(cmd);
	if (ret != 0)
		return (ret);
	if (handle_output_redirections(cmd) != 0)
		return (1);
	return (0);
}

/**
 * @brief Handle command not found error and exit
 * @param cmd The command that was not found
 * @param shell The shell state to cleanup
 */
static void	handle_command_not_found(t_command *cmd, t_shell *shell)
{
	if (cmd->args[0])
		ms_perror(cmd->args[0], "command not found");
	else
		ms_perror("", "command not found");
	cleanup_child_process(shell);
	exit(127);
}

/**
 * @brief Execute an external command in a child process, handling redirections.
 * @param cmd The command struct representing the external command to execute.
 * @param shell The shell state containing environment variables.
 * @note This function does not return; it either successfully executes the
 * command or exits with an error status.
 */
void	exec_external_child(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**envp_new;
	int		status;

	status = setup_redirections(cmd);
	if (status != 0)
	{
		cleanup_child_process(shell);
		exit(status);
	}
	if (!cmd->args || !cmd->args[0] || !cmd->args[0][0])
	{
		cleanup_child_process(shell);
		exit(0);
	}
	path = cmd->fullpath;
	if (!path)
		handle_command_not_found(cmd, shell);
	envp_new = from_envlist_2_envp(shell->env_list);
	execve(path, cmd->args, envp_new);
	free_array(envp_new);
	exit_with_exec_error(cmd->args[0], shell);
}
