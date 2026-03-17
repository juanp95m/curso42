/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:41:20 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/01 17:41:20 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	size;
	size_t	len;
	char	*dest;

	len = 0;
	while (src[len] != '\0')
		len++;
	size = n;
	if (n < (len + 1))
		size = len + 1;
	dest = (char *)malloc(size);
	if (!dest)
		return (0);
	i = -1;
	while (src && ++i < len)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	dest[i] = '\0';
	return (dest);
}
