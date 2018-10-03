/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:15:38 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 10:24:49 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel_to_image(t_env *env, int x, int y, t_color color)
{
	int		line;
	int		colonne;

	line = y * SIZE_LINE;
	colonne = x * BPP / 8;
	IMAGE_BUFFER[line + colonne] = color.blue;
	IMAGE_BUFFER[line + colonne + 1] = color.green;
	IMAGE_BUFFER[line + colonne + 2] = color.red;
}
