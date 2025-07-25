/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parasum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:14:22 by jperez-m          #+#    #+#             */
/*   Updated: 2025/07/24 17:24:29 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	char digit = (n % 10) + '0';
	write (1, &digit, 1);
}

int main (int argc, char **argv)
{
	(void)argv;

	ft_putnbr(argc - 1);
	write (1, "\n", 1);
	return (0);
}
