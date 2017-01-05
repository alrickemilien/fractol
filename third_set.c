#include "includes/fractol.h"

static int		ft_module(t_z z)
{
		return (z.re * z.re + z.im * z.im);
}

void	*burningship_set(void *void_env)
{
	t_z	old;
	t_z	new;
	t_z	pixel;
	int		n;
	int		x;
	int		y;
	int		color;
	t_env	*env;

	env = (t_env*)void_env;
	y = 0;
	while(y < WIN_HEIGHT)
	{
		x = env->thread_index * WIN_WIDTH / 4;
		while(x < env->thread_index * WIN_WIDTH / 4 + WIN_WIDTH / 4)
		{
			pixel.re = ((double)(3 * (x - WIN_WIDTH / 2))) / ((double)(env->image->zoom * WIN_WIDTH));
			pixel.im = ((double)(2 * (y - WIN_HEIGHT / 2))) / ((double)(env->image->zoom * WIN_HEIGHT));
			new.re = 0;
			new.im = 0;
			old.re = 0;
			old.im = 0;
			n = 0;
			color = 0x00FFFFFF;
			while (n < env->max_iter && ft_module(new) <= 4)
			{	
				old.re = fabs(new.re);
				old.im = fabs(new.im);
				new.re = old.re * old.re - old.im * old.im + pixel.re;
				new.im = 2 * old.re * old. im + pixel.im;
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
