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

//libreries
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

// Definimos las dimensiones de la ventana
# define WIDTH 800
# define HEIGHT 600
#define MAX_ITERATIONS 100

typedef struct s_fractal
{
	mlx_t		*mlx; // El puntero a la instancia de MLX42
	mlx_image_t	*img; // El puntero a la imagen que dibujaremos
	char		*name; // El nombre del fractal ("mandelbrot" o "julia")

	// Aquí guardaremos los límites del fractal que se ven en la pantalla
	double		min_r; // La parte real mínima (esquina izquierda)
	double		max_r; // La parte real máxima (esquina derecha)
	double		min_i; // La parte imaginaria mínima (parte de arriba)
	double		max_i; // La parte imaginaria máxima (parte de abajo)

	// Para el fractal de Julia, necesitaremos guardar la constante C
	double		julia_r;
	double		julia_i;

}	t_fractal;

void	render_fractal(t_fractal *fractal);

#endif