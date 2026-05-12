# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int ft_strncmp(char *str1, char *str2, int n)
{
	int i = 0;
	while ((str1[i] && str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_stdin(char *buffer)
{
	int i = 0;
	int b;
	while ((b = read(0, &buffer[i], 1)) > 0)
		i++;
	if (b < 0)
	{
		perror("Error");
		return (1);
	}
	buffer[i] = 0;
	return (0);
}

void filter(char *str, char *replace)
{
	int len = strlen(replace);
	int i = 0;

	while (str[i])
	{
		if (ft_strncmp(&str[i], replace, len) == 0)
		{
			for (int j = 0; j < len; j++)
				write(1, "*", 1);
			i += len;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	char buf[10000];

	if (argc != 2 || argv[1] == NULL)
		return (1);
	if (get_stdin(buf))
		return (1);
	filter(buf, argv[1]);
	return (0);
}
