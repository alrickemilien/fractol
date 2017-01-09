/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:22:29 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/09 13:14:45 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	redraw(t_env *env)
{
	free(env->image->data);
	mlx_destroy_image(env->mlx, env->image->img);
	env->image->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->image->width = WIN_WIDTH;
	env->image->height = WIN_HEIGHT;
	threads(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image->img, 0, 0);
	if (env->f == &julia_set)
		display_info_maths(env);
}

int		mouse_motion_hook(int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT && !env->lock)
	{
		env->cursor.x = x;
		env->cursor.x = y;
		env->constante.re = (WIN_WIDTH_HALF - x) * 0.001 - 0.7;
		env->constante.im = (WIN_HEIGHT_HALF - y) * 0.001 + 0.27015;
		redraw(env);
	}
	return (0);
}

int		focus_in(int button, int x, int y, void *param)
{
	t_env	*env;

	button = 0;
	env = (t_env*)param;
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		env->offset.x += -(WIN_WIDTH_HALF - x) * 0.0005 / env->image->zoom;
		env->offset.y += -(WIN_HEIGHT_HALF - y) * 0.0005 / env->image->zoom;
		env->center.x = x;
		env->center.y = y;
		env->image->zoom += 0.1;
		redraw(env);
	}
	return (0);
}

int		key_press(int keycode, void *env)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(((t_env*)env)->mlx,
							((t_env*)env)->win);
		exit(0);
	}
	if (keycode == 49 && !((t_env*)env)->lock)
		((t_env*)env)->lock = 1;
	else if (keycode == 49 && ((t_env*)env)->lock)
		((t_env*)env)->lock = 0;
	if (keycode == 259)
		((t_env*)env)->command = 1;
	if (keycode == 257)
		((t_env*)env)->shift = 1;
	if (keycode == 1 && ((t_env*)env)->command)
		ft_bitmap(((t_env*)env)->image);
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (keycode == 259)
		env->command = 0;
	if (keycode == 257)
		env->shift = 0;
	return (0);
}
