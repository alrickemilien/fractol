/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 10:52:32 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:11:07 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	redraw(t_env *env)
{
	mlx_destroy_image(env->mlx, env->image->img);
	env->image->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	threads(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image->img, 0, 0);
	if (env->f == &julia_set)
		display_info_maths(env);
}
