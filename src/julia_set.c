/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 12:25:42 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 12:32:37 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			get_imaginary_number_module(t_z z)
{
	return (z.re * z.re + z.im * z.im);
}

static int	julia_iter(t_env *env, int color, int x, int y)
{
	int		n;
	t_z		old;
	t_z		new;

	new.re = ((double)(3 * (x - DEFAULT_WINDOW_WIDTH / 2))) /
		((double)(env->zoom * DEFAULT_WINDOW_WIDTH)) + env->offset.x;

	new.im = (double)(2 * (y - DEFAULT_WINDOW_HEIGHT / 2)) /
		((double)(env->zoom * DEFAULT_WINDOW_HEIGHT)) + env->offset.y;

	n = 0;
	while (n < env->max_iteration)
	{
		old.re = new.re;
		old.im = new.im;
		new.re = old.re * old.re - old.im * old.im + env->constante.re;
		new.im = 2 * old.re * old.im + env->constante.im;
		color -= n * n << n;
		if (get_imaginary_number_module(new) > 4)
			break ;
		n++;
	}
	return (color);
}

void		*julia_set(void *void_env)
{
	int		x;
	int		y;
	t_env	*env;

	env = (t_env*)void_env;
	y = 0;
	while (y < DEFAULT_WINDOW_HEIGHT)
	{
		x = (DEFAULT_WINDOW_WIDTH / NUMBER_OF_THREADS) * env->thread_index;
		while (x < (DEFAULT_WINDOW_WIDTH / NUMBER_OF_THREADS) * (env->thread_index + 1))
		{
			if (x < DEFAULT_WINDOW_WIDTH && y < DEFAULT_WINDOW_HEIGHT && x > 0 && y > 0)
				put_pixel_to_image(env, x, y,

				split_color(mlx_get_color_value(X_SERVER, julia_iter(env, 0x00FFFFFF, x, y))));
			x++;
		}
		y++;
	}
	return (NULL);
}
