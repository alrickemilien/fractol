/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octant_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:11:28 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/26 13:21:57 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	octant_3(void *mlx, void *win, t_seg line)
{
	int	dx;
	int	dy;
	int	e;

	dx = abs(line.b.x - line.a.x);
	dy = abs(line.b.y - line.a.y);
	e = -dx;
	while (line.a.x < line.b.x)
	{
		mlx_pixel_put(mlx, win, line.a.x, line.a.y,
				ft_color(dx, (line.b.x - line.a.x), line));
		if ((e = e + 2 * dy) >= 0)
		{
			line.a.y--;
			e = e - 2 * dx;
		}
		line.a.x++;
	}
}
