#include "minishell.h"

/**
 * @brief Check if a string matches a wildcard pattern
 * Supports '*' (matches any sequence of characters) and '?' (matches any 
 * single character)
 * @param pattern The wildcard pattern to match against (e.g., "*.c")
 * @param str The string to test for a match (e.g., "main.c")
 * @return 1 if the string matches the pattern, 0 otherwise
*/
static int	match_pattern(char *pattern, char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (0);
	if (*pattern == '*' && *(pattern + 1) == '\0')
		return (1);
	if (*pattern == '?' || *pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str)
			|| match_pattern(pattern, str + 1));
	return (0);
}

/**
 * @brief Process a directory entry and add it to the token list if it matches 
 * the pattern. Checks if the directory entry name matches the given wildcard 
 * pattern. If it does, creates a new token for the entry and appends it to the
 * token list. Hidden files (starting with '.') are ignored unless the pattern 
 * explicitly starts with '.'.
 * @param name The name of the directory entry to process.
 * @param pattern The wildcard pattern to match against.
 * @param head Pointer to the head of the token list where matching entries are
 * added.
 */
static void	process_dir_entry(char *name, char *pattern, t_token **head)
{
	t_token	*new_node;

	if (name[0] == '.' && pattern[0] != '.')
		return ;
	if (match_pattern(pattern, name))
	{
		new_node = create_new_token(ft_strdup(name), WORD);
		new_node->quote = NONE;
		add_token_back(head, new_node);
	}
}

/**
 * @brief Get a list of files in the current directory that match the given 
 * wildcard pattern
 * @param pattern The wildcard pattern to match against (e.g., "*.c")
 * @return A linked list of tokens, each containing a matching filename, 
 * or NULL if no matches are found
 */
static t_token	*get_wildcard_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*matches_head;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	matches_head = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		process_dir_entry(entry->d_name, pattern, &matches_head);
		entry = readdir(dir);
	}
	closedir(dir);
	sort_matches(matches_head);
	return (matches_head);
}

/**
 * @brief Insert the list of matches into the token list, replacing the 
 * original wildcard token
 * @param head Pointer to the head of the token list
 * @param curr The current token that contains the wildcard pattern
 * @param matches The linked list of tokens containing the matching filenames
 * @return Pointer to the last inserted match token, which will be used to 
 * continue iterating through the original token list
 */
static t_token	*insert_matches(t_token **head, t_token *curr, t_token *matches)
{
	t_token	*last_match;
	t_token	*next_tmp;

	next_tmp = curr->next;
	last_match = matches;
	while (last_match->next)
		last_match = last_match->next;
	last_match->next = next_tmp;
	if (next_tmp)
		next_tmp->prev = last_match;
	if (curr->prev)
	{
		curr->prev->next = matches;
		matches->prev = curr->prev;
	}
	else
	{
		*head = matches;
		matches->prev = NULL;
	}
	free(curr->value);
	free(curr);
	return (last_match);
}

/**
 * @brief Expand wildcard tokens in the token list. This function iterates 
 * through the token list and for each token that is of type WORD, unquoted, 
 * and contains a '*', it retrieves the list of matching files and inserts 
 * them into the token list in place of the original wildcard token.
 * @param head The head of the token list to process
 * @return The head of the modified token list with wildcard tokens expanded
 */
t_token	*expand_wildcards(t_token *head)
{
	t_token	*curr;
	t_token	*matches;

	curr = head;
	while (curr)
	{
		if (curr->type == WORD && curr->quote == NONE
			&& (ft_strchr(curr->value, '*') || ft_strchr(curr->value, '?')))
		{
			matches = get_wildcard_matches(curr->value);
			if (matches)
			{
				curr = insert_matches(&head, curr, matches);
			}
		}
		curr = curr->next;
	}
	return (head);
}
