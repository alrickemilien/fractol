/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:05:23 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/02 15:05:54 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"
#include <stdio.h>

/*
 	/ XPM /
	static char * <pixmap_name>[] = {
	<Values>
	<Colors>
	<Pixels>
	<Extensions>
	};
 */

void	write_values_section(int fd, t_image *image)
{
	ft_putchar_fd('"', fd);
	ft_putstr_fd(ft_itoa(image->width), fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(ft_itoa(image->height), fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(ft_itoa(image->numcolors), fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(ft_itoa(image->cpp), fd);
	ft_putchar_fd('"', fd);
	ft_putchar_fd(',', fd);
}

void	write_colors_section(int fd, t_image *image)
{
	char	*colors_section;
	int		len;
	int		i;
	int		j;
	char	*data;
	int		line;
	int		colonne;

	data = image->data;
	len = image->cpp + 1;
	if(!(colors_section = (char*)malloc(sizeof(char) * len)))
		return ;
	i = 0;
	while (i < WIN_HEIGHT)
	{
		line = i * image->size_line;
		j = 0;
		while (j < WIN_WIDTH)
		{
			colonne = j * image->bits_per_pixel / 8;
			ft_putchar_fd('"', fd);
			ft_putchar_fd(i, fd);
			ft_putstr("     c #");
			printf("%X\",\n", data[line + colonne] + data[line + colonne + 1] + data[line + colonne + 2]);
			j++;
		}
		i++;
	}
}

/*void	write_values_section(int fd, t_image *image)
{
	int		i;

	i = 0;
}*/

void	write_xpm_file(char const *file_name, t_image *image)
{
	int		fd;
	char	*pixel_section;
	int		len;

	fd = open(file_name, O_RDWR | O_EXCL | O_CREAT);
	ft_putendl_fd("/*XPM*/\nstatic char * data[] = {", fd);
	write_values_section(fd, image);
	len = image->size_line * image->height + 3 * image->height + 2;
	if(!(pixel_section = (char*)malloc(sizeof(char) * len)))
		return ;
	pixel_section[len - 1] = '\0';
	//write_values_section(fd, image);
	pixel_section[len - 2] = ';';
	pixel_section[len - 3] = '}';
	close(fd);
}
