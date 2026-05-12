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
int main(int ac, char **av)
{
	int i = 0;
	char buf[10000];
	int b;


	if (ac != 2 || av[1] == NULL)
		return (1);

	int size = strlen(av[1]);
	while ((b = read(0, &buf[i], 1)) > 0)
		i++;
	if (b < 0)
	{
		perror("Error");
		return (1);
	}
	buf[i] = 0;
	i = 0;
	while (buf[i])
	{
		if (!ft_strncmp(buf+i, av[1], size))
		{
			fprintf(stdout, "%c", buf[i]);
			i += size;
		}
		else
		{
			fprintf(stdout, "*");
			i++;
		}
	}
	return (0);
}   
