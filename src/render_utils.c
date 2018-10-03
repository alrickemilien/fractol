#include "fractol.h"

t_color	split_color(unsigned long color)
{
	t_color	color_split;

	color_split.red = (color & 0xFF0000) >> 16;
	color_split.green = (color & 0xFF00) >> 8;
	color_split.blue = (color & 0xFF);
	return (color_split);
}

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

void	ft_write_n_bytes(unsigned char *dest, unsigned char *src, int i)
{
	int		j;

	j = 0;
	while (j < 4)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
}
