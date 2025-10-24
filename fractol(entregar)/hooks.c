/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:34 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/24 12:20:21 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractal->mlx);
}
