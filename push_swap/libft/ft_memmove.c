/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:56:10 by jperez-m          #+#    #+#             */
/*   Updated: 2025/04/30 19:35:43 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*temp1;
	char	*temp2;

	temp1 = (char *) src;
	temp2 = (char *) dst;
	i = 0;
	if (temp2 > temp1)
	{
		i = n;
		while (i > 0)
		{
			i--;
			temp2[i] = temp1[i];
		}
	}
	else
	{
		ft_memcpy(dst, src, n);
	}
	return (dst);
}
