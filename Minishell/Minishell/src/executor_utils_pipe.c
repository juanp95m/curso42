#include "minishell.h"

/**
 * @brief Close both ends of a pipe.
 * @param pfd The file descriptor array for the 
 * pipe (pfd[0] for read, pfd[1] for write)
 */
void	close_pipe(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

/**
 * @brief Wait for both child processes in a pipe to finish and retrieve the 
 * exit status of the right child.
 * @param left The PID of the left child process
 * @param right The PID of the right child process
 * @param status Pointer to an integer to store the exit status of the 
 * right child
 */
void	wait_pipe(pid_t left, pid_t right, int *status)
{
	waitpid(left, NULL, 0);
	waitpid(right, status, 0);
}

/**
 * @brief Fork a child process to execute a command in a pipe, setting up the
 * appropriate end of the pipe for input or output.
 * @param pfd The file descriptor array for the pipe
 * @param std The standard file descriptor to redirect (STDIN_FILENO or 
 * STDOUT_FILENO)
 * @param node The AST node representing the command to execute
 * @param shell The current shell state
 * @return The PID of the child process
 */
int	open_fork(int pfd[2], int std, t_node *node, t_shell *shell)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		if (std == STDOUT_FILENO)
			dup2(pfd[1], STDOUT_FILENO);
		else
			dup2(pfd[0], STDIN_FILENO);
		close_pipe(pfd);
		exit_code = traverse_tree(node, shell);
		cleanup_child_process(shell);
		exit(exit_code);
	}
	return (pid);
}
