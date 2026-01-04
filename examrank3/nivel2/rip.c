#include <stdio.h>
#include <unistd.h>

int invalid(char *str)
{
	int i = 0;
	int open = 0;
	int close = 0;

	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if(open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void rip(char *str, int remove, int pos, int  deleted)
{
	if (deleted == remove && !invalid(str))
	{
		puts(str);
		return ;
	}
	while (str[pos])
	{
		if (str[pos] == '(' || str[pos] == ')')
		{
			char tmp = str[pos];
			str[pos] = ' ';
			rip(str, remove, pos + 1, deleted + 1);
			str[pos] = tmp;
		}
		pos++;
	}
}

int main(int ac ,char **av)
{
	if (ac != 2)
		return (1);
	int remove = invalid(av[1]);
	rip(av[1], remove, 0, 0);
	return (0);
}