/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:23:06 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/23 16:02:58 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	double	c_r;
	double	c_i;
	int		iterations;
	int		color;

	c_r = map(x, fractal->min_r, fractal->max_r, WIDTH);
	c_i = map(y, fractal->max_i, fractal->min_i, HEIGHT);
	if (fractal->type == FRACTAL_MANDELBROT)
		iterations = calculate_mandelbrot(c_r, c_i);
	else
		iterations = calculate_julia(c_r, c_i, fractal);
	color = get_color(iterations);
	mlx_put_pixel(fractal->img, x, y, color);
}

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
