/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:46 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/20 13:28:21 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_julia(double z_r, double z_i, t_fractal *fractal)
{
	double	temp;
	int		i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		if ((z_r * z_r + z_i * z_i) > 4.0)
			return (i);
		temp = z_r * z_r - z_i * z_i;
		z_i = 2 * z_r * z_i;
		z_r = temp;
		z_r += fractal->julia_r;
		z_i += fractal->julia_i;
		i++;
	}
	return (MAX_ITERATIONS);
}
