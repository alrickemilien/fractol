/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:46:15 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:30:50 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			set_bitmapfileheader(int fd, t_env *env)
{
	unsigned char	*header;
	int				len;

	(void)env;

	header = (unsigned char*)malloc(14);
	ft_bzero(header, 14);
	ft_memcpy(header, "\x42\x4D", 2);

	len = DEFAULT_WINDOW_WIDTH * DEFAULT_WINDOW_HEIGHT * 3;
	while (len % 4)
		len++;
	len += 54;

	ft_memcpy(header + 2, &len, 4);

	header[10] = 0x36;

	if ((len = write(fd, header, 14)) == -1)
		ft_putendl_fd("Error creating screenshot", 2);
}

static int				set_bitmapinfoheader(int fd, t_env *env)
{
	unsigned char	*header;
	unsigned int	n;

	(void)env;

	header = (unsigned char*)malloc(40);
	ft_bzero(header, 40);
	header[0] = 0x28;

	n = DEFAULT_WINDOW_WIDTH;
	ft_write_n_bytes(header, (unsigned char*)&n, 4);

	n = DEFAULT_WINDOW_HEIGHT;
	ft_write_n_bytes(header, (unsigned char*)&n, 8);

	ft_memcpy(header + 12, "\x01\x18", 2);

	n = DEFAULT_WINDOW_HEIGHT * DEFAULT_WINDOW_WIDTH * 3;
	ft_write_n_bytes(header, (unsigned char*)&n, 20);

	ft_memcpy(header + 24, "\xC3\x0E\xC\x0E", 4);

	if (write(fd, header, 40) == 0){
		free(header);
		return (0);
	}
	free(header);
	return (1);
}

static void				data_to_bitmap(char *bitmap, t_env *env, int i)
{
	int				x;
	int				y;
	int				line;
	int				colonne;

	y = DEFAULT_WINDOW_HEIGHT - 1;
	while (y >= 0)
	{
		line = y * env->size_line;
		x = 0;
		while (x < DEFAULT_WINDOW_WIDTH)
		{
			colonne = x * BPP / 8;
			bitmap[i] = IMAGE_BUFFER[line + colonne];
			bitmap[i + 1] = IMAGE_BUFFER[line + colonne + 1];
			bitmap[i + 2] = IMAGE_BUFFER[line + colonne + 2];
			i += 3;
			x++;
		}
		y--;
	}
}

static int				set_bitmapdata(int fd, t_env *env)
{
	char			*bitmap;
	int				len;
	int				ret;

	len = DEFAULT_WINDOW_WIDTH * DEFAULT_WINDOW_WIDTH * 3;
	while (len % 4)
		len++;
	if (!(bitmap = (char*)malloc(sizeof(char) * len)))
		error("error alloc in func set_bitmapdata");
	ft_bzero(bitmap, sizeof(char) * len);
	data_to_bitmap(bitmap, IMAGE, 0);
	ret = write(fd, bitmap, len);
	free(bitmap);
	if(!ret)
		return (0);
	return (1);
}

void				ft_bitmap(t_env *env)
{
	int				fd;

	fd = open("assets/screenshot.bmp", O_RDWR | O_CREAT
			| O_NONBLOCK, S_IRUSR | S_IWUSR);

	if (fd == -1) {
		ft_putendl_fd("Scrrenshot has been taken because an error occured", 2);

		return ;
	}

	set_bitmapfileheader(fd, env);
	set_bitmapinfoheader(fd, env);
	set_bitmapdata(fd, env);

	close(fd);

	ft_putendl("screenshot.bmp has been created");
}
