#include "minishell.h"

/**
 * @brief Parse the input redirection
 * @param command Pointer to the command
 * @param tokens Pointer to the pointer of the current token
 * @return TRUE if parsed successfully, FALSE otherwise
 */
int	parse_infile(t_command *command, t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (!tmp->next || tmp->next->type != WORD)
		return (FALSE);
	if (command->infile)
		free(command->infile);
	command->infile = ft_strdup(tmp->next->value);
	if (command->infile[0] == '\0')
	{
		free_single_cmd(command);
		return (FALSE);
	}
	*tokens = tmp->next->next;
	return (TRUE);
}

/**
 * @brief Parse the output redirection
 * @param command Pointer to the command
 * @param tokens Pointer to the pointer of the current token
 * @return TRUE if parsed successfully, FALSE otherwise
 */
static int	append_outfile(t_command *command, char *filename, int append)
{
	char	**new_outfiles;
	int		*new_append_modes;
	int		count;

	count = command->outfile_count;
	new_outfiles = malloc(sizeof(char *) * (count + 2));
	new_append_modes = malloc(sizeof(int) * (count + 1));
	if (!new_outfiles || !new_append_modes)
	{
		free(new_outfiles);
		free(new_append_modes);
		return (FALSE);
	}
	ft_memcpy(new_outfiles, command->outfiles, sizeof(char *) * count);
	ft_memcpy(new_append_modes, command->append_modes, sizeof(int) * count);
	new_outfiles[count] = ft_strdup(filename);
	new_outfiles[count + 1] = NULL;
	new_append_modes[count] = append;
	free(command->outfiles);
	free(command->append_modes);
	command->outfiles = new_outfiles;
	command->append_modes = new_append_modes;
	command->outfile_count++;
	return (TRUE);
}

/**
 * @brief Parse the output redirection
 * @param command Pointer to the command
 * @param tokens Pointer to the pointer of the current token
 * @return TRUE if parsed successfully, FALSE otherwise
 */
int	parse_outfile(t_command *command, t_token **tokens)
{
	t_token	*tmp;
	int		append;

	tmp = *tokens;
	if (!tmp->next || tmp->next->type != WORD)
		return (FALSE);
	if (tmp->next->value[0] == '\0')
	{
		free_single_cmd(command);
		return (FALSE);
	}
	append = (tmp->type == APPEND);
	if (!append_outfile(command, tmp->next->value, append))
		return (FALSE);
	*tokens = tmp->next->next;
	return (TRUE);
}

/**
 * @brief Parse the heredoc redirection
 * @param command Pointer to the command
 * @param tokens Pointer to the pointer of the current token
 * @return TRUE if parsed successfully, FALSE otherwise
 */
static char	**append_delim(char **delims, int count, char *new_delim)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (count + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_arr[i] = delims[i];
		i++;
	}
	new_arr[count] = ft_strdup(new_delim);
	new_arr[count + 1] = NULL;
	free(delims);
	return (new_arr);
}

/**
 * @brief Parse the heredoc redirection
 * @param command Pointer to the command
 * @param tokens Pointer to the pointer of the current token
 * @return TRUE if parsed successfully, FALSE otherwise
 */
int	parse_heredoc(t_command *command, t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (!tmp->next || tmp->next->type != WORD)
		return (FALSE);
	if (tmp->next->value[0] == '\0')
	{
		free_single_cmd(command);
		return (FALSE);
	}
	command->heredoc_delimiters = append_delim(command->heredoc_delimiters,
			command->heredoc_delim_count, tmp->next->value);
	if (!command->heredoc_delimiters)
		return (FALSE);
	command->heredoc_delim_count++;
	*tokens = tmp->next->next;
	return (TRUE);
}
