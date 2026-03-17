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
 * @brief Prints the syntax error message and, in non-interactive mode,
 * also prints the offending input line (like bash does).
 */
static void	print_syntax_error(char *token_str, char *input)
{
	ft_putstr_fd("minishell: line 1: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_str, 2);
	ft_putendl_fd("'", 2);
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("minishell: line 1: `", 2);
		ft_putstr_fd(input, 2);
		ft_putendl_fd("'", 2);
	}
}

/**
 * @brief Validates the token list for syntax errors before parsing.
 * Checks for leading, trailing, or consecutive pipe/logic operators.
 * @param tokens The token list to validate
 * @param input  The original input line (for non-interactive error reporting)
 * @return 1 if a syntax error is found, 0 otherwise
 */
int	check_syntax_errors(t_token *tokens, char *input)
{
	t_token	*cur;

	if (!tokens)
		return (0);
	if (is_pipe_op(tokens->type))
	{
		print_syntax_error(pipe_op_str(tokens->type), input);
		return (1);
	}
	cur = tokens;
	while (cur->next)
	{
		if (is_pipe_op(cur->type) && is_pipe_op(cur->next->type))
		{
			print_syntax_error(pipe_op_str(cur->next->type), input);
			return (1);
		}
		cur = cur->next;
	}
	if (is_pipe_op(cur->type))
	{
		print_syntax_error("newline", input);
		return (1);
	}
	return (0);
}
