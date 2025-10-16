/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:31:08 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/15 13:25:12 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(void)
{
	t_fractal	fractal;

	init_fractal(&fractal);
	render_fractal(&fractal);
	mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);

	// Ahora registramos el hook para las teclas
	mlx_key_hook(fractal.mlx, &key_hook, &fractal);

	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
