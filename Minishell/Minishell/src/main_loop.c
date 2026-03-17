#include "minishell.h"

/**
 * @brief Get user input from the terminal or standard input.
 * If the shell is running interactively (i.e., connected to a terminal), it
 * uses readline to provide line editing capabilities.
 * If the shell is not running interactively (e.g., when input is piped in), it
 * reads a line from standard input using read_line_raw.
 * @param ps1 The prompt string to display when using readline (ignored in 
 * non-interactive mode).
 * @return A pointer to the input string. The caller is responsible for freeing
 * this string. Returns NULL on EOF or error.
 */
char	*get_user_input(char *ps1)
{
	if (isatty(STDIN_FILENO))
		return (readline(ps1));
	return (read_line_raw(STDIN_FILENO));
}

/**
 * @brief Process the list of tokens by adding expansion information, expanding
 * variables, splitting expanded tokens, and removing quotes. This function
 * modifies the token list in place and returns the new head of the list.
 * @param tokens The head of the token list to process
 * @param shell The shell state containing environment variables for expansion
 * @note If BONUS is defined, it also performs wildcard expansion.
 * @return The head of the processed token list
 */
#if BONUS

	t_token	*process_tokens(t_token *tokens, t_shell *shell)
	{
		tokens = add_expansion_info(tokens);
		tokens = expand_dollars(shell, tokens);
		tokens = split_expanded_tokens(tokens);
		tokens = expand_wildcards(tokens);
		tokens = remove_quotes_from_tokens(tokens);
		return (tokens);
	}

#else

	t_token	*process_tokens(t_token *tokens, t_shell *shell)
	{
		tokens = add_expansion_info(tokens);
		tokens = expand_dollars(shell, tokens);
		tokens = split_expanded_tokens(tokens);
		tokens = remove_quotes_from_tokens(tokens);
		return (tokens);
	}

#endif

/**
 * @brief Execute the command tree represented by the AST nodes. This function
 * first assigns full paths to all command nodes, preprocesses heredocs, and
 * then traverses the tree to execute the commands. It also updates the shell's
 * last exit code based on the execution result.
 * @param nodes The root of the AST representing the command tree
 * @param shell The shell state to update with the last exit code
 */
void	execute_command_tree(t_node *nodes, t_shell *shell)
{
	if (nodes)
	{
		assign_fullpath_recursive(nodes, shell);
		if (preprocess_heredocs(nodes, shell) == 0)
			shell->last_exit_code = traverse_tree(nodes, shell);
		else if (g_signal_status != 0)
			shell->last_exit_code = g_signal_status;
		else
			shell->last_exit_code = 1;
	}
}
