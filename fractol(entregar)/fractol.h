/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:31:05 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/28 11:18:51 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATIONS 100

/* Zoom constants */
# define ZOOM_IN_FACTOR 0.9
# define ZOOM_OUT_FACTOR 1.1

/* Default values for the complex plane */
# define DEFAULT_MIN_R -2.0
# define DEFAULT_MAX_R 2.0
# define DEFAULT_MIN_I -2.0
# define DEFAULT_MAX_I 2.0

/* Validation limits */
# define MAX_DECIMALS 12 /* Máximo de decimales permitidos en parámetros numéricos */

/* Enum for fractal type */
typedef enum e_fractal_type
{
	FRACTAL_MANDELBROT,
	FRACTAL_JULIA
}	t_fractal_type;

typedef struct s_fractal
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_fractal_type	type;
	double			min_r;
	double			max_r;
	double			min_i;
	double			max_i;
	double			julia_r;
	double			julia_i;
	int				needs_render;
}	t_fractal;

/* Function prototypes */

/* init.c */
void	init_fractal(t_fractal *fractal);

/* render.c */
void	render_fractal(t_fractal *fractal);

/* mandelbrot.c */
int		calculate_mandelbrot(double c_r, double c_i);

/* julia.c */
int		calculate_julia(double z_r, double z_i, t_fractal *fractal);

/* hooks.c */
void	key_hook(mlx_key_data_t keydata, void *param);
void	zoom(t_fractal *fractal, double zoom_factor);
void	scroll_hook(double xdelta, double ydelta, void *param);
void	render_loop(void *param);

/* utils.c */
double	map(double unscaled_num, double new_min,
			double new_max, double old_max);
double	ft_atof(const char *str);
int		is_valid_number(const char *str);

/* colors.c */
int		get_color(int iterations);
int		interpolate_color(int iterations, int color1, int color2);

#endif