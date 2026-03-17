#include "minishell.h"

/**
 * @brief  Assigns nesting depth for parentheses in the token list
 * @param token Pointer to the head of the token list
 */
void	assign_parenthesis_depth(t_token *token)
{
	int	depth;

	depth = 0;
	while (token)
	{
		if (token->type == L_PAREN)
		{
			depth++;
			token->nesting = depth;
		}
		else if (token->type == R_PAREN)
		{
			token->nesting = depth;
			depth--;
		}
		else
			token->nesting = depth;
		token = token->next;
	}
}

/**
 * @brief Check if input string is empty or contains only whitespace.
 * @param input The input string to check.
 * @return 1 if empty or whitespace-only, 0 otherwise.
 */
int	is_empty_input(char *input)
{
	int	i;

	if (!input)
		return (1);
	i = 0;
	while (input[i])
	{
		if (!is_space(input[i]))
			return (0);
		i++;
	}
	return (1);
}
