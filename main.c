/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:17:48 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/27 16:15:15 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		main()
{
	t_env	*env;

	if(!(env = (t_env*)malloc(sizeof(t_env))))
		error("error malloc");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1900, 1080, "fractol");
	if(!(env->image = (t_image*)malloc(sizeof(t_image))))
		error("error malloc");
	env->image->img = mlx_new_image(env->mlx, 1900, 1080);
	fill_image(env->image, 1900, 1080, split_color(mlx_get_color_value(env->mlx, 0x00CC33FF)));
	julia_set(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image->img, 0, 0);
	mlx_key_hook(env->win, &event, env);
	mlx_loop(env->mlx);
	
	return (0);
}
