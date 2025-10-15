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

// Una función para inicializar los valores de nuestro struct
static void	init_fractal(t_fractal *fractal)
{
	fractal->mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
	if (!fractal->mlx)
		exit(EXIT_FAILURE);
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		mlx_terminate(fractal->mlx);
		exit(EXIT_FAILURE);
	}
	// Establecemos los límites iniciales del fractal
	fractal->min_r = -2.0;
	fractal->max_r = 2.0;
	fractal->min_i = -2.0;
	fractal->max_i = 2.0;
}

int	main(void)
{
	t_fractal	fractal;

	// 1. Inicializamos todos los datos
	init_fractal(&fractal);

	// 2. Dibujamos el fractal en la imagen
	render_fractal(&fractal);

	// 3. Mostramos la imagen en la ventana
	mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);

	// 4. Esperamos a que el usuario haga algo
	mlx_loop(fractal.mlx);

	// 5. Limpiamos al salir
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
