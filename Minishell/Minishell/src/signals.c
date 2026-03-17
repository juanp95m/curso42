#include "minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl+C) in interactive mode. This function
 * sets the global signal status to 128 + SIGINT, prints a newline, and resets
 * the readline state to show a new prompt on the next line.
 * @param sig The signal number (not used in this function).
 */
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_status = 128 + SIGINT;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Set up signal handlers for interactive mode.
 * This function configures the shell to handle SIGINT (Ctrl+C) by calling
 * `handle_sigint`, and to ignore SIGQUIT (Ctrl+\).
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Set up signal handlers to ignore signals in non-interactive mode.
 * This function configures the shell to ignore both SIGINT and SIGQUIT, which
 * is appropriate when the shell is not running interactively (e.g., when
 * executing a script).
 */
void	setup_ignore_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Set up signal handlers for non-interactive (piped / scripted) mode.
 * SIGINT is reset to SIG_DFL so that a direct kill -SIGINT terminates the
 * shell process and the parent's waitpid() reports exit status 130 (128+2).
 * SIGQUIT keeps being ignored, matching bash non-interactive behaviour.
 */
void	setup_noninteractive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Set up signal handlers for child processes.
 * This function configures the child process to use the default signal handlers
 * for SIGINT and SIGQUIT, which allows the child process to be interrupted or
 * quit by the user as expected.
 */
void	setup_child_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
