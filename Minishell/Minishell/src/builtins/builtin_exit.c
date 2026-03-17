#include "minishell.h"

/**
 * @brief Check if a string consists only of digits, 
 * with an optional leading '+' or '-'.
 * @param str The string to check.
 * @return 1 if the string is a valid number, 0 otherwise.
 */
static int	ft_only_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || str[i] == ' ' || str[i] == '\t')
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

/**
 * @brief Check for overflow when converting a string to a long long integer.
 * This function checks if the number represented
 * by the string exceeds the limits
 * of a long long integer. It also handles the optional leading '+' or '-' sign.
 * @param str The string to convert and check for overflow.
 * @param res A pointer to store the converted long long 
 * value if no overflow occurs.
 */
static int	ft_atol_overflow(const char *str, long long *res)
{
	int					i;
	int					sign;
	unsigned long long	limit;
	unsigned long long	num;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	limit = LLONG_MAX;
	if (sign == -1)
		limit = (unsigned long long)LLONG_MIN;
	while (ft_isdigit(str[i]))
	{
		if (num > (limit - (str[i] - '0')) / 10)
			return (1);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	*res = (long long)(num * sign);
	return (0);
}

/**
 * @brief Process the arguments passed to the exit command and determine 
 * the exit code. This function checks if the first argument is a valid number 
 * and if there are too many arguments. It sets the exit code accordingly 
 * based on the rules of the exit command.
 * @param args The arguments passed to the exit command (args[0] is "exit").
 * @param exit_code A pointer to store the determined exit code.
 * @return 0 if the arguments are valid
 */
static int	process_exit_args(char **args, int *exit_code)
{
	long long	val;

	val = 0;
	if (!ft_only_number(args[1]) || ft_atol_overflow(args[1], &val))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		*exit_code = 2;
	}
	else if (args[2])
	{
		ms_perror("exit", "too many arguments");
		*exit_code = 1;
		return (1);
	}
	else
	{
		*exit_code = (int)(val % 256);
		if (*exit_code < 0)
			*exit_code += 256;
	}
	return (0);
}

/**
 * @brief Implements the 'exit' built-in command, which exits the shell with a
 * given exit code. If no exit code is provided, it uses the last exit code.
 * If the provided exit code is not a valid number, it prints an error message
 * and exits with code 2. If there are too many arguments, it prints an error
 * message and exits with code 1. If the command is executed in an interactive
 * shell, it also prints "exit" to the standard error before exiting.
 * @param args The arguments passed to the exit command (args[0] is "exit").
 * @param shell The shell instance, which contains the last exit code and other
 * relevant information.
 * @return The exit code to be used when exiting the shell.
 */
int	builtin_exit(char **args, t_shell *shell)
{
	int			exit_code;

	if (getpid() == shell->main_pid && isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (!args[1])
		exit_code = shell->last_exit_code;
	else
	{
		if (process_exit_args(args, &exit_code) == 1)
			return (1);
	}
	shell->exit_requested = 1;
	shell->last_exit_code = exit_code;
	return (exit_code);
}

/**
 * @brief Handle the exit status of a child process.
 * This function checks if the child process exited normally or was terminated 
 * by a signal, and returns the appropriate exit status.
 * @param status The status returned by waitpid.
 * @return The exit status of the child process, or 128 + signal number if it
 * was terminated by a signal.
 */
int	handle_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (sig == SIGINT)
			ft_putstr_fd("\n", 2);
		return (128 + sig);
	}
	return (status);
}
