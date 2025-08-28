/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:32 by jperez-m          #+#    #+#             */
/*   Updated: 2025/08/28 16:06:40 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	lcm(unsigned int a, unsigned int b)
{
	unsigned int	n;
	
	if (a == 0 || b == 0)
	       return (0);
	else if (a > b)
		n = a;
	else
		n = b;
	while (1)
	{
		if (n % a == 0 && n % b == 0)
			return (n);
		n++;	
	}
}

#include <stdio.h>

int main(void)
{
	printf("%d\n", lcm(6, 8));
	return 0;
}
