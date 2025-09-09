/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:08:06 by jperez-m          #+#    #+#             */
/*   Updated: 2025/05/05 17:35:36 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	if (dstsize == 0)
		return (j);
	i = 0;
	while ((src[i] != '\0') && (i < dstsize -1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = ('\0');
	return (j);
}
