/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:07:16 by jperez-m          #+#    #+#             */
/*   Updated: 2025/06/26 21:20:56 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	prints_bits(unsigned char octet)
{
	int	i = 7;

	while (i >= 0)
	{
		if ((octet >> i) & 1)
			write (1, "1", 1);
		else
			write (1, "0", 1);
		i--;
	}
}

int main ()
{
	unsigned char octet = 2;
	prints_bits(octet);
	return (0);
}
