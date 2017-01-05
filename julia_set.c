#include "includes/fractol.h"
#include <stdio.h>

int		ft_module(t_z z)
{
	return (z.re * z.re + z.im * z.im);
}

void	*julia_set(void *void_env)
{
	t_z	old;
	t_z	new;
	int		n;
	int		x;
	int		y;
	int		color;
	t_env	*env;

	env = (t_env*)void_env;
//	printf("Re :%lf\nIm : %lf\n\n", env->constante.re, env->constante.im);
//	printf("Voici mon index de thread %d : \n", env->thread_index);
	y = 0;
	while(y < WIN_HEIGHT)
	{
		x = WIN_WIDTH / 8 * env->thread_index;
		while(x < WIN_WIDTH / 8 * (env->thread_index + 1))
		{
			new.re = ((double)(3 * (x - WIN_WIDTH_HALF))) / ((double)(env->image->zoom * WIN_WIDTH)) + env->offset.x;
			new.im = (double)(2 * (y - WIN_HEIGHT_HALF)) / ((double)(env->image->zoom * WIN_HEIGHT)) + env->offset.y;
			n = 0;
			color = 0x00FFFFFF;
			while (n < env->max_iter)
			{
				old.re = new.re;
				old.im = new.im;
				new.re = old.re * old.re - old.im * old.im + env->constante.re;
				new.im = 2 * old.re * old. im + env->constante.im;
				
				color -= 10000;
				if (ft_module(new) > 4)
					break ;
				n++;
			}
			if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
				put_pixel_to_image(env->image, x, y, split_color(mlx_get_color_value(env->mlx, color)));
			x++;
		}
		y++;
	}
	return (NULL);
}
