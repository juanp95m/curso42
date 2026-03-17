/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:23:36 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/05 20:23:38 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <limits.h>

static long int	count_digits(int n)
{
	long int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		n = -n;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*create_memory(int size)
{
	char	*array;

	array = (char *)ft_calloc(sizeof(char), size + 1);
	if (!array)
	{
		free(array);
		return (NULL);
	}
	return (array);
}

static void	add_nbr(long int nb, char *array, int size)
{
	if (nb < 0)
	{
		array[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		array[0] = '0';
	array[size] = '\0';
	size--;
	while (nb)
	{
		array[size] = (nb % 10) + '0';
		size--;
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char		*array;
	int			size;
	long int	nb;

	nb = n;
	size = count_digits(nb);
	if (nb < 0)
		size += 1;
	array = create_memory(size);
	if (!array)
		return (0);
	add_nbr(nb, array, size);
	return (array);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char *res;

// 	res = ft_itoa(-INT_MAX - 1);
// 	printf("%s", res);
// 	free(res);
// 	return (0);
// }