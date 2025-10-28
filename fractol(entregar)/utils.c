/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:01:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/28 13:31:49 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (unscaled_num / old_max) + new_min);
}

static long	parse_integer(const char **str)
{
	long	result;

	result = 0;
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_decimal(const char **str)
{
	double	result;
	double	divisor;

	result = 0.0;
	divisor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			result = result * 10.0 + (**str - '0');
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (result / divisor);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;

	sign = 1;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = (double)parse_integer(&str);
	result += parse_decimal(&str);
	return (sign * result);
}

int	is_valid_number(const char *str)
{
	int i;
	int has_digit;
	int dot_count;
	int decimals;
	int after_dot;

	i = 0;
	has_digit = 0;
	dot_count = 0;
	decimals = 0;
	after_dot = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	/* disallow leading dot (e.g. ".5") to keep parsing simple */
	if (str[i] == '.')
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (ft_isdigit(str[i]))
		{
			has_digit = 1;
			if (after_dot)
				decimals++;
		}
		else if (str[i] == '.')
		{
			if (++dot_count > 1)
				return (0);
			after_dot = 1;
		}
		else
			return (0);
		i++;
	}
	/* enforce maximum decimals */
	if (decimals > MAX_DECIMALS)
		return (0);
	return (has_digit);
}
