/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:54:23 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/17 12:55:53 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

char	ft_mirror(char c)
{
	if (c >= 'a' && c <= 'z')
		return (122 - c + 97);
	return (c);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	encode(char *str)
{
	int		i;
	int		output_count;
	char	c;

	i = 0;
	output_count = 0;
	while (str[i])
	{
		c = ft_tolower(str[i]);
		if (ft_isalpha(c) || ft_isdigit(c))
		{
			if (output_count > 0 && output_count % 5 == 0)
				write(1, " ", 1);
			if (ft_isalpha(c))
				c = ft_mirror(c);
			write(1, &c, 1);
			output_count++;
		}
		i++;
	}
}

void	decode(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = ft_tolower(str[i]);
		if (ft_isalpha(c))
		{
			c = ft_mirror(c);
			write(1, &c, 1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_strcmp(argv[1], "encode") == 0)
			encode(argv[2]);
		else if (ft_strcmp(argv[1], "decode") == 0)
			decode(argv[2]);
		else
			write(1, "Error\n", 6);
	}
	else
		write(1, "Error: Incorrect number of arguments\n", 38);
	return (0);
}
