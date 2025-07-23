/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:01:21 by jperez-m          #+#    #+#             */
/*   Updated: 2025/06/17 20:27:24 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int argc, char **argv)
{
	if (argc == 2)
	{
		int	i;
		int	j;
		i = 0;
		while (argv[1][i])
		{
			if (argv[1][i] >= 65 && argv[1][i] <= 90)
			{
				j = 0;
				while (j < argv[1][i] - 64)
				{
					write(1, &argv[1][i], 1);
					j++;
				}
			}

			else if (argv[1][i] >= 97 && argv[1][i] <= 122)
			{	
				j = 0;
				while (j < argv[1][i] - 96)
				{
					write(1, &argv[1][i], 1);
					j++;
				}
			}
			else
				write(1, &argv[1][i], 1);
			i++;
		}	
		write(1, "\n", 1);
		return (0);
		}
}
