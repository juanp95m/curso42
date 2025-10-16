/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:31:05 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/15 17:08:56 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITERATIONS 100

typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		*name;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	double		julia_r;
	double		julia_i;
}	t_fractal;

// --- Prototipos de funciones ---

// init.c
void	init_fractal(t_fractal *fractal);

// render.c
void	render_fractal(t_fractal *fractal);

// mandelbrot.c
int		calculate_mandelbrot(double c_r, double c_i);

// hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);

// utils.c
double	map(double unscaled_num, double new_min, double new_max, double old_max);

#endif