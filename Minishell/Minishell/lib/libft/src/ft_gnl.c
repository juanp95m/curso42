# include "libft.h"

char	*extract_line(char *stash)
{
	char	*line;
	t_Index	index;

	if (!stash)
		return (NULL);
	line = NULL;
	index.jump = ft_strlen_char(stash, '\n');
	line = ft_substr(stash, 0, index.jump + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
		return (ft_free(stash));
	stash = update_stash(stash);
	return (line);
}
