#include "minishell.h"

/**
 * @brief Recognize if a string is a built-in command and return its 
 * corresponding enum value.
 * @param str The string to check.
 * @return The enum value corresponding to the built-in command, 
 * or WORD if not found.
 */
int	recon_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (EXIT);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (UNSET);
	return (WORD);
}

/**
 * @brief Assign the token type based on its string value. This function checks
 * for operators and built-in commands, and returns the appropriate enum value.
 * If the string does not match any operator or built-in, it returns WORD.
 * @param str The string value of the token to classify.
 * @return The enum value representing the token type.
 */
int	assign_token_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (REDIRECT_OUT);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (REDIRECT_IN);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (APPEND);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, "&&", 3) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 3) == 0)
		return (OR);
	else if (ft_strncmp(str, "(", 2) == 0)
		return (L_PAREN);
	else if (ft_strncmp(str, ")", 2) == 0)
		return (R_PAREN);
	else if (recon_builtin(str) != WORD)
		return (recon_builtin(str));
	return (WORD);
}
