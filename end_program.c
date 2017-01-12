/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:12:34 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:25:07 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	end_program(t_env *env)
{
	mlx_destroy_image(env->mlx, env->image->img);
	mlx_destroy_window(env->mlx, env->win);
	free(env->image);
	free(env);
	exit(0);
}
