/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:22:29 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/05 18:17:19 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/fractol.h"
#include <unistd.h>

void	redraw(void *env)
{
	mlx_destroy_image(((t_env*)env)->mlx, ((t_env*)env)->image->img);
	//mlx_clear_window(((t_env*)env)->mlx, ((t_env*)env)->win);
	((t_env*)env)->image->img = mlx_new_image(((t_env*)env)->mlx, WIN_WIDTH, WIN_HEIGHT);
	((t_env*)env)->image->data = mlx_get_data_addr(((t_env*)env)->image->img, &(((t_env*)env)->image->bits_per_pixel), &(((t_env*)env)->image->size_line), &(((t_env*)env)->image->endian));
	((t_env*)env)->image->width = WIN_WIDTH;
	((t_env*)env)->image->height = WIN_HEIGHT;
	threads((t_env*)env);
	mlx_put_image_to_window(((t_env*)env)->mlx, ((t_env*)env)->win, ((t_env*)env)->image->img, 0, 0);
	if (((t_env*)env)->f == &julia_set)
		display_info_maths(env);
}

int		mouse_motion_hook(int x, int y, void *env)
{
	if(x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		((t_env*)env)->cursor.x = x;
		((t_env*)env)->cursor.x = y;
//	printf("x :%d\ny :%d\n\n", x, y);
		((t_env*)env)->constante.re = (WIN_WIDTH_HALF - x)  * 0.001 - 0.7;
		((t_env*)env)->constante.im = (WIN_HEIGHT_HALF - y) * 0.001 + 0.27015;
//
	}
	if(!((t_env*)env)->lock)
		redraw(env);
	return (0);
}

int		focus_in(int button, int x, int y, void *param)
{
	t_env	*env;

	button = 0;
	env = (t_env*)param;
	env->center.x = x;
	env->center.y = y;
	env->image->zoom += 1;
	env->constante.re += (env->cursor.x - WIN_WIDTH_HALF) * 0.0015;
	env->constante.im += (env->cursor.y - WIN_HEIGHT_HALF) * 0.0015;
	env->offset.x += 0.0015 / env->image->zoom * env->center.x;
	env->offset.y += 0.0015 / env->image->zoom * env->center.y; 
	redraw(env);
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
	if(keycode == 49 && !((t_env*)env)->lock)
		((t_env*)env)->lock = 1;
	else if (keycode == 49 && ((t_env*)env)->lock)
		((t_env*)env)->lock = 0;
	if(keycode == 124)
		((t_env*)env)->offset.x += 0.25 / ((t_env*)env)->image->zoom;
	if(keycode == 123)
		((t_env*)env)->offset.x -= 0.25 / ((t_env*)env)->image->zoom;
	if(keycode == 126)
		((t_env*)env)->offset.y += 0.25 / ((t_env*)env)->image->zoom;
	if(keycode == 125)
		((t_env*)env)->offset.y -= 0.25 / ((t_env*)env)->image->zoom;
	if(keycode == 69)
		((t_env*)env)->image->zoom++;
	if(keycode == 78)
		((t_env*)env)->image->zoom--;
	redraw(env);
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
