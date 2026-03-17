#include "minishell.h"

/**
 * @brief Adds expansion info to each token in the list
 * @param head Pointer to the head of the token list
 * @return Pointer to the head of the updated token list
 */
t_token	*add_expansion_info(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		tmp->expandable = FALSE;
		if (has_expandable_dollar(tmp->value))
			tmp->expandable = TRUE;
		tmp = tmp->next;
	}
	return (head);
}

/**
 * @brief Joins two strings and frees the first one
 * @param s1 First string (will be freed)
 * @param s2 Second string
 * @return New joined string
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

/**
 * @brief Retrieves the value of an environment variable
 * @param var_name Name of the variable (without $)
 * @param shell Pointer to the shell state (for env vars)
 * @return Value of the variable (dynamically allocated string)
 */
char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*value;

	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(shell->last_exit_code));
	value = get_env_var(var_name, shell);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

/**
 * @brief Processes a string to expand all dollar variables
 * @param str Input string with potential $variables
 * @param shell Pointer to the shell state (for env vars)
 * @return New string with variables expanded
 */
static char	*process_expansion(char *str, t_shell *shell)
{
	char	*res;
	char	*chunk;
	int		i;
	int		q[2];

	res = ft_strdup("");
	i = 0;
	ft_memset(q, 0, sizeof(int) * 2);
	while (str[i])
	{
		if ((str[i] == '\'' && !q[1]) || (str[i] == '"' && !q[0]))
			chunk = handle_quote_char(str, &i, q);
		else if (str[i] == '$' && !q[0])
			chunk = extract_var_segment(str, &i, shell);
		else
			chunk = extract_literal(str, &i, q);
		res = ft_strjoin_free(res, chunk);
		free(chunk);
	}
	return (res);
}

/**
 * @brief Expands dollar variables in tokens marked as expandable
 * @param shell Pointer to the shell state (for env vars)
 * @param head Pointer to the head of the token list
 * @return Pointer to the head of the updated token list
 */
t_token	*expand_dollars(t_shell *shell, t_token *head)
{
	t_token	*tmp;
	char	*expanded_str;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->expandable == TRUE)
		{
			expanded_str = process_expansion(tmp->value, shell);
			free(tmp->value);
			tmp->value = expanded_str;
			tmp->expandable = FALSE;
		}
		tmp = tmp->next;
	}
	return (head);
}
