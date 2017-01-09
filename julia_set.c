/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 12:25:42 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/09 13:06:53 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int			ft_module(t_z z)
{
	return (z.re * z.re + z.im * z.im);
}

static int	julia_iter(t_env *env, int color, int x, int y)
{
	int		n;
	t_z		old;
	t_z		new;

	new.re = ((double)(3 * (x - WIN_WIDTH_HALF))) /
		((double)(env->image->zoom * WIN_WIDTH)) + env->offset.x;
	new.im = (double)(2 * (y - WIN_HEIGHT_HALF)) /
		((double)(env->image->zoom * WIN_HEIGHT)) + env->offset.y;
	n = 0;
	while (n < env->max_iter)
	{
		old.re = new.re;
		old.im = new.im;
		new.re = old.re * old.re - old.im * old.im + env->constante.re;
		new.im = 2 * old.re * old.im + env->constante.im;
		color -= 8000;
		if (ft_module(new) > 4)
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
	while (y < WIN_HEIGHT)
	{
		x = WIN_WIDTH / 8 * env->thread_index;
		while (x < WIN_WIDTH / 8 * (env->thread_index + 1))
		{
			if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
				put_pixel_to_image(env->image, x, y,
				split_color(mlx_get_color_value(env->mlx,
					julia_iter(env, 0x00FFFFFF, x, y))));
			x++;
		}
		y++;
	}
	return (NULL);
}
