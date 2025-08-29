/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:20:41 by jperez-m          #+#    #+#             */
/*   Updated: 2025/08/28 18:54:25 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{
	octet = (octet >> 4) | (octet << 4);
	octet = ((0b11001100 & octet) >> 2) | ((0b00110011 & octet) << 2);
	octet = ((0b10101010 & octet) >> 1) | ((0b00110011 & octet) << 1);
	return (octet);
}

void	ft_printbits(unsigned char octet)
{
	int i = 7;
	while (i >= 0)
	{
		if (octet >> i & 1)
			write(1, "1", 1);
		else
			write (1, "0", 1);
		i--;
	}
}

int main (void)
{
    unsigned char test = 225; // 11100001 en binario
    unsigned char result = reverse_bits(test);
    ft_printbits(test);
	write (1, "\n", 1);
    ft_printbits(result);
	write (1, "\n", 1);
    return 0;
}
