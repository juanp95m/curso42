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

void	str_capitalizer(char *str)
{
	int	i = 0;
	int	new_word = 1;
	while (str[i])
	{
		// Convertir a minúscula si es letra mayuscula
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		// Capitalizar si es inicio de palabra
		if (str[i] >= 'a' && str[i] <= 'z' && new_word)
			str[i] = str[i] - 32;
		// Detectar separador para próxima palabra
		if (str[i] == ' ' || str[i] == '\t')
			new_word = 1;
		else
			new_word = 0;
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