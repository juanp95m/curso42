/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:27:00 by jperez-m          #+#    #+#             */
/*   Updated: 2025/07/08 15:48:36 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		if (argv[2][0] == '*')
			printf("%d", atoi(argv[1]) * atoi(argv[3]));
		else if (argv[2][0] == '+')
			printf("%d", atoi(argv[1]) + atoi(argv[3]));
		else if (argv[2][0] == '-')
			printf("%d", atoi(argv[1]) - atoi(argv[3]));
		else if (argv[2][0] == '/')
			printf("%d", atoi(argv[1]) / atoi(argv[3]));
		else
			printf("%d", atoi(argv[1]) % atoi(argv[3]));
	}
	printf("\n");
}
