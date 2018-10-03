#include "fractol.h"

void	fill_image(t_env *env, int width, int height, t_color color)
{
	int		x;
	int		y;

	y = 0;
	while(y < height)
	{
		x = 0;
		while(x < width)
		{
			put_pixel_to_image(env, x, y, color);
			x++;
		}
		y++;
	}
}
