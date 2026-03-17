#include "minishell.h"

/**
 * @brief Count the number of nodes in the environment lis.
 * @param env Pointer to the first node of the list.
 * @return The total number of nodes in the list.
 */
int	ft_envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

/**
 * @brief Get the value of an environment variable by its key.
 * Used by the expander ($VAR) and builtins like cd.
 * @param env The environment list to search.
 * @param key The key (name) of the variable to find.
 * @return The value (string) of the variable if it exists, or NULL if not.
 */
char	*ft_getenv(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * @brief Create a new `t_env` node with the given key and value.
 * This function allocates memory for a new environment list node,
 * duplicates the provided key and value, and assigns them to the node.
 * If an error occurs during memory allocation, it frees any resources
 * already allocated and returns `NULL`.
 * @param key The key of the environment variable (e.g., "PATH").
 * @param value The value of the environment variable (e.g., "/usr/bin").
 * If `NULL`, the node's value will also be `NULL`.
 * @return A pointer to the new `t_env` node if successful, 
 * or `NULL` if it fails.
 */
t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new;

	(void)value;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	if (!new->key || (value && !new->value))
	{
		free(new->key);
		if (new->value)
			free(new->value);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

/**
 * @brief Add a node to the end of a linked list of type `t_env`.
 * This function traverses the linked list to find the last node
 * and adds the new node at the end. If the list is empty, the new node
 * becomes the first element of the list.
 * @param list A pointer to the pointer of the first node in the list.
 * @param new_node The node to be added at the end of the list.
 */
void	ft_env_add_back(t_env **list, t_env *new_node)
{
	t_env	*last;

	if (!list || !new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last = *list;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}
