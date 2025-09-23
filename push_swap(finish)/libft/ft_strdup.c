/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:10 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:31:12 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	duplicate = (char *)malloc(sizeof(char) * (len + 1));
	if (duplicate == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i <= len)
	{
		duplicate[i] = s[i];
		i++;
	}
	return (duplicate);
}
