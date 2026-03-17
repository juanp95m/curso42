#include "minishell.h"

/**
 * @brief  Check if a char is special
 * Mandatory: | , <, >
 * For bonus: | , <, >, &, ( or )
 * @param c Char to be checked
*/
#if BONUS

	int	is_special_char(char c)
	{
		return (c == '|' || c == '<' || c == '>' || c == '&'
			|| c == '(' || c == ')');
	}

#else

	int	is_special_char(char c)
	{
		return (c == '|' || c == '<' || c == '>');
	}

#endif

/**
 * @brief  Check if a char is a space
 * @param c Char to be checked
 */
int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * @brief  Check if a char is a quote ' or "
 * @param c Char to be checked
*/
int	is_quote(char c)
{
	if (c == '\'')
		return (SINGLE);
	else if (c == '"')
		return (DOUBLE);
	return (NONE);
}
