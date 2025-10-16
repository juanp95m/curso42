/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:01:04 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/16 11:01:05 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_mandelbrot(double c_r, double c_i)
{
	double	z_r;
	double	z_i;
	double	temp;
	int		i;

	z_r = 0;
	z_i = 0;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		if ((z_r * z_r + z_i * z_i) > 4.0)
			return (i);
		temp = z_r * z_r - z_i * z_i;
		z_i = 2 * z_r * z_i;
		z_r = temp;
		z_r += c_r;
		z_i += c_i;
		i++;
	}
	return (MAX_ITERATIONS);
}