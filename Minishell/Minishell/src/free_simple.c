#include "minishell.h"

/**
 * @brief Free a single command structure, including its arguments and
 * redirection information.
 * @param cmd The command structure to free
 */
void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

/**
 * @brief Free a dynamically allocated array of strings.
 * @param arr The array to free
 */
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Free a linked list of environment variables.
 * @param env The head of the environment variable list to free
 */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

/**
 * @brief Free a key-value pair.
 * @param key The key to free
 * @param val The value to free
 */
void	free_keyval(char *key, char *val)
{
	if (key)
		free(key);
	if (val)
		free(val);
}

/**
 * @brief Free an array of environment variable strings in case of an error.
 * @param envp The array of environment variable strings to free
 * @param i The number of strings in the array to free
 */
void	free_env_error(char **envp, int i)
{
	while (i-- > 0)
		free(envp[i]);
	free(envp);
}
