/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:23:06 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/15 17:08:28 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Prototipo de la función map
static double map(double unscaled_num, double new_min, double new_max, double old_max);

// Definimos el número máximo de iteraciones

//  Calcula si un punto (c_r, c_i) pertenece al conjunto de Mandelbrot.
//	Devuelve el número de iteraciones que tardó en escapar.
static int	calculate_mandelbrot(double c_r, double c_i)
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

//Se encarga de la lógica para un solo píxel
static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	double	c_r;
	double	c_i;
	int		iterations;
	int		color;

	// 1. Mapear el píxel a un número complejo
	c_r = map(x, fractal->min_r, fractal->max_r, WIDTH);
	c_i = map(y, fractal->max_i, fractal->min_i, HEIGHT);

	// 2. Calcular las iteraciones para ese punto
	iterations = calculate_mandelbrot(c_r, c_i);

	// 3. Asignar un color
	if (iterations == MAX_ITERATIONS)
		color = 0x000000FF; // Negro
	else
		color = 0x0000FFFF * (iterations % 255); // Colorido

	// 4. Pintar el píxel
	mlx_put_pixel(fractal->img, x, y, color);
}

// RENDER_FRACTAL AHORA ES MUCHO MÁS CORTA Y LIMPIA
void	render_fractal(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
}


// Asegúrate de mantenerla en tu archivo.
static double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * unscaled_num / old_max + new_min);
}

