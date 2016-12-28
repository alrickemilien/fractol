/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:22:29 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/28 15:24:35 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/fractol.h"

void	redraw(void *env)
{
	mlx_destroy_image(((t_env*)env)->mlx, ((t_env*)env)->image->img);
	//mlx_clear_window(((t_env*)env)->mlx, ((t_env*)env)->win);
	mlx_new_image(((t_env*)env)->mlx, WIN_WIDTH, WIN_HEIGHT);
	((t_env*)env)->image->img = mlx_new_image(((t_env*)env)->mlx, WIN_WIDTH, WIN_HEIGHT);
	julia_set((t_env*)env);
	mlx_put_image_to_window(((t_env*)env)->mlx, ((t_env*)env)->win, ((t_env*)env)->image->img, 0, 0);
}

int		mouse_motion_hook(int x, int y, void *env)
{
	((t_env*)env)->cursor.x = x;
	((t_env*)env)->cursor.x = y;
	printf("x : %d\ny: %d\n\n", x, y);
	redraw(env);
	return (0);
}

int		key_hook(int keycode, void *env)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(((t_env*)env)->mlx,
				((t_env*)env)->win);
		exit(0);
	}
	if(keycode == 69)
	{
		((t_env*)env)->image->zoom++;
		redraw(env);
	}
	if(keycode == 78)
	{
		((t_env*)env)->image->zoom--;
		redraw(env);
	}
//	mlx_do_key_autorepeaton(((t_env*)env)->mlx);
	return (0);
}
