/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:15:51 by jperez-m          #+#    #+#             */
/*   Updated: 2025/05/27 17:16:48 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_printptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += write(1, "%", 1);
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_length += ft_format(args, str[i]);
		}
		else
		{
			write(1, &str[i], 1);
			print_length++;
		}
		i++;
	}
	va_end(args);
	return (print_length);
}

/*int main ()
{
	int a = 42;
	char *str = "Hello, World!";
	void *ptr = &a;

	ft_printf("Character: %c\n", 'A');
	ft_printf("String: %s\n", str);
	ft_printf("Pointer: %p\n", ptr);
	ft_printf("Decimal: %d\n", a);
ft_printf("Unsigned: %u\n", (unsigned int)a);
	ft_printf("Hexadecimal (lowercase): %x\n", (unsigned int)a);
	ft_printf("Hexadecimal (uppercase): %X\n", (unsigned int)a);
	ft_printf("Percent sign: %%\n");

	return 0;
}
*/
