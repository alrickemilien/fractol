/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:15:38 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/27 15:53:56 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	put_pixel_to_image(t_image *image, int x, int y, t_color color)
{
	image->data = mlx_get_data_addr(image->img, &(image->bits_per_pixel), &(image->size_line), &(image->endian));

	image->data[y * image->size_line + x * image->bits_per_pixel  / 8] = color.red;
	image->data[y * image->size_line + x * image->bits_per_pixel  / 8 + 1] = color.green;
	image->data[y * image->size_line + x * image->bits_per_pixel  / 8 + 2] = color.blue;
}
