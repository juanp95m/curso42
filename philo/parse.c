/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:09:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/13 14:29:55 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	ft_isspace(int c)
{
	if ((c > 8 && c < 14) || (c == 32))
		return (1);
	return (0);
}

long	ft_atolmax(const char *nptr)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr ++;
	if (*nptr == '-' || *nptr == '+')
	{
        if (*nptr == '-')
		    sign = -1;
		nptr ++;
	}
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (-1);
		result = result * 10 + (*nptr++ - '0');
		if ((result * sign) > INT_MAX)
			return (result);
	}
	return (result * sign);
}

int is_invalid_argument(int argc, char **argv)
{
    int i;
    int num;

    if (argc < 5 || argc > 6)
	{
        printf("invalid arguments number\n");
		return (1);
	}
    i = 1;
    while (i < argc)
    {
        num = ft_atolmax(argv[i]);
        if (num <= 0)
		{
			printf("arguments must be a integer number bigger than 0 \n");
			return (1);
		}
        i++;
    }
    return (0);
}

