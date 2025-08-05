/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:23:37 by jperez-m          #+#    #+#             */
/*   Updated: 2025/07/25 12:35:52 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	str_capitalizer(char *str)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		if (str[i] >= 'a' && str[i] <= 'z' && str[i + 1] < 33 && str[i - 1] < 33)
			str[i] = str[i] - 32;
		if ((str[i] >= 'a' && str[i] <= 'z') && (str[i - 1] < 33))
			str[i] = str[i] - 32;
		write(1, &str[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)

{
	int	i = 1;
	
	if (argc == 1)
		write(1, "\n", 1);
	while (argc > i)
	{
		str_capitalizer(argv[i]);
		write(1, "\n", 1);
		i++;
	}
}