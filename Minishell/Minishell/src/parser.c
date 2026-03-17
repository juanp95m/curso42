#include "minishell.h"

/**
 * @brief Processes a single command token (argument or redirection)
 * @param cmd The command node being built
 * @param tokens Pointer to the pointer of the current token
 * @return 1 on success, 0 on failure
 */
static int	handle_cmd_token(t_command *cmd, t_token **tokens)
{
	if ((*tokens)->type == WORD || (*tokens)->type >= BUILTIN)
	{
		add_arg(cmd, *tokens);
		*tokens = (*tokens)->next;
	}
	else if (!dispatch_redirections(cmd, tokens))
		return (0);
	return (1);
}

/**
 * @brief Creates a simple command node or handles parenthesis
 * @param tokens Pointer to the pointer of the current token
 * @return Pointer to the AST node representing the command 
 * or parenthesis, or NULL on error
 */
t_node	*parse_simple_cmd(t_token **tokens)
{
	t_node	*node;

	if (!*tokens)
		return (NULL);
	if ((*tokens)->type == L_PAREN)
		return (handle_parenthesis(tokens));
	node = create_ast_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->cmd = create_cmd_node();
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	while (*tokens && ((*tokens)->type != PIPE))
	{
		if (!handle_cmd_token(node->cmd, tokens))
		{
			free_ast(node);
			return (NULL);
		}
	}
	return (node);
}

/**
 * @brief Level 2: Parse pipes
 * Handles operator precedence by calling parse_simple_cmd() for the 
 * right-hand side
 * @param tokens Pointer to the pointer of the current token
 * @return Pointer to the AST node representing the pipe, or NULL on error
 */
t_node	*parse_pipe(t_token **tokens)
{
	t_node	*left;
	t_node	*node;

	left = parse_simple_cmd(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == PIPE)
	{
		node = create_ast_node(NODE_PIPE);
		node->left = left;
		*tokens = (*tokens)->next;
		node->right = parse_simple_cmd(tokens);
		left = node;
	}
	return (left);
}

/**
 * @brief Main parser entry point
 * @param tokens Pointer to the head of the token list
 * @return Pointer to the root of the AST, or NULL on error
 */
t_node	*parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipe(&tokens));
}

/**
 * @brief Placeholder for expression parsing in mandatory feature 
 * (e.g. for command substitution). Not implemented in this version but 
 * kept to keep minishell compilation smooth between mandatory and bonus 
 * features.
 * @param tokens Pointer to the pointer of the current token
 * @return Pointer to the AST node representing the expression, or NULL on error
 */
t_node	*parse_expression(t_token **tokens)
{
	(void)tokens;
	return (NULL);
}
