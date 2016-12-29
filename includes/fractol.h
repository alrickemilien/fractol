/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 09:00:51 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/29 16:18:46 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include "macro_key_mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

typedef struct	s_z
{
	double	re;
	double	im;
}				t_z;

typedef struct	s_image
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			zoom;
	void		*img;
	char		*data;
}				t_image;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_dpoint
{
	double		x;
	double		y;
}				t_dpoint;

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}				t_color;

typedef	struct	s_env
{
	void		*mlx;
	void		*win;
	t_image		*image;
	t_z			constante;
	t_point		cursor;
	t_dpoint		offset;
	int			max_iter;
	int			thread_index;
}				t_env;

int		error(char *str);
int		key_hook(int keycode, void *param);
int		mouse_motion_hook(int x, int y, void *param);
void	put_pixel_to_image(t_image *image, int x, int y, t_color color);
t_color	split_color(unsigned long color);
void	fill_image(t_image *image, int width, int height, t_color color);
void	*julia_set(void *env);
void	threads(t_env *env);
void	*mandelbrot_set(void *env);
void	*third_set(void *env);

#endif
