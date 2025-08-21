/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizz_buzz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:30:24 by jperez-m          #+#    #+#             */
/*   Updated: 2025/06/17 16:46:59 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	putnbr(int n)
{
	if (n > 9)
	{
		putnbr(n / 10);
	}
	char digit = (n % 10) + '0';
	write (1, &digit, 1);
}

int main (void)
{
	int	i;
	i = 1;
	while (i <= 100)
	{
		if (i % 15 == 0)
			write (1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write (1, "fizz", 4);
		else if (i % 5 == 0)
			write (1, "buzz", 4);
		else
			putnbr(i);
		write (1, "\n", 1);
		i++;
	}
	return (0);
}
