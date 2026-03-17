#include "minishell.h"

/**
 * @brief Checks if the given string is a valid environment variable name.
 * @param str The string to check.
 * @return TRUE if the string is a valid environment variable name, 
 * FALSE otherwise.
 */
int	is_valid_env_name(char *str)
{
	int	i;

	if (!str || !*str)
		return (FALSE);
	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_' )
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Implements the 'env' built-in command, which prints the current 
 * environment variables.
 * @param args The arguments passed to the command.
 * @param shell The shell instance.
 * @return 0 on success, 1 on failure.
 */
int	builtin_env(char **args, t_shell *shell)
{
	t_env	*current;

	if (args && args[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		return (1);
	}
	if (!shell || !shell->env_list)
		return (1);
	current = shell->env_list;
	while (current != NULL)
	{
		if (current->value != NULL )
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	return (0);
}
