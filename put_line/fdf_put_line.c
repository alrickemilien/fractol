/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:06:39 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/26 14:19:17 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/fdf_put_line.h"

/*
	**    \ 5 | 4 /
	**   6 \  |  /  3
	** ----------------
   	**   7 /  |   \ 2
	**   / 8  |  1 \
*/

int			fdf_put_line(t_data *data, t_seg line)
{
	t_point	d;

	if (line.a.x < 0 || line.a.y < 0 || line.b.x < 0 || line.b.y < 0)
		return (0);
	d.x = line.b.x - line.a.x;
	d.y = line.b.y - line.a.y;
	if (!d.x)
	{
		octant_limit(data->mlx->mlx, data->mlx->win, line);
		return (1);
	}
	if (line.a.x <= line.b.x)
	{
		put_line_right_side(data->mlx->mlx, data->mlx->win, line, d);
		return (1);
	}
	put_line_left_side(data->mlx->mlx, data->mlx->win, line, d);
	return (1);
}
