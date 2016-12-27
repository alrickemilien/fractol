/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:22:29 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/27 15:22:35 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int				event(int keycode, void *env)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(((t_env*)env)->mlx,
				((t_env*)env)->win);
		exit(0);
	}
	return (0);
}
