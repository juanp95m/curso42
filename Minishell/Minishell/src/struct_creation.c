#include "minishell.h"

/**
 * @brief Create a new token with the given value and type.
 * @param value The string value of the token (will be freed by the caller)
 * @param type The type of the token (e.g. WORD, OPERATOR)
 * @return A pointer to the newly created token, or NULL on allocation failure
 */
t_token	*create_new_token(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(value);
		return (NULL);
	}
	new->value = value;
	new->type = type;
	new->quote = NONE;
	new->expandable = FALSE;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * @brief Add a token to the end of the token list.
 * @param head Pointer to the pointer of the head of the token list
 * @param new The token to add to the list
 */
void	add_token_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp -> next;
	tmp->next = new;
	new->prev = tmp;
}
