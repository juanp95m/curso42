/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:26:22 by jperez-m          #+#    #+#             */
/*   Updated: 2025/05/12 20:51:21 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isfromset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] && ft_isfromset(s[start], set))
		start++;
	while (s[end] && ft_isfromset(s[end], set) && start < end)
		end--;
	result = ft_substr(s, start, end - start +1);
	return (result);
}
