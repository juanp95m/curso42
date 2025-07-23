/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:37:07 by jperez-m          #+#    #+#             */
/*   Updated: 2025/06/25 19:40:51 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
	       i++;
	return (s1[i] - s2[i]);
}

int	main(void)
{
	char	str1[] = "abcddd";
	char	str2[] = "abc";
	int	result;
	result = ft_strcmp(str1, str2);
	printf("%d", result);
	return (0);
}
