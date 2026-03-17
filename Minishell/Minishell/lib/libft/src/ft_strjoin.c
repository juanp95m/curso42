/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:12:18 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/01 21:12:20 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len + 1);
	str[len] = '\0';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_strjoin("aaaa", "bbbb"));
// 	return (0);
// }

// Function name ft_strjoin
// Prototype char *ft_strjoin(char const *s1, char const *s2);
// Turn in files -
// Parameters s1: The prefix string.
// s2: The suffix string.
// Return value The new string.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates memory (using malloc(3)) and returns a
// new string, which is the result of concatenating
// ’s1’ and ’s2’.

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char		*str;
// 	// size_t		i;
// 	size_t		len;
// 	// size_t		j;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	// if (s1[0] == '\0' || s2[0] == '\0')
// 	// 	len = 0;
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	str = (char *)malloc(sizeof(char) * len + 1);
// 	if (!str)
// 	{
// 		free(str);
// 		return (NULL);
// 	}
// 	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
// 	ft_strlcat(str, s2, len + 1);
// 	// i = 0;
// 	// while (i < ft_strlen(s1) + 1)
// 	// {
// 	// 	str[i] = s1[i];
// 	// 	i++;
// 	// }
// 	// j = 0;
// 	// while (i < len)
// 	// {
// 	// 	str[i] = s2[j];
// 	// 	i++;
// 	// 	j++;
// 	// }
// 	str[len] = '\0';
// 	return (str);
// }