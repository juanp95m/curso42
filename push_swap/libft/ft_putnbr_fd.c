/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:30:46 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:30:48 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	n;
	long	divisor;
	int		digit;

	n = nb;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	divisor = 1;
	while (n / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		digit = n / divisor;
		ft_putchar_fd(digit + '0', fd);
		n %= divisor;
		divisor /= 10;
	}
}
