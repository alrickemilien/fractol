/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:15:38 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/28 18:54:57 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	put_pixel_to_image(t_image *image, int x, int y, t_color color)
{
	int		line;
	int		colonne;

	image->data = mlx_get_data_addr(image->img, &(image->bits_per_pixel), &(image->size_line), &(image->endian));
	line = y * image->size_line;
	colonne = x * image->bits_per_pixel  / 8;
	image->data[line + colonne] = color.red;
	image->data[line + colonne + 1] = color.green;
	image->data[line + colonne + 2] = color.blue;
}
