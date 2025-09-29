/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:36:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/29 13:50:42 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_parse(const char **s, int *sign)
{
	while (**s == ' ' || (**s >= 9 && **s <= 13))
		(*s)++;
	*sign = 1;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*sign = -1;
		(*s)++;
	}
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	long	limit;
	int		digit;

	init_parse(&str, &sign);
	if (sign == 1)
		limit = INT_MAX;
	else
		limit = 2147483648L;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (limit - digit) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

void	free_stack_and_error(t_stack **stack)
{
	free_stack(stack);
	write(2, "Error\n", 6);
	exit(1);
}

void	free_split_local(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
