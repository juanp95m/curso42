/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:57:52 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/18 00:00:00 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_fractal *fractal, double zoom_factor)
{
	double	center_r;
	double	center_i;
	double	range_r;
	double	range_i;

	center_r = (fractal->max_r + fractal->min_r) / 2.0;
	center_i = (fractal->max_i + fractal->min_i) / 2.0;
	range_r = (fractal->max_r - fractal->min_r) * zoom_factor;
	range_i = (fractal->max_i - fractal->min_i) * zoom_factor;
	fractal->min_r = center_r - range_r / 2.0;
	fractal->max_r = center_r + range_r / 2.0;
	fractal->min_i = center_i - range_i / 2.0;
	fractal->max_i = center_i + range_i / 2.0;
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	(void)xdelta;
	fractal = (t_fractal *)param;
	if (ydelta > 0)
		zoom(fractal, 0.9);
	else if (ydelta < 0)
		zoom(fractal, 1.1);
	fractal->needs_render = 1;
}

void	render_loop(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (fractal->needs_render)
	{
		render_fractal(fractal);
		fractal->needs_render = 0;
	}
}

