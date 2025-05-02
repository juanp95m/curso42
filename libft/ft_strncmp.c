/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:41:27 by jperez-m          #+#    #+#             */
/*   Updated: 2025/05/01 14:07:54 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *) s1;
	temp2 = (unsigned char *) s2;
	i = 0;
	while (temp1[i] && temp2[i] && i < n)
	{
		if (temp1[i] != temp2[i])
			return (temp1[i] - temp2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (temp1[i] - temp2[i]);
}
