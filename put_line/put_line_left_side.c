/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:00:28 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/26 14:19:55 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/fdf_put_line.h"

void	put_line_left_side(void *mlx, void *win, t_seg line, t_point d)
{
	if (line.a.y >= line.b.y && d.y / d.x > 1)
		octant_5(mlx, win, line);
	else if (line.a.y >= line.b.y && d.y / d.x < 1 && d.y / d.x >= 0)
		octant_6(mlx, win, line);
	else if (line.a.y <= line.b.y && d.y / d.x > -1 && d.y / d.x <= 0)
		octant_7(mlx, win, line);
	else if (line.a.y <= line.b.y && d.y / d.x <= -1)
		octant_8(mlx, win, line);
}
