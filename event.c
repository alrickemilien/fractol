/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:22:29 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/30 19:53:34 by aemilien         ###   ########.fr       */
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
	threads((t_env*)env);
	mlx_put_image_to_window(((t_env*)env)->mlx, ((t_env*)env)->win, ((t_env*)env)->image->img, 0, 0);
}

int		mouse_motion_hook(int x, int y, void *env)
{
	if(x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		((t_env*)env)->cursor.x = x;
		((t_env*)env)->cursor.x = y;
//	printf("x :%d\ny :%d\n\n", x, y);
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
	printf("x : %d\n", env->center.x);
	printf("y : %d\n\n", env->center.y);
	env->image->zoom += 1;
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
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (keycode == 259)
		env->command = 0;
	return (0);
}
