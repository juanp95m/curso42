/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:01:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/28 19:35:26 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	result;
	double	divisor;
	int		sign;

	sign = get_sign(&str);
	result = 0.0;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		divisor = 1.0;
		while (ft_isdigit(*str))
		{
			divisor *= 10.0;
			result = result + (*str++ - '0') / divisor;
		}
	}
	return (sign * result);
}

static int	validate_decimals(const char *str, int i, int *has_digit)
{
	int	decimals;

	decimals = 0;
	i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]) && ++decimals <= 6)
	{
		*has_digit = 1;
		i++;
	}
	if (decimals > 6 || ft_isdigit(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == '\0');
}

int	is_valid_number(const char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '.')
		return (0);
	while (ft_isdigit(str[i]))
	{
		has_digit = 1;
		i++;
	}
	if (str[i] == '.')
		return (validate_decimals(str, i, &has_digit));
	while (ft_isspace(str[i]))
		i++;
	return (has_digit && str[i] == '\0');
}
