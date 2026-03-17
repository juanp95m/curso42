/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:41:00 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/05 15:41:03 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	wordlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static char	**freeall(char **big)
{
	int	i;

	i = 0;
	if (!big)
		return (NULL);
	while (big[i])
	{
		free(big[i]);
		i++;
	}
	free(big);
	return (NULL);
}

static char	**create_big_memory(const char *str, int word_count)
{
	char	**big;

	if (!str)
		return (NULL);
	big = (char **)ft_calloc(sizeof(char **), (word_count + 1));
	if (!big)
	{
		free(big);
		return (NULL);
	}
	return (big);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i] != '\0' )
	{
		if (str[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		if (str[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		count;
	int		flag;
	char	**big;

	i = -1;
	count = 0;
	flag = 0;
	big = create_big_memory(str, count_words(str, c));
	if (!big)
		return (freeall(big));
	while (str[++i] != '\0' )
	{
		if (str[i] != c && flag == 0)
		{
			big[count] = ft_substr(&str[i], 0, wordlen(&str[i], c));
			if (!big[count])
				return (freeall(big));
			count++;
			flag = 1;
		}
		if (str[i] == c)
			flag = 0;
	}
	return (big);
}

// int	main(void)
// {
// 	char	**res;
// 	int		i;

// 	res = ft_split("      split       this for   me  !       ", ' ');
// 	i = 0;
// 	while(res[i] != NULL)
// 	{
// 		printf("%s - %d\n", res[i], i);
// 		free(res[i]);
// 		i++;
// 	}
// 	// freeall(res);
// 	free(res);
// 	return (0);
// }
