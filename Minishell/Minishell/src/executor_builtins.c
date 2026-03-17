#include "minishell.h"

/**
 * @brief Depending of builtin_type print a specific message for help
 * @param builtin_type
 * @return 0
 */
int	print_builtin_help(t_tokentype builtin_type)
{
	if (builtin_type == CD)
		ft_putendl_fd("cd: cd [dir]\nChange the current directory to DIR. \
The default DIR is the value of the HOME shell variable.", 1);
	if (builtin_type == PWD)
		ft_putendl_fd("pwd: pwd [dir]\nPrint the name of the current working \
directory.", 1);
	if (builtin_type == EXPORT)
		ft_putendl_fd("export: export\n[name[=value] ...] or export -p \
Set export attribute for shell variables.", 1);
	if (builtin_type == UNSET)
		ft_putendl_fd("unset: unset [name]\nUnset values and attributes \
of shell variables and functions.", 1);
	if (builtin_type == ENV)
		ft_putendl_fd("Usage: env [NAME=VALUE]\nSet each NAME to VALUE \
in the environment and run COMMAND.", 1);
	if (builtin_type == EXIT)
		ft_putendl_fd("exit: exit [n]\nExit the shell.\nExits the shell with \
a status of N.  If N is omitted, the exit status is that of the last \
command executed.", 1);
	return (0);
}

/**
 * @brief Execute a built-in command in the parent process.
 * @param cmd The command structure representing the built-in command 
 * to execute.
 * @param shell The shell state containing environment variables.
 * @return The exit status of the built-in command.
 */
static int	run_builtin(t_command *cmd, t_shell *shell)
{
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "--help", 7) == 0 \
&& cmd->builtin_type != ECHO)
		return (print_builtin_help(cmd->builtin_type));
	if (cmd->builtin_type == CD)
		return (builtin_cd(cmd->args, shell));
	if (cmd->builtin_type == ECHO)
		return (builtin_echo(cmd->args, shell));
	if (cmd->builtin_type == PWD)
		return (builtin_pwd(cmd->args, shell));
	if (cmd->builtin_type == EXPORT)
		return (builtin_export(cmd->args, shell));
	if (cmd->builtin_type == UNSET)
		return (builtin_unset(cmd->args, shell));
	if (cmd->builtin_type == ENV)
		return (builtin_env(cmd->args, shell));
	if (cmd->builtin_type == EXIT)
		return (builtin_exit(cmd->args, shell));
	return (0);
}

/**
 * @brief Execute a built-in command in the parent process, handling 
 * redirections.
 * @param cmd The command struct representing the built-in command to execute.
 * @param shell The shell state containing environment variables.
 * @return The exit status of the built-in command.
 * @note This function saves the original standard input and output fds.
 */
int	exec_builtin_parent(t_command *cmd, t_shell *shell)
{
	int	saved_io[2];
	int	status;

	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	status = setup_redirections(cmd);
	if (status != 0)
	{
		dup2(saved_io[0], STDIN_FILENO);
		dup2(saved_io[1], STDOUT_FILENO);
		close(saved_io[0]);
		close(saved_io[1]);
		return (status);
	}
	status = run_builtin(cmd, shell);
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
	return (status);
}
