/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:17:10 by jperez-m          #+#    #+#             */
/*   Updated: 2025/05/01 20:34:45 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*temp;
	char	*temp2;

	temp = (char *) src;
	temp2 = (char *) dst;
	i = 0;
	if (temp == NULL && temp2 == NULL)
		return (NULL);
	while (i < n)
	{
		temp2[i] = temp[i];
		i++;
	}
	return (dst);
}
