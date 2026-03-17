#include "minishell.h"

/**
 * @brief Executes a logic node (AND/OR) by evaluating the left child and
 * deciding whether to execute the right child based on the result and 
 * the operator type. In mandatory build this is a stub that is never
 * reached because the parser never produces NODE_AND/NODE_OR nodes.
 * @param node The AST node representing the logic operator (AND/OR)
 * @param shell The current shell state
 * @return The exit status of the executed command(s)
 */
#if BONUS

	int	exec_node_logic(t_node *node, t_shell *shell)
	{
		int	status;

		status = traverse_tree(node->left, shell);
		if (node->type == NODE_AND)
		{
			if (status == 0)
				return (traverse_tree(node->right, shell));
		}
		else
		{
			if (status != 0)
				return (traverse_tree(node->right, shell));
		}
		return (status);
	}

#else

	int	exec_node_logic(t_node *node, t_shell *shell)
	{
		(void)node;
		(void)shell;
		return (0);
	}

#endif

/**
 * @brief Executes a pipe node by creating two child processes, setting up the
 * pipe between them, and executing the left and right commands.
 * @param node The AST node representing the pipe operator
 * @param shell The current shell state
 * @return The exit status of the right command in the pipe
 */
int	exec_node_pipe(t_node *node, t_shell *shell)
{
	int		pfd[2];
	pid_t	l_pid;
	pid_t	r_pid;
	int		status;

	setup_ignore_signals();
	if (pipe(pfd) == -1)
		return (1);
	l_pid = open_fork(pfd, STDOUT_FILENO, node->left, shell);
	r_pid = open_fork(pfd, STDIN_FILENO, node->right, shell);
	close_pipe(pfd);
	wait_pipe(l_pid, r_pid, &status);
	setup_interactive_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

/**
 * @brief Executes a command node by determining if it's a builtin or external
 * command and executing it accordingly.
 * @param node The AST node representing the command
 * @param shell The current shell state
 * @return The exit status of the executed command
 */
int	exec_node_cmd(t_node *node, t_shell *shell)
{
	t_command	*cmd;
	int			status;
	pid_t		pid;

	cmd = node->cmd;
	if ((!cmd->args || !cmd->args[0] || !cmd->args[0][0])
		&& cmd->heredoc_delim_count == 0
		&& !cmd->infile && cmd->outfile_count == 0)
		return (0);
	if (cmd->builtin_type != EXTERNAL && cmd->builtin_type != WORD)
		return (exec_builtin_parent(cmd, shell));
	setup_ignore_signals();
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		setup_child_signals();
		exec_external_child(cmd, shell);
	}
	waitpid(pid, &status, 0);
	setup_interactive_signals();
	status = handle_exit_status(status);
	return (status);
}

/**
 * @brief Traverses the AST and executes commands based on 
 * the node types (CMD, AND, OR, PIPE).
 * @param node The current AST node to execute
 * @param shell The current shell state
 * @return The exit status of the executed command(s)
 */
int	traverse_tree(t_node *node, t_shell *shell)
{
	if (!node)
		return (shell->last_exit_code);
	if (node->type == NODE_PIPE)
		return (exec_node_pipe(node, shell));
	else if (node->type == NODE_AND || node->type == NODE_OR)
		return (exec_node_logic(node, shell));
	else if (node->type == NODE_CMD)
		return (exec_node_cmd(node, shell));
	return (0);
}
