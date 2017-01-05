/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 12:59:18 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/26 14:20:01 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/fdf_put_line.h"

void	put_line_right_side(void *mlx, void *win, t_seg line, t_point d)
{
	if (line.a.y <= line.b.y && d.y / d.x >= 1)
		octant_1(mlx, win, line);
	else if (line.a.y <= line.b.y && d.y / d.x < 1 && d.y / d.x >= 0)
		octant_2(mlx, win, line);
	else if (line.a.y >= line.b.y && d.y / d.x > -1 && d.y / d.x <= 0)
		octant_3(mlx, win, line);
	else if (line.a.y >= line.b.y && d.y / d.x <= -1)
		octant_4(mlx, win, line);
}
