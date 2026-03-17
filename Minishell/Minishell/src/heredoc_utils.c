#include <minishell.h>

/**
 * @brief Append a character to a string, reallocating memory as needed.
 * This function creates a new string that is the concatenation of the original
 * string and the new character. It frees the original string and updates the
 * pointer to point to the new string.
 * @param line A pointer to the original string. This will be freed and updated
 * to point to the new string.
 * @param c The character to append to the string.
 * @return 1 on success, 0 on memory allocation failure.
 */
static int	rl_append_char(char **line, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(*line, buf);
	free(*line);
	*line = tmp;
	return (*line != NULL);
}

/**
 * @brief Read a line of input from the user, handling heredoc input.
 * This function reads characters one by one until a newline is encountered. It
 * uses `rl_append_char` to build the line dynamically. If the end of input is
 * reached without reading any characters, it returns NULL.
 * @param fd The file descriptor to read from (usually STDIN).
 * @return A dynamically allocated string containing the line read, or NULL on
 * error or end of input.
 */
char	*read_line_raw(int fd)
{
	char	*line;
	char	buf[1];
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	ret = read(fd, buf, 1);
	while (ret > 0 && buf[0] != '\n')
	{
		if (!rl_append_char(&line, buf[0]))
			return (NULL);
		ret = read(fd, buf, 1);
	}
	if (ret <= 0 && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
