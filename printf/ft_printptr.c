/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:55:11 by paguiler          #+#    #+#             */
/*   Updated: 2025/05/22 19:03:44 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_puthex(unsigned long n)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		len += ft_puthex(n / 16);
	len += ft_putchar(base[n % 16]);
	return (len);
}

int	ft_printptr(void *ptr)
{
	int	len;

	if (ptr == 0)
		return (write (1, "(nil)", 5));
	len = 0;
	len += write(1, "0x", 2);
	if (ptr == NULL)
	{
		len += write(1, "0", 1);
		return (len);
	}
	len += ft_puthex((unsigned long)ptr);
	return (len);
}
