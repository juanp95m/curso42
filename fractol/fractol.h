/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:31:05 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/20 12:34:36 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080
# define MAX_ITERATIONS 100

// Constantes para zoom
# define ZOOM_IN_FACTOR 0.9
# define ZOOM_OUT_FACTOR 1.1

// Valores por defecto del plano complejo
# define DEFAULT_MIN_R -2.0
# define DEFAULT_MAX_R 2.0
# define DEFAULT_MIN_I -2.0
# define DEFAULT_MAX_I 2.0

// Enum para el tipo de fractal
typedef enum e_fractal_type
{
	FRACTAL_MANDELBROT,
	FRACTAL_JULIA
}	t_fractal_type;

typedef struct s_fractal
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			*name;
	t_fractal_type	type;
	double			min_r;
	double			max_r;
	double			min_i;
	double			max_i;
	double			julia_r;
	double			julia_i;
	int				needs_render;
}	t_fractal;

// --- Prototipos de funciones ---

// init.c
void	init_fractal(t_fractal *fractal);

// render.c
void	render_fractal(t_fractal *fractal);

// mandelbrot.c
int		calculate_mandelbrot(double c_r, double c_i);

// julia.c
int		calculate_julia(double z_r, double z_i, t_fractal *fractal);

// hooks.c
void	key_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

// events.c
void	zoom(t_fractal *fractal, double zoom_factor);
void	scroll_hook(double xdelta, double ydelta, void *param);
void	render_loop(void *param);

// utils.c
double	map(double unscaled_num, double new_min, double new_max, double old_max);
double	ft_atof(const char *str);

// colors.c
int		get_color(int iterations);
int		interpolate_color(int iterations, int color1, int color2);

#endif