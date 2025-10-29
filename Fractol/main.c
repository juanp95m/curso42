/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:31:08 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/28 19:45:45 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	show_error_message(void)
{
	ft_putendl_fd("Error: Invalid parameters.", 2);
	ft_putendl_fd("Usage: ./fractol mandelbrot", 2);
	ft_putendl_fd("       ./fractol julia <real> <imaginary>", 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd("Julia parameters examples:", 2);
	ft_putendl_fd("  ./fractol julia -0.4 0.6     (spiral)", 2);
	ft_putendl_fd("  ./fractol julia 0.285 0.01   (dendrites)", 2);
	ft_putendl_fd("  ./fractol julia -0.70176 -0.3842  (lightning)", 2);
	ft_putendl_fd("  ./fractol julia -0.835 -0.2321  (dragon)", 2);
	ft_putendl_fd("  ./fractol julia -0.8 0.156    (galaxy)", 2);
	exit(EXIT_FAILURE);
}

static void	validate_julia_params(char **argv, t_fractal *fractal)
{
	if (!is_valid_number(argv[2]) || !is_valid_number(argv[3]))
		show_error_message();
	fractal->julia_r = ft_atof(argv[2]);
	fractal->julia_i = ft_atof(argv[3]);
	if (fractal->julia_r < -2.0 || fractal->julia_r > 2.0
		|| fractal->julia_i < -2.0 || fractal->julia_i > 2.0)
		show_error_message();
}

static void	parse_args(int argc, char **argv, t_fractal *fractal)
{
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		fractal->type = FRACTAL_MANDELBROT;
		fractal->julia_r = 0.0;
		fractal->julia_i = 0.0;
	}
	else if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		fractal->type = FRACTAL_JULIA;
		validate_julia_params(argv, fractal);
	}
	else
		show_error_message();
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	parse_args(argc, argv, &fractal);
	init_fractal(&fractal);
	mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
	mlx_loop_hook(fractal.mlx, &render_loop, &fractal);
	mlx_key_hook(fractal.mlx, &key_hook, &fractal);
	mlx_scroll_hook(fractal.mlx, &scroll_hook, &fractal);
	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
