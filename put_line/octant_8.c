/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octant_8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:13:50 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/26 13:22:40 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	octant_8(void *mlx, void *win, t_seg line)
{
	int	dx;
	int	dy;
	int	e;

	dx = abs(line.b.x - line.a.x);
	dy = abs(line.b.y - line.a.y);
	e = -dy;
	while (line.a.y < line.b.y)
	{
		mlx_pixel_put(mlx, win, line.a.x, line.a.y,
				ft_color(dy, (line.b.y - line.a.y), line));
		if ((e = e + 2 * dx) >= 0)
		{
			line.a.x--;
			e = e - 2 * dy;
		}
		line.a.y++;
	}
}
