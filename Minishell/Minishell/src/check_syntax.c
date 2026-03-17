#include "minishell.h"

/**
 * @brief Helper function to check if a token type is a pipe or logic operator.
 * @param type The token type to check
 * @return 1 if it's a pipe/logic operator, 0 otherwise
 */
int	is_pipe_op(t_tokentype type)
{
	return (type == PIPE || type == OR || type == AND);
}

/**
 * @brief Helper function to check if a token type is a redirection operator.
 * @param type The token type to check
 * @return 1 if it's a redirection operator, 0 otherwise
 */
int	is_redir(t_tokentype type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC);
}

/**
 * @brief Helper function to check if a token type is any kind of operator.
 * @param type The token type to check
 * @return 1 if it's an operator, 0 otherwise
 */
int	is_operator(t_tokentype type)
{
	return (is_pipe_op(type) || is_redir(type));
}

/**
 * @brief Helper function to get the string representation of a pipe/logic 
 * operator.
 * @param type The token type
 * @return A pointer to the string representation ("|", "||", or "&&")
 */
char	*pipe_op_str(t_tokentype type)
{
	if (type == OR)
		return ("||");
	if (type == AND)
		return ("&&");
	return ("|");
}

/**
 * @brief Checks for consecutive or trailing pipe/logic operators.
 * Trailing pipes just print the newline message (no command hint needed).
 * @param tokens The list of tokens to check
 * @param input The original input line for error messages
 * @return 1 if a syntax error is found, 0 otherwise
 */
int	check_middle_and_trailing(t_token *tokens, char *input)
{
	t_token	*cur;
	char	*msg;

	cur = tokens;
	while (cur->next)
	{
		if (is_pipe_op(cur->type) && is_pipe_op(cur->next->type))
		{
			print_syntax_error(pipe_op_str(cur->next->type), input);
			return (1);
		}
		if (is_redir(cur->type) && is_operator(cur->next->type))
		{
			print_syntax_error(cur->next->value, input);
			return (1);
		}
		cur = cur->next;
	}
	msg = "minishell: syntax error near unexpected token `newline'";
	if (is_pipe_op(cur->type) || is_redir(cur->type))
	{
		ft_putendl_fd(msg, 2);
		return (1);
	}
	return (0);
}
