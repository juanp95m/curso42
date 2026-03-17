#include "minishell.h"
/*
int main(int ac, char **av, char **envp)
{
	char	*input_readline;
	t_token	*tokens;
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)envp;

	init_shell_state(&shell, envp);
	// builtin_env(NULL, &shell);
	while (1)
	{
		input_readline = readline("Tanqueshell$>");
		if (input_readline == NULL)
		{
			rl_clear_history();
			break;
		}
		else if (strlen(input_readline) == 0)
		{
			free(input_readline);
			continue;
		}
		else if (ft_strncmp(input_readline, "exit", 4) == 0)
		{
			builtin_exit(av, &shell);
		}
		add_history(input_readline);
		tokens = lexer(input_readline);
		debug_print_tokens(tokens);
		free_tokens(tokens);
		free(input_readline);
	}
	return (0);
}
*/