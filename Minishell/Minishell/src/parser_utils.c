#include "minishell.h"

/**
 * @brief Add an argument to the command with builtin_type included
 * Uses ft_strdup to create a deep copy of the value, avoiding double free errors
 * @param command Pointer to the command
 * @param token Pointer to the token
*/
void	add_arg(t_command *command, t_token *token)
{
	int	i;

	if (!command || !command->args)
		return ;
	i = 0;
	while (command->args[i])
		i++;
	if (i < 1023)
	{
		if (i == 0 && token->type > BUILTIN)
			command->builtin_type = token->type;
		else if (i == 0 && token->type < BUILTIN)
			command->builtin_type = EXTERNAL;
		command->args[i] = ft_strdup(token->value);
		command->args[i + 1] = NULL;
	}
}

/**
 * @brief Dispatch redirection parsing based on token type
 * @param cmd Pointer to the command
 * @param tokens Pointer to the pointer of the current token
 * @return TRUE if parsed successfully, FALSE otherwise
 */
int	dispatch_redirections(t_command *cmd, t_token **tokens)
{
	if ((*tokens)->type == REDIRECT_IN)
		return (parse_infile(cmd, tokens));
	else if ((*tokens)->type == REDIRECT_OUT || (*tokens)->type == APPEND)
		return (parse_outfile(cmd, tokens));
	else if ((*tokens)->type == HEREDOC)
		return (parse_heredoc(cmd, tokens));
	return (TRUE);
}

/**
 * @brief Handles parenthesis for subshells
 * Consumes '(' -> calls recursion -> consumes ')'
 * @param tokens Pointer to the pointer of the current token
 * @return Pointer to the AST node representing the parenthesized expression,
 * or NULL on error
 */
t_node	*handle_parenthesis(t_token **tokens)
{
	t_node	*node;

	*tokens = (*tokens)->next;
	node = parse_expression(tokens);
	if (!node)
		return (NULL);
	if (*tokens && (*tokens)->type == R_PAREN)
		*tokens = (*tokens)->next;
	else
	{
		ft_putstr_fd("minishell: syntax error: expected ')'\n", 2);
		return (NULL);
	}
	return (node);
}
