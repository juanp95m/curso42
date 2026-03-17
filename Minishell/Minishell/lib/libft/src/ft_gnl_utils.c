# include "libft.h"

int	ft_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (2);
	}
	return (fd);
}

char	*read_line(int fd, char *stash)
{
	t_Index	index;
	char	*buffer;

	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	index.readed = 1;
	while (index.readed > 0 && (ft_strchr(stash, '\n') == NULL))
	{
		index.readed = read(fd, buffer, BUFFER_SIZE);
		if (index.readed < 0)
		{
			free(buffer);
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[index.readed] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_free(char *buffer)
{
	free(buffer);
	return (NULL);
}

size_t	ft_strlen_char(const char *str, char c)
{
	long	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*update_stash(char *stash)
{
	char	*temp;
	t_Index	index;

	if (!stash)
		return (NULL);
	index.jump = ft_strlen_char(stash, '\n');
	index.total = ft_strlen_char(stash, '\0');
	if (index.jump + 1 >= index.total)
		return (ft_free(stash));
	temp = stash;
	stash = ft_substr(stash + index.jump + 1, 0, index.total - index.jump - 1);
	free(temp);
	return (stash);
}
