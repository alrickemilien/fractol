/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 11:55:06 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 10:25:07 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int		get_imaginary_number_module(t_z z)
{
	return (z.re * z.re + z.im * z.im);
}

static int		mandelbrot_set_color(t_env *env, int color, int x, int y)
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

	while (n < env->max_iteration && get_imaginary_number_module(new) <= 4)
	{
		old.re = new.re;
		old.im = new.im;
		new.re = old.re * old.re - old.im * old.im + pixel.re;
		new.im = 2 * old.re * old.im + pixel.im;
		color -= n * n << n;
		n++;
	}

	return (color);
}

void			*mandelbrot_set(void *void_env)
{
	int			x;
	int			y;
	t_env		*env;

	env = (t_env*)void_env;
	y = 0;
	while (y < DEFAULT_WINDOW_HEIGHT)
	{
		x = env->thread_index * DEFAULT_WINDOW_WIDTH / 4;
		while (x < env->thread_index * DEFAULT_WINDOW_WIDTH / 4 + DEFAULT_WINDOW_WIDTH / 4)
		{
			if (x < DEFAULT_WINDOW_WIDTH && y < DEFAULT_WINDOW_HEIGHT && x > 0 && y > 0)
				put_pixel_to_image(env, x, y, split_color(
					mlx_get_color_value(X_SERVER,
						mandelbrot_set_color(env, 0x00FFFFFF, x, y))));
			x++;
		}
		y++;
	}
	return (NULL);
}
