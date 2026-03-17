#include <minishell.h>

/**
 * @brief Returns 1 if the token type is a pipe/logic operator
 */
static int	is_pipe_op(t_tokentype type)
{
	return (type == PIPE || type == OR || type == AND);
}

/**
 * @brief Returns the string representation of a pipe/logic operator
 */
static char	*pipe_op_str(t_tokentype type)
{
	if (type == OR)
		return ("||");
	if (type == AND)
		return ("&&");
	return ("|");
}

/**
 * @brief Validates the token list for syntax errors before parsing.
 * Checks for leading, trailing, or consecutive pipe/logic operators.
 * @return 1 if a syntax error is found, 0 otherwise
 */
int	check_syntax_errors(t_token *tokens)
{
	t_token	*cur;

	if (!tokens)
		return (0);
	if (is_pipe_op(tokens->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(pipe_op_str(tokens->type), 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	cur = tokens;
	while (cur->next)
	{
		if (is_pipe_op(cur->type) && is_pipe_op(cur->next->type))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(pipe_op_str(cur->next->type), 2);
			ft_putendl_fd("'", 2);
			return (1);
		}
		cur = cur->next;
	}
	if (is_pipe_op(cur->type))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		return (1);
	}
	return (0);
}
