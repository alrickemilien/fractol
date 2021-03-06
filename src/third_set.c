/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 12:40:37 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:12:15 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		ft_module(t_z z)
{
	return (RE(z) * RE(z) + I(z) * I(z));
}

static	int		third_set_color(t_env *env, int color, int x, int y)
{
	t_z			old;
	t_z			new;
	t_z			pixel;
	int			n;

	pixel.re = ((double)(3 * (x - DEFAULT_WINDOW_WIDTH / 2))) /
				((double)(env->zoom * DEFAULT_WINDOW_WIDTH)) + env->offset.x;

	pixel.im = ((double)(2 * (y - DEFAULT_WINDOW_HEIGHT / 2))) /
				((double)(env->zoom * DEFAULT_WINDOW_HEIGHT)) + env->offset.y;

	new.re = 0;
	new.im = 0;
	old.re = 0;
	old.im = 0;

	n = 0;
	while (n < env->max_iteration && ft_module(new) <= 4)
	{
		old.re = new.re;
		old.im = new.im;
		new.re = fabs(old.re * old.re - old.im * old.im + pixel.re);
		new.im = fabs(2 * old.re * old.im + pixel.im);
		color -= n * 1.61 * n / M_PI;
		n++;
	}

	return (color);
}

void			*third_set(void *void_env)
{
	int			x;
	int			y;
	t_env		*env;

	env = (t_env*)void_env;
	y = 0;
	while (y < DEFAULT_WINDOW_HEIGHT)
	{
		x = (DEFAULT_WINDOW_WIDTH / NUMBER_OF_THREADS) * env->thread_index;
		while (x < (DEFAULT_WINDOW_WIDTH / NUMBER_OF_THREADS) * (env->thread_index + 1))
		{
			x = env->thread_index * DEFAULT_WINDOW_WIDTH / 4;
			if (x < DEFAULT_WINDOW_WIDTH && y < DEFAULT_WINDOW_HEIGHT && x > 0 && y > 0)
				put_pixel_to_image(IMAGE, x, y, split_color(
					mlx_get_color_value(X_SERVER,	third_set_color(env, 0x000002AA, x, y))));
			x++;
		}
		y++;
	}
	return (NULL);
}
