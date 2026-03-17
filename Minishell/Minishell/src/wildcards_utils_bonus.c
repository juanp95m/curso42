#include "minishell.h"

/**
 * @brief Check if a string matches a wildcard pattern
 * Supports '*' (matches any sequence of characters) and '?' (matches any 
 * single character)
 * @param pattern The wildcard pattern to match against (e.g., "*.c")
 * @param str The string to test for a match (e.g., "main.c")
 * @return 1 if the string matches the pattern, 0 otherwise
 */
void	swap_nodes_value(t_token *a, t_token *b)
{
	char		*tmp_val;
	t_tokentype	tmp_type;

	tmp_val = a->value;
	tmp_type = a->type;
	a->value = b->value;
	a->type = b->type;
	b->value = tmp_val;
	b->type = tmp_type;
}

/**
 * @brief Insert a list of matching tokens into the token list in place of the
 * original wildcard token.
 * @param head Pointer to the pointer of the head of the token list
 * @param curr The current token that contains the wildcard pattern
 */
void	sort_matches(t_token *head)
{
	t_token	*curr;
	int		swapped;

	if (!head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = head;
		while (curr->next)
		{
			if (ft_strncmp(curr->value, curr->next->value,
					ft_strlen(curr->value) + 1) > 0)
			{
				swap_nodes_value(curr, curr->next);
				swapped = 1;
			}
			curr = curr->next;
		}
	}
}
