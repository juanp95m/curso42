/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:29:06 by jperez-m          #+#    #+#             */
/*   Updated: 2025/06/26 20:03:29 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	neg;
	int	result;

	neg = 1;
	result = 0;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{	
		if (*str == '-')
			neg = -neg;
		str++;
	}
	while (*str >= '0' && *str <= '9')
       	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * neg);
}

int	main()
{
	printf("%d", ft_atoi("	-1234		"));
	return (0);
}
