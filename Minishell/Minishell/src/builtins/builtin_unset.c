#include "minishell.h"

/**
 * @brief Verifies if a string is a valid identifier for an environment 
 * variable.
 * @param s The string to check.
 * @return 1 if the string is a valid identifier, 0 otherwise.
 */
static	int	is_valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (ft_isdigit(s[0]))
		return (0);
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Removes an environment variable from the linked list.
 * @param shell Main structure containing the environment list.
 * @param key Name of the variable to remove.
 */
static void	del_from_list(t_shell *shell, char *key)
{
	t_env	*curr;
	t_env	*prev;
	size_t	len;

	curr = shell->env_list;
	prev = NULL;
	len = ft_strlen(key);
	if (!shell->env_list)
		return ;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len + 1) == 0)
		{
			if (prev == NULL)
				shell->env_list = curr->next;
			else
				prev->next = curr->next;
			free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/**
 * @brief It prints the error for unset and set the status to 1.
 * @param status 
 * @return status set as 1.
 */
static	int	failure_unset(int status)
{
	fprintf(stderr, "");
	status = 1;
	return (status);
}

/**
 * @brief Implements the 'unset' built-in command, which removes environment
 * variables from the shell's environment list. It checks if each provided
 * argument is a valid identifier and if so, it removes the corresponding
 * variable from the environment list. If an argument is not a valid identifier,
 * it prints an error message and returns a non-zero exit code.
 * @param args The arguments passed to the unset command (args[0] is "unset").
 * @param shell The shell instance containing the environment list.
 * @return 0 if all variables were unset successfully, 1 if there was an error
 * with any argument.
 */
int	builtin_unset(char **args, t_shell *shell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!args[i][0])  // string vacío
		{
			i++;
			continue;
		}
		if (!is_valid_identifier(args[i]))
			failure_unset(status);
		if (ft_strncmp(args[i], "_", 2) == 0)
			failure_unset(status);
		else
			del_from_list(shell, args[i]);
		i++;
	}
	return (status);
}
