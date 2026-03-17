#include "minishell.h"

/**
 * @brief Pre-process heredocs for a single command node.
 * Reads all heredoc inputs from the terminal and stores the resulting
 * fd in cmd->heredoc_fd so it is available after fork/pipe.
 * @param cmd The command node containing heredoc information.
 * @param shell The shell state.
 * @return 0 on success, 1 on error.
 */
static int	preprocess_cmd_heredocs(t_command *cmd, t_shell *shell)
{
	cmd->heredoc_fd = get_heredoc_fd(cmd, shell);
	if (cmd->heredoc_delim_count > 0 && cmd->heredoc_fd == -1)
		return (1);
	return (0);
}

/**
 * @brief Recursively pre-process heredocs for all command nodes in the AST.
 * Traverses the AST and calls preprocess_cmd_heredocs on each command node.
 * @param node The current AST node to process.
 * @param shell The shell state.
 * @return 0 if all heredocs were processed successfully, 1 if any error 
 * occurred.
 */
int	preprocess_heredocs(t_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (preprocess_cmd_heredocs(node->cmd, shell));
	if (preprocess_heredocs(node->left, shell) != 0)
		return (1);
	return (preprocess_heredocs(node->right, shell));
}

/**
 * @brief Get the file descriptor for a command's heredoc input.
 * If the command has multiple heredoc delimiters, it processes them in order
 * and returns the fd of the last one. If any heredoc processing fails, it
 * returns -1.
 * @param cmd The command containing heredoc delimiters.
 * @param shell The shell state for processing heredocs.
 * @return The file descriptor for the last processed heredoc, or -1 on error.
 */
int	get_heredoc_fd(t_command *cmd, t_shell *shell)
{
	int	fd;
	int	i;

	if (cmd->heredoc_delim_count == 0)
		return (-1);
	fd = -1;
	i = 0;
	while (i < cmd->heredoc_delim_count)
	{
		if (fd != -1)
			close(fd);
		fd = process_heredoc(cmd->heredoc_delimiters[i],
				shell->heredoc_count + i, shell);
		if (fd == -1)
			return (-1);
		i++;
	}
	return (fd);
}

/**
 * @brief Handles waiting for the child process and processing the exit status.
 * Opens the resulted file or handles the cleanup if interrupted.
 * @param pid The process ID of the child process.
 * @param filename The name of the temporary file containing the heredoc content.
 * @return The file descriptor for reading the heredoc content, or -1 on error.
 */
static int	heredoc_parent_wait(pid_t pid, char *filename)
{
	int	status;
	int	fd;

	setup_ignore_signals();
	waitpid(pid, &status, 0);
	setup_interactive_signals();
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| WIFSIGNALED(status))
	{
		unlink(filename);
		free(filename);
		g_signal_status = 130;
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd);
}

/**
 * @brief Process a heredoc by reading lines until the delimiter is encountered.
 * Uses fork to handle Ctrl+C properly and allow parent to cleanup.
 * @param delimiter The string that indicates the end of the heredoc input.
 * @param heredoc_num A unique number to generate a unique temporary filename.
 * @return A file descriptor for reading the heredoc content, or -1 on error.
 */
int	process_heredoc(char *delimiter, int heredoc_num, t_shell *shell)
{
	char	*filename;
	pid_t	pid;

	filename = generate_heredoc_name(heredoc_num);
	if (!filename)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(filename);
		return (-1);
	}
	if (pid == 0)
		heredoc_child_process(filename, delimiter, shell);
	return (heredoc_parent_wait(pid, filename));
}
