/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:12:34 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:30:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	end_program(t_env *env)
{
	mlx_destroy_image(X_SERVER, IMAGE);
	mlx_destroy_window(X_SERVER, WINDOW);
	free(env);
	exit(0);
}
