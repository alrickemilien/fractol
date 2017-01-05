/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 09:00:51 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/05 18:23:35 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include "macro_key_mlx.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# define USAGE "Usage : ./fractol [--julia] [--mandelbrot] [--burninship]"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200
# define WIN_WIDTH_HALF 600
# define WIN_HEIGHT_HALF 600

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
	int			width;
	int			height;
	double		zoom;
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
	void		*(*f)(void *);
	t_image		*image;
	t_z			constante;
	t_point		cursor;
	t_dpoint	offset;
	t_point		thread_origin;
	int			max_iter;
	int			thread_index;
	t_point		dimension_image;
	int			command;
	int			shift;
	int			lock;
	t_point		center;
}				t_env;

int		error(char *str);
int		key_press(int keycode, void *param);
int		mouse_motion_hook(int x, int y, void *param);
void	put_pixel_to_image(t_image *image, int x, int y, t_color color);
t_color	split_color(unsigned long color);
void	fill_image(t_image *image, int width, int height, t_color color);
void	*julia_set(void *env);
void	threads(t_env *env);
void	*mandelbrot_set(void *env);
void	*burningship_set(void *env);
int		key_release(int keycode, void *param);
int		focus_in(int button, int x, int y, void *param);
void	display_info_maths(t_env *env);
void	ft_bitmap(t_image *image);
void	ft_write_n_bytes(unsigned char *dest, unsigned char *src, int n);
#endif
