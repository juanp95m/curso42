/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:40:54 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/09 14:16:40 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	shiftasciif(unsigned int i,char c)
// {
// 	char new;

// 	new = c + i;
// 	return (new);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	size_t	size;
	char	*array;

	size = ft_strlen(s);
	array = ft_calloc(sizeof(char), size + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		array[i] = f(i, s[i]);
		i++;
	}
	return (array);
}

// static void print_array(char const *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		printf("%c", s[i]);
// 		i++;
// 	}
// }
// #include <stdio.h>
// int	main(void)
// {
// 	char *res;
// 	res = ft_strmapi("abc", shiftasciif);
// 	// printf("%c", shiftasciif(2, 'a'));
// 	// printf("%s", res);
// 	print_array(res);
// 	return (0);
// }