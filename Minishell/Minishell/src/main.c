#include "minishell.h"

/**
 * @brief Increment the SHLVL environment variable to indicate a new shell 
 * level.
 * @param shell The shell state containing the environment variables
 * @note If SHLVL is not set, it initializes it to 1. 
 * If SHLVL is set to a non-numeric value, it resets it to 1.
 * If SHLVL is set to a numeric value, it increments it by 1.
 */
void	increment_shlvl(t_shell *shell)
{
	char	*str_val;
	int		int_val;
	char	*new_str;

	str_val = get_env_var("SHLVL", shell);
	if (str_val == NULL)
		set_env_var("SHLVL", "1", shell);
	else
	{
		int_val = ft_atoi(str_val);
		if (int_val < 0)
			int_val = 0;
		else
			int_val++;
		new_str = ft_itoa(int_val);
		if (new_str)
		{
			set_env_var("SHLVL", new_str, shell);
			free(new_str);
		}
	}
}

/**
 * @brief Free all resources associated with the shell state
 * @param shell The shell state to free
 */
void	create_basic_env_vars(t_shell *shell)
{
	char	*cwd_val;

	if (get_env_var("OLDPWD", shell) == NULL)
		set_env_var("OLDPWD", NULL, shell);
	if (get_env_var("PWD", shell) == NULL)
	{
		cwd_val = getcwd(NULL, 0);
		set_env_var("PWD", cwd_val, shell);
		free(cwd_val);
	}
	if (get_env_var("MAIL", shell) == NULL)
		set_env_var("MAIL", "mlermo-j@student.42malaga.com", shell);
	if (get_env_var("_", shell) == NULL)
		set_env_var("_", "/usr/bin/env", shell);
	if (get_env_var("PS1", shell) == NULL)
		set_env_var("PS1", "\001\033[1;32m\002Minishell\001\033[0m\002\
\001\033[1;34m\002$> \001\033[0m\002", shell);
	increment_shlvl(shell);
}

/**
 * @brief Check if a signal was received and update the shell's last exit code.
 * This function checks the global signal status variable, and if it indicates
 * that a signal was received, it updates the shell's last exit code accordingly
 * and resets the signal status.
 * @param shell Pointer to the shell state
 */
void	check_signal_status(t_shell *shell)
{
	if (g_signal_status != 0)
	{
		shell->last_exit_code = g_signal_status;
		g_signal_status = 0;
	}
}

int	g_signal_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell_state(&shell, envp);
	create_basic_env_vars(&shell);
	run_shell(&shell);
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	free_shell(&shell);
	return (shell.last_exit_code);
}
