#include "minishell.h"

/**
 * @brief Fills newstr with characters from str, excluding quotes
 * @param newstr The new string to fill (pre-allocated)
 * @param str The original string
 */
static void	fill_without_quotes(char *newstr, char *str)
{
	int	i;
	int	j;
	int	in_squote;
	int	in_dquote;

	i = 0;
	j = 0;
	in_squote = FALSE;
	in_dquote = FALSE;
	while (str[i])
	{
		if (str[i] == '\'' && in_dquote == FALSE)
			in_squote = !in_squote;
		else if (str[i] == '\"' && in_squote == FALSE)
			in_dquote = !in_dquote;
		else
		{
			newstr[j] = str[i];
			j++;
		}
		i++;
	}
	newstr[j] = '\0';
}

/**
 * @brief Removes quotes from a given string
 * @param str The original string with quotes
 * @return A new string without quotes (dynamically allocated)
 */
static char	*remove_quotes(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	fill_without_quotes(new_str, str);
	return (new_str);
}

/**
 * @brief Removes quotes from all tokens in the list
 * @param head Pointer to the head of the token list
 * @return Pointer to the head of the updated token list
 */
t_token	*remove_quotes_from_tokens(t_token *head)
{
	t_token	*tmp;
	char	*new_value;
	int		new_type;

	tmp = head;
	while (tmp != NULL)
	{
		new_value = remove_quotes(tmp->value);
		free(tmp->value);
		tmp->value = new_value;
		if (tmp->type == WORD)
		{
			new_type = recon_builtin(tmp->value);
			if (new_type != WORD)
				tmp->type = new_type;
		}
		tmp = tmp->next;
	}
	return (head);
}
