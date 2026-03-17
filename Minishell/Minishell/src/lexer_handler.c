#include "minishell.h"

/**
 * @brief   advances index past the current quoted section
 * @param line The input string
 * @param i    Index of the opening quote
 * @return Index after the closing quote
 */
int	skip_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
		return (-1);
	i++;
	return (i);
}

/**
 * @brief  Check if a string contains a dollar sign
 * @param str String to be checked
 */
int	has_dollar(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] != '\0' && !is_space(str[i + 1]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/**
 * @brief  Check if the operator is a double crocodile (>>)
 * @param str String to be checked
 */
int	is_dbl(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief  Processes operators like |, <, >, <<, >>
 * @param line The input command line
 * @param i    Current index in the line
 * @param list Pointer to the token list
 * @return The new index position after reading the operator
*/
int	handle_operator(char *line, int i, t_token **list)
{
	int		len;
	char	*operator_str;
	int		type;

	len = 1;
	if (is_dbl(&line[i]))
	{
		len = 2;
	}
	operator_str = ft_substr(line, i, len);
	type = assign_token_type(operator_str);
	add_token_back(list, create_new_token(operator_str, type));
	return (i + len);
}
