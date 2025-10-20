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

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	double	c_r;
	double	c_i;
	int		iterations;
	int		color;

	c_r = map(x, fractal->min_r, fractal->max_r, WIDTH);
	c_i = map(y, fractal->max_i, fractal->min_i, HEIGHT);
	if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
		iterations = calculate_mandelbrot(c_r, c_i);
	else if (ft_strncmp(fractal->name, "julia", 5) == 0)
		iterations = calculate_julia(c_r, c_i, fractal);
	else
		iterations = 0;
	if (iterations == MAX_ITERATIONS)
		color = 0x000000FF;
	else
		color = (0xFF0000FF | (iterations * 16 << 24) | (iterations * 8 << 16));
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

