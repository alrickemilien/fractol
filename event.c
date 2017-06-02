/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:22:29 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 12:25:42 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "macro_key_mlx.h"

int			mouse_motion_hook(int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (!env->lock)
	{
		env->cursor.x = x;
		env->cursor.x = y;
		env->constante.re = (WIN_WIDTH_HALF - x) * 0.001 - 0.7;
		env->constante.im = (WIN_HEIGHT_HALF - y) * 0.001 + 0.27015;
		redraw(env);
	}
	return (0);
}

int			focus_in(int button, int x, int y, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		if (button == 5)
		{
			env->image->zoom += 0.1;
			env->offset.x += -(WIN_WIDTH_HALF - x) * 0.0005 / env->image->zoom;
			env->offset.y += -(WIN_HEIGHT_HALF - y) * 0.0005 / env->image->zoom;
			redraw(env);
		}
		else if (button == 4 && env->image->zoom > 0.5)
		{
			env->image->zoom -= 0.1;
			env->offset.x -= (WIN_WIDTH_HALF - x) * 0.0005 / env->image->zoom;
			env->offset.y -= (WIN_HEIGHT_HALF - y) * 0.0005 / env->image->zoom;
			redraw(env);
		}
		env->center.x = x;
		env->center.y = y;
	}
	return (0);
}

static void	move_fractal(int keycode, void *env)
{
	if (keycode == KEY_DOWN)
		((t_env*)env)->offset.y += 0.25 / ((t_env*)env)->image->zoom;
	if (keycode == KEY_UP)
		((t_env*)env)->offset.y -= 0.25 / ((t_env*)env)->image->zoom;
	if (keycode == KEY_RIGHT)
		((t_env*)env)->offset.x -= 0.25 / ((t_env*)env)->image->zoom;
	if (keycode == KEY_LEFT)
		((t_env*)env)->offset.x += 0.25 / ((t_env*)env)->image->zoom;
}

int			key_press(int keycode, void *env)
{
	if (keycode == KEY_ESC)
		end_program((t_env *)env);
	if (keycode == KEY_SPACEBAR && !((t_env*)env)->lock)
		((t_env*)env)->lock = 1;
	else if (keycode == KEY_SPACEBAR && ((t_env*)env)->lock)
		((t_env*)env)->lock = 0;
	if (keycode == KEY_COMMAND_LEFT || KEY_COMMAND_RIGHT)
		((t_env*)env)->command = 1;
	move_fractal(keycode, env);
	if (keycode == 1 && ((t_env*)env)->command)
		ft_bitmap(((t_env*)env)->image);
	if (keycode == KEY_PAD_ADD && ((t_env*)env)->max_iter < 500)
		((t_env*)env)->max_iter += 5;
	if (keycode == KEY_PAD_SUB && ((t_env*)env)->max_iter > 10)
		((t_env*)env)->max_iter -= 5;
	redraw(env);
	return (0);
}

int			key_release(int keycode, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (keycode == KEY_COMMAND_LEFT || KEY_COMMAND_RIGHT)
		env->command = 0;
	return (0);
}
