/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:43:26 by paguiler          #+#    #+#             */
/*   Updated: 2025/05/22 19:03:36 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_format(va_list args, const char format);
int	ft_printchar(char c);
int	ft_printstr(char *s);
int	ft_printptr(void *ptr);
int	ft_printnbr(int n);
int	ft_print_unsigned(unsigned int n);
int	ft_printhex(unsigned int n, char format);

#endif
