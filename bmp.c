#include "includes/fractol.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

void	set_bitmapfileheader(int fd, t_image *image)
{
	unsigned char	*header;
	unsigned int		file_size;
	unsigned char	*tmp;
	int		i;
	unsigned char c;
	int ret;

	header = (unsigned char*)malloc(sizeof(unsigned char) * 14);
	ft_bzero(header, 14);
	header[0] = 0x42;
	header[1] = 0x4D;
	file_size = image->size_line * image->height;
	tmp = (unsigned char*)&file_size;
	printf("tmp[1] %x\n\n", tmp[2]);
	header[2] = tmp[3];
	header[3] = tmp[2];
	header[4] = tmp[1];
	header[5] = tmp[0];
/*
 * offset : Adresse de la zone de définition de l’image
 */
	header[10] = 0x36;
	//header[11] = 0;
	//header[12] = 0;
	//header[13] = 0;
	i = 0;
	while (i < 6)
	{
		c= header[i];
		printf("%X\n", c);
		i++;
	}
	ret = write(fd, header, 14);
	/*printf("ret : %d\n", ret);
	close (fd);
	fd = open("screenshot.bmp", O_RDWR);
	i = 0;
	while (read(fd, &c, 1) && i < 14)
	{
		printf("%X\n", c);
		i++;
	}*/
	perror("write error");
	ft_putchar('\n');
}

void	set_bitmapinfoheader(int fd, t_image *image)
{
	char	*header;
	char	*tmp;
	int		n;
	
	header = (char*)malloc(sizeof(char) * 40);
	ft_bzero(header, 40);
	
	header[0] = 0x28;

	n = image->width;
	tmp = (char*)&n;
	header[4] = tmp[3];
	header[5] = tmp[2];
	header[6] = tmp[1];
	header[7] = tmp[0];
	
	n = image->height;
	tmp = (char*)&n;
	header[8] = tmp[3];
	header[9] = tmp[2];
	header[10] = tmp[1];
	header[11] = tmp[0];

	header[12] = 0x01;
	//header[13] = 0;
	
	n = image->bits_per_pixel;
	tmp = (char*)&n;
	header[14] = tmp[1];
	header[15] = tmp[0];

/*compression
	header[16]
	header[17]
	header[18]
	header[19]
*/	
	n = image->size_line * image->height;
	tmp = (char*)&n;
	header[20] = tmp[3];
	header[21] = tmp[2];
	header[22] = tmp[1];
	header[23] = tmp[0];

	header[24] = 0xC3;
	header[25] = 0x0E;
	header[26] = 0;
	header[27] = 0;

	header[28] = 0xC3;
	header[29] = 0x0E;
	header[30] = 0;
	header[31] = 0;

	//header[32]
	//header[33]
	//header[34]
	//header[35]
	//header[36]
	//header[37]
	//header[38]
	//header[39]
	write(fd, header, 40);
}

void	set_bitmapdata(int fd, t_image *image)
{
	char	*bitmap;
	int		x;
	int		y;
	int		line;
	int		colonne;
	int		i;

	bitmap = (char*)malloc(sizeof(char) * image->size_line * image->height);
	ft_bzero(bitmap, sizeof(char) * image->size_line * image->height);
	y = image->height - 1;
	i = 0;
	while (y >= 0)
	{
		line = y * image->size_line;
		x = 0;
		while (x < image->width)
		{
			colonne = x * image->bits_per_pixel / 8;
			bitmap[i] = image->data[line + colonne];
			bitmap[i + 1] = image->data[line + colonne + 1];
			bitmap[i + 2] = image->data[line + colonne + 2];
			i += 3;
			x++;
		}
		y--;
	}
	write(fd, bitmap, sizeof(char) * image->size_line * image->height);
}

void	ft_bitmap(t_image *image)
{
	int		fd;
	unsigned char	c;
	int		i;

	fd = open("screenshot.bmp", O_RDWR | O_EXCL | O_CREAT | O_NONBLOCK , S_ISCHR);
	set_bitmapfileheader(fd, image);
	set_bitmapinfoheader(fd, image);
	set_bitmapdata(fd, image);
	close (fd);
	fd = open("screenshot.bmp", O_RDWR | O_NONBLOCK, S_ISCHR);
	i = 0;
	while (read(fd, &c, 1) && i < 14)
	{
		printf("%X\n", c);
		i++;
	}
	ft_putendl("OK");
}
