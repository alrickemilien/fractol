#include "includes/fractol.h"
#include "includes/julia_set.h"
#include <stdio.h>


void	put_square(t_image image, t_point where, int side, int color)
{
	int		x;
	int		y;

	y = where.y;
	while(y < side)
	{
		x = where.x;
		while(x < side)
		{
			put_pixel_to_image(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_losange(t_image image, t_point where, int side, int color)
{
	int		x;
	int		y;
	int		n;
	double	diagonale;

	diagonale = side * 1.4142;
	n = 0;
	while(n < side)
	{
		y = where.y;
		while(y < (int)diagonale)
		{
			x = 0;
			while(x - n < (int)diagonale)
			{
				put_pixel_to_image(image, x, y, color);
				x++;
			}
			y++;
		}
		n++;
	}
}

typedef struct	s_leaf
{
	t_point		pos;
	t_point		sommet1;
	t_point		sommet1;
	double		side;
}				t_leaf;

int		recursive_draw(t_env *env, t_leaf square, int n)
{
	t_leaf	new_square;

	if(n == 50)
		return (0);
	if(!(n % 2))
	{
		new_square.pos = square.sommet1;
		new_square.side = (0.5 * 1.4142);
		put_losange(env->image, new_square.pos, , 0x0018C459);
		recursive_draw(env, n++);
	}
	else
	{
	}
		put_square();
	return (0);
}

void	*pythagore_three(void *env)
{
	int		n;
	double	old_side;
	double	new_side;

	return (NULL);
}
