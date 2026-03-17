#include "minishell.h"

/**
 * @brief Handles the main interactive loop of the shell, including reading 
 * user input, processing it through the lexer and parser, and executing
 * commands.
 * @param tokens The list of tokens to process
 * @param nodes The AST nodes representing the command tree
 * @param shell The shell state
 */
void	process_tokens_parser(t_token *tokens, t_node *nodes, t_shell *shell)
{
	tokens = process_tokens(tokens, shell);
	nodes = parser(tokens);
	shell->current_tokens = tokens;
	shell->current_ast = nodes;
	execute_command_tree(nodes, shell);
	shell->current_tokens = NULL;
	shell->current_ast = NULL;
	shell->heredoc_count = 0;
	free_tokens(tokens);
	free_ast(nodes);
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

	nodes = NULL;
	if (is_empty_input(input))
		return ;
	tokens = lexer(input);
	if (!tokens)
	{
		shell->last_exit_code = 2;
		return ;
	}
	if (check_syntax_errors(tokens, input))
	{
		shell->last_exit_code = 2;
		free_tokens(tokens);
		return ;
	}
	process_tokens_parser(tokens, nodes, shell);
}

/**
 * @brief Set up signal handlers based on whether the shell is running in
 * interactive mode (connected to a terminal) or non-interactive mode (e.g.,
 * executing a script). In interactive mode, it sets up handlers for SIGINT and
 * SIGQUIT. In non-interactive mode, it ignores these signals.
 */
static void	set_signals_type(void)
{
	if (isatty(STDIN_FILENO))
		setup_interactive_signals();
	else
		setup_noninteractive_signals();
}

/**
 * @brief The main loop of the shell when running in interactive mode. It 
 * continuously prompts the user for input, processes it, and executes commands
 * until an exit.
 * @param shell The shell state to maintain across iterations
 */
void	run_shell(t_shell *shell)
{
	char	*input;

	set_signals_type();
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
