#include "minishell.h"

/**
 * @brief Insert a new token after the current token in the token list.
 * @param current The token after which the new token should be inserted.
 * @param new_token The new token to insert.
*/
static void	insert_token_after(t_token *current, t_token *new_token)
{
	new_token->next = current->next;
	if (current->next)
		current->next->prev = new_token;
	current->next = new_token;
	new_token->prev = current;
}

/**
 * @brief Handle splitting an expanded token into multiple tokens if it
 * contains spaces.
 * @param curr The current token to potentially split
 * @param words The array of words obtained by splitting the token's value
 */
static void	handle_split_token(t_token *curr, char **words)
{
	int		i;
	t_token	*new_tok;
	t_token	*temp_iter;

	free(curr->value);
	curr->value = ft_strdup(words[0]);
	curr->expandable = FALSE;
	i = 1;
	temp_iter = curr;
	while (words[i])
	{
		new_tok = create_new_token(ft_strdup(words[i]), WORD);
		new_tok->quote = NONE;
		new_tok->expandable = FALSE;
		insert_token_after(temp_iter, new_tok);
		temp_iter = new_tok;
		i++;
	}
}

/**
 * @brief Remove an empty token from the token list and free its memory.
 * @param head Pointer to the pointer of the head of the token list
 * @param curr The token to remove
 * @return The next token after the removed token
 */
static t_token	*remove_empty_token(t_token **head, t_token *curr)
{
	t_token	*next;

	next = curr->next;
	if (curr->prev)
		curr->prev->next = curr->next;
	else
		*head = curr->next;
	if (curr->next)
		curr->next->prev = curr->prev;
	free(curr->value);
	free(curr);
	return (next);
}

/**
 * @brief Split tokens that have been expanded and contain spaces into multiple
 * tokens. This function iterates through the token list, identifies tokens that
 * are unquoted, of type WORD, and contain spaces, and splits them into multiple
 * tokens accordingly.
 * @param head The head of the token list to process
 * @return The head of the modified token list with split tokens
 */
static void	split_words(t_token *curr)
{
	char	**words;

	words = ft_split(curr->value, ' ');
	if (words && words[0])
	{
		handle_split_token(curr, words);
		free_array(words);
	}
	else if (words)
		free_array(words);
}

/**
 * @brief Split expanded tokens that contain spaces into multiple tokens.
 * This function iterates through the token list and splits any token that is 
 * unquoted, of type WORD, and contains spaces into multiple tokens.
 * @param head The head of the token list to process
 * @return The head of the modified token list with split tokens
 */
t_token	*split_expanded_tokens(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->quote == NONE && curr->type == WORD
			&& curr->value[0] == '\0')
		{
			curr = remove_empty_token(&head, curr);
			continue ;
		}
		if (curr->quote == NONE && ft_strchr(curr->value, ' '))
		{
			split_words(curr);
		}
		curr = curr->next;
	}
	return (head);
}
