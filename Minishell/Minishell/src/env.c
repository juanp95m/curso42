#include "minishell.h"

/**
 * @brief Duplication of char **envp to manipulate
 * @param envp Environtment variables
 * @return The copy of the envp
 */
char	**dup_env_array(char **envp)
{
	int		i;
	int		count;
	char	**newenv;

	count = 0;
	if (!envp)
		return (NULL);
	while (envp[count])
		count++;
	newenv = malloc(sizeof(char *) * (count + 1));
	if (!newenv)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		newenv[i] = ft_strdup(envp[i]);
		if (!newenv[i])
		{
			free_array(newenv);
			return (NULL);
		}
		i++;
	}
	newenv[i] = NULL;
	return (newenv);
}

/**
 * @brief Search and return the value of an environment variable.
 *
 * @param name The name of the variable to search (e.g., "PATH").
 * @param shell The shell state.
 * @return A pointer to the variable's value, or `NULL` if not found.
 * @example For "PATH", returns "/usr/bin:/bin:..."
 */
char	*get_env_var(char *name, t_shell *shell)
{
	t_env	*current;
	int		len;

	current = shell->env_list;
	if (!shell || !current)
		return (NULL);
	len = ft_strlen(name);
	while (current)
	{
		if (ft_strncmp(current->key, name, len + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Add or modify an environment variable.
 *
 * @param key The name of the variable to set (e.g., "USER").
 * @param value The value to assign (e.g., "mhotta").
 * @param shell The shell state.
 */
void	set_env_var(char *key, char *value, t_shell *shell)
{
	t_env	*curr;
	t_env	*new_node;
	int		len;

	if (!shell)
		return ;
	curr = shell->env_list;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len + 1) == 0)
		{
			if (value)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
			}
			return ;
		}
		curr = curr->next;
	}
	new_node = ft_env_new(key, value);
	if (!new_node)
		return ;
	ft_env_add_back(&shell->env_list, new_node);
}

/**
 * @brief Create a string in the format "KEY=VALUE" for an environment variable.
 * @param key The name of the variable (e.g., "PATH").
 * @param value The value of the variable (e.g., "/usr/bin:/bin").
 * @return A newly allocated string in the format "KEY=VALUE", or `NULL` 
 * on failure.
 */
static char	*make_env_str(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	if (!value)
		return (tmp);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

/**
 * @brief Convert the linked list of environment variables into an array 
 * of strings.
 * This function takes the linked list of environment variables stored in the 
 * shell
 * state and creates a new array of strings, where each string is in the format
 * "KEY=VALUE". This is useful for functions that expect the environment as an 
 * array
 * (like `execve`).
 * @param env_list The head of the linked list of environment variables.
 * @return A newly allocated array of strings representing the environment, 
 * or `NULL` on failure. The caller is responsible for freeing this array.
 */
char	**from_envlist_2_envp(t_env *env_list)
{
	char	**envp;
	t_env	*curr;
	int		i;

	envp = malloc(((ft_envsize(env_list)) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	curr = env_list;
	i = 0;
	while (curr)
	{
		envp[i] = make_env_str(curr->key, curr->value);
		if (!envp[i])
		{
			free_env_error(envp, i);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
