/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:27 by jperez-m          #+#    #+#             */
/*   Updated: 2025/05/13 19:02:31 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_wordcount(const char *s, char c)
{
	int	isdelimiter;
	int	words;

	words = 0;
	isdelimiter = 1;
	while (s && *s)
	{
		if (*s == c)
			isdelimiter = 1;
		else if (*s != c && isdelimiter)
		{
			isdelimiter = 0;
			words++;
		}
		s++;
	}
	return (words);
}

static int	word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	char	**create_mem(int wc)
{
	char	**str;

	str = (char **)ft_calloc(wc + 1, sizeof(char *));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static	void	free_mem(char **array, int count)
{
	if (!array)
	{
		while (count > 0)
		{
			free(array[count]);
			count--;
		}
	}
	free(array);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		i;
	int		flag;
	int		count;

	i = -1;
	count = 0;
	flag = 0;
	array = create_mem(ft_wordcount(s, c));
	if (!s || !(array))
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			array[count] = ft_substr(&s[i], 0, word_len(&s[i], c));
			if (!array[count])
				free_mem(array, count);
			count++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
	}
	return (array);
}
