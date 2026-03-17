#include "minishell.h"

/**
 * @brief Get user input from the terminal or standard input.
 * If the shell is running interactively (i.e., connected to a terminal), it
 * uses readline to provide line editing capabilities.
 * If the shell is not running interactively (e.g., when input is piped in), it
 * reads a line from standard input using get_next_line.
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

t_token	*process_tokens(t_token *tokens, t_shell *shell)
{
	tokens = add_expansion_info(tokens);
	tokens = expand_dollars(shell, tokens);
	tokens = split_expanded_tokens(tokens);
	tokens = expand_wildcards(tokens);
	tokens = remove_quotes_from_tokens(tokens);
	return (tokens);
}

/**
 * @brief Process the user input line: tokenize, expand variables, 
 * parse, and execute.
 * @param input The raw input line from the user
 * @param shell Pointer to the shell state
 */
void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_node	*nodes;

	tokens = lexer(input);
	if (!tokens)
	{
		shell->last_exit_code = 2;
		return ;
	}
	tokens = process_tokens(tokens, shell);
	nodes = parser(tokens);
	shell->current_tokens = tokens;
	shell->current_ast = nodes;
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
	shell->current_tokens = NULL;
	shell->current_ast = NULL;
	shell->heredoc_count = 0;
	free_tokens(tokens);
	free_ast(nodes);
}

// void	run_script(char *filename, t_shell *shell)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(filename);
// 		shell->last_exit_code = 127;
// 		return ;
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
// 			line[ft_strlen(line) - 1] = '\0';
// 		if (line[0] != '\0')
// 			process_input(line, shell);
// 		free(line);
// 	}
// 	close(fd);
// }

void	run_interactive(t_shell *shell)
{
	char	*input;

	setup_interactive_signals();
	while (1)
	{
		check_signal_status(shell);
		input = get_user_input(get_env_var("PS1", shell));
		check_signal_status(shell);
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (input[0] != '\0')
		{
			if (isatty(STDIN_FILENO))
				add_history(input);
			process_input(input, shell);
		}
		free(input);
		if (shell->exit_requested)
			break ;
	}
}
