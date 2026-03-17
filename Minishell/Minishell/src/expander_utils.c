#include "minishell.h"

/**
 * @brief Advances the index past a variable name
 * @param str Input string
 * @param i Pointer to current index (will be updated)
 */
static void	advance_idx_past_var(char *str, int *i)
{
	if (str[*i] == '?')
		(*i)++;
	else if (ft_isdigit(str[*i]))
		(*i)++;
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
}

/**
 * @brief Extracts the variable segment starting at str[i]
 * @param str Input string
 * @param i Pointer to current index (will be updated)
 * @param shell Pointer to the shell state (for env vars)
 * @return Value of the extracted variable (dynamically allocated string)
 */
char	*extract_var_segment(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (!str[*i] || str[*i] == ' '
		|| (!ft_isalnum(str[*i]) && str[*i] != '_' && str[*i] != '?'))
		return (ft_strdup("$"));
	start = *i;
	advance_idx_past_var(str, i);
	var_name = ft_substr(str, start, *i - start);
	var_value = get_var_value(var_name, shell);
	free(var_name);
	return (var_value);
}

/**
 * @brief Checks if the string contains an expandable dollar sign
 * @param str Input string
 * @return 1 if expandable, 0 otherwise
 */
int	has_expandable_dollar(char *str)
{
	int	i;
	int	q[2];

	if (!str)
		return (FALSE);
	i = 0;
	ft_memset(q, 0, sizeof(int) * 2);
	while (str[i])
	{
		if (str[i] == '\'' && !q[1])
			q[0] = !q[0];
		else if (str[i] == '"' && !q[0])
			q[1] = !q[1];
		else if (str[i] == '$' && !q[0]
			&& str[i + 1] && !is_space(str[i + 1]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * @brief Handles a quote character and updates the quote state
 * @param str Input string
 * @param i Pointer to current index (will be updated)
 * @param q Quote state array
 * @return Pointer to the extracted quote character (dynamically allocated)
 */
char	*handle_quote_char(char *str, int *i, int *q)
{
	if (str[*i] == '\'')
		q[0] = !q[0];
	else
		q[1] = !q[1];
	return (ft_substr(str, (*i)++, 1));
}

/**
 * @brief Extracts a literal segment (non-expandable text)
 * @param str Input string
 * @param i Pointer to current index (will be updated)
 * @param q Quote state array
 * @return Pointer to the extracted literal segment (dynamically allocated)
 */
char	*extract_literal(char *str, int *i, int *q)
{
	int	start;

	start = *i;
	while (str[*i])
	{
		if ((str[*i] == '\'' && !q[1]) || (str[*i] == '"' && !q[0]))
			break ;
		if (str[*i] == '$' && !q[0])
			break ;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}
