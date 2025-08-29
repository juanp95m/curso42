/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:00:44 by jperez-m          #+#    #+#             */
/*   Updated: 2025/08/29 10:32:59 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		int	i = 0;
		int	j = 0;

		while (argv[1][i] && argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
				i++;
			j++;
		}
	
		if (argv[1][i] == 0)
			write (1, "1", 1);
		else
			write (1, "0", 1);
	}
	write(1, "\n", 1);
}