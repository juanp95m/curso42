/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:20:17 by paguiler          #+#    #+#             */
/*   Updated: 2025/05/22 19:03:26 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int n)
{
	int		printed_chars;
	char	digit;

	printed_chars = 0;
	if (n > 9)
		printed_chars += ft_print_unsigned(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);
	printed_chars++;
	return (printed_chars);
}
