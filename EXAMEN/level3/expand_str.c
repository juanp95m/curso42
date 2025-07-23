/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:26:53 by jperez-m          #+#    #+#             */
/*   Updated: 2025/07/23 11:33:59 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int	i = 0;
		char *str = argv[1];
		while (str[i] && str[i] <= 32)
			i++;
		while (str[i])
		{
			if (str[i] > 32)
				write (1, &str[i], 1);
			else if (str[i + 1] && str[i + 1] > 32)
				write (1, "   ", 3);
			i++;
		}
	}
	write (1, "\n", 1);
}
