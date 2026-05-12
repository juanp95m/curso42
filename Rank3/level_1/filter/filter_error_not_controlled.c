# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

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

int main(int ac, char **av)
{
	char buff[10000];
	int i = 0;
	int n;

	if (ac != 2 || av[1] == NULL)
		return (1);
	int size = strlen(av[1]);
	while((n = read(0, &buff[i], 1)) > 0)
	{
		if (n < 0)
		{
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	buff[i] = 0;
	i = 0;
	while (buff[i])
	{
		if (!ft_strncmp(&buff[i], av[1], size))
		{
			write(1, &buff[i], 1);
			i++;
		}
		else
		{
			for (int j =0; j < size; j++)
				write(1, "*", 1);
			i += size;
		}
	}


	return (0);
}
