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

void	put_pixel_to_image(t_image *image, int x, int y, t_color color)
{
	int		line;
	int		colonne;

	line = y * image->size_line;
	colonne = x * image->bpp / 8;
	image->data[line + colonne] = color.blue;
	image->data[line + colonne + 1] = color.green;
	image->data[line + colonne + 2] = color.red;
}
