/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:01:37 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/01 20:01:41 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*str;
// 	int				i;
// 	unsigned int	dif;

// 	i = 0;
// 	dif = start + len;
// 	str = (char *)malloc(sizeof(char) * len + 1);
// 	if (!str || !s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 	{
// 		str[i] = '\0';
// 		return (str);
// 	}
// 	while (start < dif)
// 	{
// 		str[i] = s[start];
// 		start++;
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char *res;

// 	res = ft_substr("123456789", 3, 4);
// 	printf("%s\n", res);
// 	free(res);
// 	return (0);
// }

// Function name ft_substr
// Prototype char *ft_substr(char const *s, unsigned int start,
// size_t len);
// Turn in files -
// Parameters s: The original string from which to create the
// substring.
// start: The starting index of the substring within
// ’s’.
// len: The maximum length of the substring.
// Return value The substring.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates memory (using malloc(3)) and returns a
// substring from the string ’s’.
// The substring starts at index ’start’ and has a
// maximum length of ’len’.