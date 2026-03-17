#include "minishell.h"

/**
 * @brief Handle the SIGINT signal (Ctrl+C) in heredoc mode.
 * Closes STDIN to make readline return NULL, allowing normal cleanup flow.
 * @param sig The signal number (not used in this function).
 */
void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

/**
 * @brief Set up signal handlers for heredoc mode.
 * This function configures the shell to handle SIGINT (Ctrl+C) by calling
 * `heredoc_sigint`, and to ignore SIGQUIT (Ctrl+\).
 */
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &heredoc_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Generate a unique filename for the heredoc temporary file.
 * This function creates filenames in the format ".heredoc_tmp_X" where X is
 * an incrementing number. It checks for the existence of the file and returns
 * a name that does not exist.
 * @param num The starting number to generate the filename.
 * @return A unique filename for the heredoc temporary file, or NULL on error.
 */
char	*generate_heredoc_name(int num)
{
	char	*num_str;
	char	*name;

	while (1)
	{
		num_str = ft_itoa(num);
		if (!num_str)
			return (NULL);
		name = ft_strjoin(".heredoc_tmp_", num_str);
		free(num_str);
		if (!name)
			return (NULL);
		if (access(name, F_OK) != 0)
			return (name);
		free(name);
		num++;
	}
}

/**
 * @brief Write lines to the heredoc temporary file until the delimiter is 
 * reached. This function reads lines from standard input and writes them 
 * to the provided file descriptor until a line matching the delimiter is
 * encountered. It handles both interactive and non-interactive input.
 * @param fd The file descriptor of the heredoc temporary file to write to.
 * @param delimiter The string that indicates the end of the heredoc input.
 */
void	write_heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = read_line_raw(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

/**
 * @brief The main function for the heredoc child process.
 * This function sets up the heredoc environment, opens the temporary file 
 * for writing, and enters the loop to read lines until the delimiter is 
 * reached. It also handles signals appropriately
 * @param filename The name of the temporary file to write the heredoc content 
 * to.
 * @param delim The delimiter string that indicates the end of the heredoc 
 * input.
 * @param shell The shell context containing environment variables and state.
 */
void	heredoc_child_process(char *filename, char *delim, t_shell *shell)
{
	int		tmp_fd;
	char	*delim_cpy;

	delim_cpy = ft_strdup(delim);
	cleanup_child_process(shell);
	tmp_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	if (tmp_fd == -1)
	{
		free(delim_cpy);
		exit(1);
	}
	g_signal_status = 0;
	setup_heredoc_signals();
	write_heredoc_loop(tmp_fd, delim_cpy);
	close(tmp_fd);
	free(delim_cpy);
	if (g_signal_status == 130)
		exit(130);
	exit(0);
}
