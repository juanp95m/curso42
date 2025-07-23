/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:08:17 by jperez-m          #+#    #+#             */
/*   Updated: 2025/07/08 19:59:21 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

unsigned char reverse_bits(unsigned char octet)
{
	octet = (octet >> 4) | (octet << 4);
	octet = ((0b11001100 & octet) >> 2) | ((0b00110011 & octet) << 2);
    octet = ((0b10101010 & octet) >> 1) | ((0b01010101 & octet) << 1);
	return (octet);	
}
int main() 
{
    unsigned char test = 225; // 11100001 en binario
    unsigned char result = reverse_bits(test);
    printf("Original: %d, Reversed: %d\n", test, result);
    return 0;
}