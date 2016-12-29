#include "includes/fractol.h"
#include "includes/julia_set.h"
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
	env->constante.re = (env->cursor.x - WIN_WIDTH / 2) * 0.0015;
	env->constante.im = (env->cursor.y - WIN_HEIGHT / 2) * 0.0015;
//	printf("Re :%lf\nIm : %lf\n\n", env->constante.re, env->constante.im);
//	printf("Voici mon index de thread %d : \n", env->thread_index);
	y = 0;
	while(y < WIN_HEIGHT)
	{
		x = env->thread_index * WIN_WIDTH / 4;
		while(x < env->thread_index * WIN_WIDTH / 4 + WIN_WIDTH / 4)
		{
			new.re = ((double)(3 * (x - WIN_WIDTH / 2))) / ((double)(env->image->zoom * WIN_WIDTH));
			new.im = (double)(2 * (y - WIN_HEIGHT / 2)) / ((double)(env->image->zoom * WIN_HEIGHT));
			n = 0;
			color = 0x00FFFFFF;
			while (n < env->max_iter && ft_module(new) <= 4)
			{	
				old.re = new.re;
				old.im = new.im;
				new.re = old.re * old.re - old.im * old.im + env->constante.re;
				new.im = 2 * old.re * old. im + env->constante.im;
				if(x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
					put_pixel_to_image(env->image, x, y, split_color(mlx_get_color_value(env->mlx, color)));
				color -= 10000;
				n++;
			}
			x++;
		}
		y++;
	}
	return (NULL);
}
