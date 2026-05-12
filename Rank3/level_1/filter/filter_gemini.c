#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper: Custom comparison matching strncmp behavior
int ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	// If we finished the loop because i==n, it's a match.
	// If we hit a null terminator early, check if both ended.
	if (i == n) return (0);
	return (s1[i] - s2[i]);
}

// 1. Reads ALL of stdin into a dynamically resizing buffer
char *read_full_stdin(void)
{
	int		size = 128; // Start small
	int		count = 0;
	int		bytes_read;
	char	*buffer;
	char	*temp;

	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	
	while ((bytes_read = read(0, &buffer[count], 1)) > 0)
	{
		count++;
		// If buffer full, double it
		if (count >= size)
		{
			size *= 2;
			temp = realloc(buffer, size);
			if (!temp)
			{
				free(buffer);
				return (NULL);
			}
			buffer = temp;
		}
	}
	if (bytes_read < 0) // Read error
	{
		free(buffer);
		return (NULL);
	}
	buffer[count] = '\0'; // Null terminate
	return (buffer);
}

void process_filter(char *str, char *needle)
{
	int len = strlen(needle);
	int i = 0;

	while (str[i])
	{
		// Check if we have enough chars left AND they match
		if (ft_strncmp(&str[i], needle, len) == 0)
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
	char *content;

	// Check Args: strict requirement
	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	content = read_full_stdin();
	
	// Error handling for read/malloc failures
	if (!content)
	{
		perror("Error"); // Prints "Error: <system message>"
		return (1);
	}

	process_filter(content, argv[1]);
	
	free(content); // Now valid because content was malloc'd
	return (0);
}