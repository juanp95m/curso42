/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:24 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/20 12:08:23 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Interpola entre dos colores basándose en el número de iteraciones
** color1 y color2 deben estar en formato RGBA (0xRRGGBBAA)
** Retorna un color intermedio entre color1 y color2
*/
int	interpolate_color(int iterations, int color1, int color2)
{
	int		r;
	int		g;
	int		b;
	double	factor;

	factor = (double)(iterations % 50) / 50.0;
	r = ((color1 >> 24) & 0xFF) * (1 - factor) + ((color2 >> 24) & 0xFF) * factor;
	g = ((color1 >> 16) & 0xFF) * (1 - factor) + ((color2 >> 16) & 0xFF) * factor;
	b = ((color1 >> 8) & 0xFF) * (1 - factor) + ((color2 >> 8) & 0xFF) * factor;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/*
** Genera un color basado en el número de iteraciones
** Si llegó a MAX_ITERATIONS, el punto está dentro del conjunto (negro)
** Si no, genera un gradiente de colores
*/
int	get_color(int iterations)
{
	int	color1;
	int	color2;

	if (iterations == MAX_ITERATIONS)
		return (0x000000FF);
	color1 = 0x0000FFFF;
	color2 = 0xFF00FFFF;
	return (interpolate_color(iterations, color1, color2));
}
