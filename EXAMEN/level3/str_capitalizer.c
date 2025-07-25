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

void	r_capitalizer(char *s)
{
	int	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z' && s[i + 1] < 33 && s[i - 1])
		{	
			s[i] -= 32;
			write (1, &s[i], 1);
		}
		else if (s[i] >= 'a' && s[i] <= 'z' && s[i + 1] < 33)
		{	
			s[i] -= 32;
			write (1, &s[i], 1);
		}
		else 
			write (1, &s[i], 1);

		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i = 1;
	if (argc > 1)
	{
		while (i <= argc - 1)
		{
			r_capitalizer(argv[i]);
			write (1, "\n", 1);
			i++;	
		}	
		
	}
	else
		write (1, "\n", 1);
	return (0);
}
