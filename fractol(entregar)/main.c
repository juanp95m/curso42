/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:31:08 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/24 12:20:21 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	show_error_message(void)
{
	ft_putendl_fd("Error: Parámetros inválidos.", 2);
	ft_putendl_fd("Uso: ./fractol mandelbrot", 2);
	ft_putendl_fd("     ./fractol julia <real> <imaginario>", 2);
	exit(EXIT_FAILURE);
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
		fractal->julia_r = ft_atof(argv[2]);
		fractal->julia_i = ft_atof(argv[3]);
	}
	else
	{
		show_error_message();
	}
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
