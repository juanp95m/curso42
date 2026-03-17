#include "minishell.h"

/**
 * @brief Check if a string is a valid -n flag for echo (e.g., -n, -nn, etc.).
 * @param str The string to check.
 * @return TRUE if the string is a valid -n flag, FALSE otherwise.
*/
static int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || (!str[1]))
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Built-in command to print arguments to standard output, with optional 
 * newline suppression.
 * @param args The arguments passed to the echo command (args[0] is "echo").
 * @param shell The shell state (not used in this function but included for 
 * consistency).
 * @return 0 on success.
 */
int	builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	n_flag;

	(void)shell;
	i = 1;
	n_flag = FALSE;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = TRUE;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == FALSE)
		ft_putstr_fd("\n", 1);
	return (0);
}
