/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:30:31 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:30:33 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	temp = b;
	i = 0;
	while (i < n)
	{
		temp[i] = c;
		i++;
	}
	return (b);
}
