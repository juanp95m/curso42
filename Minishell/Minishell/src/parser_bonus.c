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
	while (*tokens && ((*tokens)->type < AND || (*tokens)->type > R_PAREN))
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
 * @brief Level 1: Parse logical operators (&&, ||)
 * Handles operator precedence by calling parse_pipe() for the right-hand side
 * Recursively builds the AST with correct operator precedence
 * Example: For "cmd1 && cmd2 || cmd3", it creates 
 * an AND node with cmd1 and 
 * an OR node with cmd2 and cmd3
 * @param tokens Pointer to the pointer of the current token
 * @return Pointer to the root of the AST for this expression, or NULL on error
 */
t_node	*parse_expression(t_token **tokens)
{
	t_node		*left;
	t_node		*node;
	t_node_type	type;

	left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == AND || (*tokens)->type == OR))
	{
		if ((*tokens)->type == AND)
			type = NODE_AND;
		else
			type = NODE_OR;
		node = create_ast_node(type);
		node->left = left;
		*tokens = (*tokens)->next;
		node->right = parse_pipe(tokens);
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
	return (parse_expression(&tokens));
}
