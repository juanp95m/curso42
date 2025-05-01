/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:28:54 by jperez-m          #+#    #+#             */
/*   Updated: 2025/04/30 18:39:37 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	temp = (unsigned char *) b;
	i = 0;
	while (i < n)
	{
		temp [i] = c;
		i++;
	}
	b = (void *)temp;
	return (b);
}
