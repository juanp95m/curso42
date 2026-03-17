/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:07:41 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/07 19:20:13 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	shiftasciif(unsigned int i,char c)
// {
// 	char new;

// 	new = c + i;
// 	return (new);
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
// #include <stdio.h>
// int	main(void)
// {
// 	char *str = "abc";
// 	printf("%s\n", str);
// 	ft_striteri(str, shiftasciif);
// 	printf("%s\n", str);
// 	return (0);
// }