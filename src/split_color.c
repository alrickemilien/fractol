/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:50:16 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 10:24:58 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	split_color(unsigned long color)
{
	t_color	color_split;

	color_split.red = (color & 0xFF0000) >> 16;
	color_split.green = (color & 0xFF00) >> 8;
	color_split.blue = (color & 0xFF);
	return (color_split);
}