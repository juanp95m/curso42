/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:45:40 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/01 21:45:43 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	check_coincidence(const char *set, char c)
{
	int	coincidence;
	int	i;

	i = 0;
	coincidence = 0;
	while (set[i] != '\0' && coincidence == 0)
	{
		if (set[i] == c)
			coincidence = 1;
		i++;
	}
	return (coincidence);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				start;
	int				end;
	unsigned char	*res;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (check_coincidence(set, s1[start]) == 1)
		start++;
	while (check_coincidence(set, s1[end]) == 1)
		end--;
	res = (unsigned char *)ft_substr(s1, start, (end - start) + 1);
	if (!res)
		return (NULL);
	return ((char *)res);
}

// int	main(void)
// {
// 	char	*s;

// 	char 	test[] = "abcoooabc";
// 	s = ft_strtrim(test, "abc");
// 	// char 	test[] = 
//"   \t  \n\n \t\t  \n\n\nHello \t  
// 	// Please\n Trim me !\n   \n \n \t\t\n  ";
// 	// s = ft_strtrim(test, " \n\t");
// 	printf("%s\n%s\n", test, s);
// 	//free(s);
// 	return (0);
// }

// static size_t	find_index_ocurrence(const char *s1, char c, char f)
// {
// 	size_t	i;
// 	size_t	j;

// 	j = ft_strlen(s1);
// 	i = 0;
// 	if (f == 'f')
// 	{
// 		while(i < j)
// 		{
// 			if (s1[i] == c)
// 				return (i+1);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		while (j > i)
// 		{
// 			if (s1[j] == c)
// 				return (j);
// 			j--;
// 		}
// 	}
// 	return (0);
// }

// static	char	*create_charmalloc(int	len)
// {
// 	char	*str;
// 	str = (char *)malloc(sizeof(char) * len + 1);
// 	if (!str)
// 		return (str);
// 	else
// 		return (str);
// }
// static char	*get_indexes(char const *s1, char const *set)
// {
// }
// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	i;
// 	char	*str;
// 	size_t	start;
// 	size_t	end;

// 	start = 0;
// 	end = ft_strlen(s1);
// 	i = 0;
// 	// printf("%zu\n", ft_strlen(set));
// 	if (!s1 || !set)
// 		return (NULL);
// 	if (ft_strlen(set) == 0)
// 		return ((char *)s1);
// 	while (i < ft_strlen(set))
// 		{
// 			if (find_index_ocurrence(s1, set[i], 'f') > start)
// 				start = find_index_ocurrence(s1, set[i], 'f');
// 			if (find_index_ocurrence(s1, set[i], 'r') < end)
// 				end = find_index_ocurrence(s1, set[i], 'r');
// 			i++;
// 		}
// 	printf("%zu, %zu\n", start, end);
// 	str = create_charmalloc(end - start);
// 	ft_memcpy(str, s1+start, end - start);
// 	str[(end - start) + 1] = '\0';
// 	return (str);
// }

// Function name ft_strtrim
// Prototype char *ft_strtrim(char const *s1, char const *set);
// Turn in files -
// Parameters s1: The string to be trimmed.
// set: The string containing the set of characters
// to be removed.
// Return value The trimmed string.
// NULL if the allocation fails.
// External functs. malloc
// Description Allocates memory (using malloc(3)) and returns a
// copy of ’s1’ with characters from ’set’ removed
// from the beginning and the end.
	// printf("%zu, %zu", start, end);
	// while (i < ft_strlen(s1))
	// {	
	// 	j = 0;
	// 	while (j < ft_strlen(set))
	// 	{
	// 		if (s1[i] == set[j])
	// 		{
	// 			str[i] = '-';
	// 			//printf("%c != %c\n", s1[i], set[j]);
	// 			//ft_memcpy(str+i, (char *)&s1[i], 1);
	// 		}
	// 		// else
	// 		// printf("%c == %c\n", s1[i], set[j]);
	// 		j++;
	// 	}
	// 	// if (ft_memcmp(s1+i, set, ft_strlen(set)) == 0)
	// 	// {
	// 		//ft_memset((void *)(str+i),'-', ft_strlen(set));
	// 		//ft_memcpy(str, s1+i, i+ft_strlen(set));			
	// 		// printf("%zu\n", i);
	// 		// start = i;
	// 	// }
	// 	i++;
	// 	// if (i == ft_strlen(set) && j != ft_strlen(s1))
	// 		// i = 0;
	// }
	// printf("%s", ft_strchr(str, '-'));
	//printf("%zu", start);
	// ft_memcpy(str, s1+ft_strlen(set), ft_strlen(s1) - start);
	// return (str);
// }