#include "fractol.h"

void	init_fractal(t_fractal *fractal)
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
	fractal->min_r = -2.0;
	fractal->max_r = 2.0;
	fractal->min_i = -2.0;
	fractal->max_i = 2.0;
}