/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:34 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/16 11:00:37 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// La función que se ejecuta cada vez que se pulsa una tecla
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;

	// Convertimos el puntero genérico de vuelta a un puntero de nuestro struct
	fractal = (t_fractal *)param;

	// Comprobamos si la tecla pulsada es ESC y si la acción es 'PRESS'
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		// Si es así, cerramos la ventana de forma segura
		mlx_close_window(fractal->mlx);
	}
}