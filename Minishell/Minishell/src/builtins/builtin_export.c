#include "minishell.h"

/**
 * @brief Process a single argument passed to the export command. This 
 * function checks if the argument is a valid environment variable assignment 
 * (e.g., KEY=VALUE) or just a variable name. It then updates the shell's 
 * environment variables accordingly.
 * @param arg The argument to process (e.g., "PATH=/usr/bin" or "USER").
 * @param shell The shell state containing environment variables.
 * @return 0 if the argument was processed successfully, 1 if there was an 
 * error (e.g., invalid variable name).
 */
static int	process_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		key = ft_substr(arg, 0, eq - arg);
	else
		key = ft_strdup(arg);
	if (!is_valid_env_name(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(key);
		return (1);
	}
	value = NULL;
	if (eq)
		value = ft_strdup(eq + 1);
	set_env_var(key, value, shell);
	free(key);
	if (value)
		free(value);
	return (0);
}

/**
 * @brief Sort an array of environment variable pointers alphabetically 
 * by their keys using bubble sort.
 * @param env The array of environment variable pointers to sort.
 * @param size The number of environment variables in the array.
 */
static void	ft_sort_env_array(t_env **env, int size)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strncmp(env[j]->key, env[j + 1]->key,
					ft_strlen(env[j]->key) + 1) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Create a sorted array of pointers to environment variables from the
 * shell's environment list. This array is used for printing the export
 * variables.
 * @param shell The shell state containing the environment list.
 * @param size_env The number of environment variables in the list.
 * @return A newly allocated array of pointers to environment variables, sorted
 * by key. The array is terminated with a NULL pointer. Returns NULL on
 * failure.
 */
static t_env	**get_sorted_env(t_shell *shell, int size_env)
{
	t_env	**arr;
	t_env	*curr;
	int		i;

	arr = malloc(sizeof(t_env *) * (size_env + 1));
	if (!arr)
		return (NULL);
	curr = shell->env_list;
	i = 0;
	while (i < size_env)
	{
		arr[i] = curr;
		curr = curr->next;
		i++;
	}
	arr[size_env] = NULL;
	ft_sort_env_array(arr, size_env);
	return (arr);
}

/**
 * @brief Print the environment variables in the format used by the export
 * command.
 * @param shell The shell state containing environment variables.
 * @note This function skips the variable with key "_" when printing.
 */
static void	print_export_vars(t_shell *shell)
{
	t_env	**sorted;
	int		i;

	sorted = get_sorted_env(shell, ft_envsize(shell->env_list));
	if (!sorted)
		return ;
	i = -1;
	while (sorted[++i])
	{
		if (ft_strncmp(sorted[i]->key, "_", 2) != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted[i]->key, 1);
			if (sorted[i]->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(sorted[i]->value, 1);
				ft_putendl_fd("\"", 1);
			}
			else
				ft_putchar_fd('\n', 1);
		}
	}
	free(sorted);
}

/**
 * @brief Implements the 'export' built-in command, which is used to set
 * environment variables. If called without arguments, it prints all environment
 * variables in a sorted order. If called with arguments, it processes each
 * argument as an environment variable assignment and updates the shell's
 * environment accordingly.
 * @param args The arguments passed to the export command (args[0] is "export").
 * @param shell The shell instance containing environment variables.
 * @return 0 if all arguments were processed successfully, 1 if there was an
 * error with any argument.
 */
int	builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if (!args[1])
	{
		print_export_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], shell))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
