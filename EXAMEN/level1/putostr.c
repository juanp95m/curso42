/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putostr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:12:01 by jperez-m          #+#    #+#             */
/*   Updated: 2025/06/18 17:30:31 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
}

int	main (void)
{
	char	string[20] = "holaaa";
	ft_putstr(string);
	return (0);
}
