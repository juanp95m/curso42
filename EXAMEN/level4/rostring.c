#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		char *s = argv[1];
		int i = 0;
		int start, end, first_word_printed = 0;

		while (s[i] == ' ' || s[i] == '\t')
			i++;
		start = i;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
		end = i;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		
		while (s[i])
		{
			if (s[i] && s[i] != ' ' && s[i] != '\t')
			{
				write(1, &s[i], 1);
				first_word_printed = 1;
			}
			else if (first_word_printed)
			{
				write(1, " ", 1);
				first_word_printed = 0;
			}
			i++;
		}
		if (s[0] && first_word_printed)
			write(1, " ", 1);
		write(1, &s[start], end - start);
	}
	write(1, "\n", 1);
	return (0);
}
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			if (printed)
				write(1, " ", 1);
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		else
		{
			write(1, &str[i], 1);
			printed = 1;
			i++;
		}
	}
	
	// Print first word
	if (printed)
		write(1, " ", 1);
	write(1, first_word, first_len);
	write(1, "\n", 1);
	
	return (0);
}
