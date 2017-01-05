/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octant_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:13:09 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/26 14:16:56 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	octant_limit(void *mlx, void *win, t_seg line)
{
	int	dy;

	dy = (line.b.y - line.a.y);
	while (line.a.y != line.b.y)
	{
		mlx_pixel_put(mlx, win, line.a.x, line.a.y,
						ft_color(dy, (line.b.y - line.a.y), line));
		if (dy >= 0)
			line.a.y++;
		if (dy <= 0)
			line.a.y--;
	}
}
