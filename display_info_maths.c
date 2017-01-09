/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info_maths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 12:58:10 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/09 14:56:38 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	display_info_maths(t_env *env)
{
	mlx_string_put(env->mlx, env->win, 5, 5, 0x00FF0000, "zoom: ");
	mlx_string_put(env->mlx, env->win,
		ft_strlen("zoom :  ") * 8 + 5, 5, 0x00FF0000,
		ft_dtoa(env->image->zoom, 2));
	mlx_string_put(env->mlx, env->win, 5, 20, 0x00FF0000, "Cx: ");
	mlx_string_put(env->mlx, env->win,
		ft_strlen("Cx : ") * 8 + 5, 20, 0x00FF0000,
		ft_dtoa(env->constante.re, 5));
	mlx_string_put(env->mlx, env->win, 5, 35, 0x00FF0000, "Cy: ");
	mlx_string_put(env->mlx, env->win,
		ft_strlen("Cy : ") * 8 + 5, 35, 0x00FF0000,
		ft_dtoa(env->constante.im, 5));
}
