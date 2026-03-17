#include "minishell.h"

/**
 * @brief Helper to find the end index of a word and detect quotes
 * @param line The input command line
 * @param i    Current index in the line
 * @param quote Pointer to store detected quote type
 * @return The index marking the end of the word
 */
static int	find_end_of_word(char *line, int i, int *quote)
{
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			*quote = is_quote(line[i]);
			i = skip_quotes(line, i);
			if (i == -1)
				return (-1);
		}
		else if (!is_special_char(line[i]) && !is_space(line[i]))
			i++;
		else
			break ;
	}
	return (i);
}

/**
 * @brief  Processes words (alphanumeric, etc.)
 * @param line The input command line
 * @param i    Current index in the line
 * @param list Pointer to the token list
 * @return The new index position after reading the word
 */
int	handle_word(char *line, int i, t_token **list)
{
	int		start;
	char	*word;
	t_token	*node;
	int		quote;

	start = i;
	quote = NONE;
	i = find_end_of_word(line, i, &quote);
	word = ft_substr(line, start, i - start);
	if (!word)
		return (-1);
	node = create_new_token(word, assign_token_type(word));
	if (!node)
		return (-1);
	node->quote = quote;
	add_token_back(list, node);
	return (i);
}

/**
 * @brief  Main lexer function to tokenize input line
 * @param line The input command line
 * @return Pointer to the head of the token list
*/
t_token	*lexer(char *line)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_special_char(line[i]))
			i = handle_operator(line, i, &head);
		else
			i = handle_word(line, i, &head);
		if (i == -1)
		{
			ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
			free_tokens(head);
			return (NULL);
		}
	}
	assign_parenthesis_depth(head);
	return (head);
}
