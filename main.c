/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:17:48 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/28 15:50:54 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		main()
{
	t_env	*env;

	if(!(env = (t_env*)malloc(sizeof(t_env))))
		error("error malloc");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	if(!(env->image = (t_image*)malloc(sizeof(t_image))))
		error("error malloc");
	env->image->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->image->zoom = 1;
	env->cursor.x = 0;
	env->cursor.y = 0;
	julia_set(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image->img, 0, 0);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_hook(env->win, 6, 0, &mouse_motion_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
