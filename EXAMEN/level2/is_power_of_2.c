/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:39:36 by jperez-m          #+#    #+#             */
/*   Updated: 2025/07/09 12:48:41 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	is_power_of_2(unsigned int n)
{
	unsigned int	test = 1;

	while (test <= n)
	{
		if (test == n)
			return (1);
		test = test * 2;
	}
	return (0);
}
while (test < n)
	test *= 2;
return (test == n)
int main ()
{
	int x = is_power_of_2(15);
	printf("%d", x);
}
