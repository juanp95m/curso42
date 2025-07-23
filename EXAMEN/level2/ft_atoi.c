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
	int	i;
	int	simbol;
	int	result;

	i = 0;
	simbol = 1;
	result = 0;

	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{	
		if (str[i] == '-')
			simbol *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
       	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * simbol);
}

int	main()
{
	printf("%d", ft_atoi("	-1234		"));
	return (0);
}
