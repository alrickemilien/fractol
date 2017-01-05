/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:15:38 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/05 15:55:08 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	put_pixel_to_image(t_image *image, int x, int y, t_color color)
{
	int		line;
	int		colonne;
	
	line = y * image->size_line;
	colonne = x * image->bits_per_pixel  / 8;

	image->data[line + colonne] = color.blue;
	image->data[line + colonne + 1] = color.green;
	image->data[line + colonne + 2] = color.red;
}
