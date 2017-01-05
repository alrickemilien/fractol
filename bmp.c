#include "includes/fractol.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

void	set_bitmapfileheader(int fd, t_image *image)
{
	unsigned char	*header;
	unsigned int	file_size;
	unsigned char	*tmp;
	int		i;
//	unsigned char c;
	int ret;
	int		len;

	header = (unsigned char*)malloc(sizeof(unsigned char) * 14);
	ft_bzero(header, 14);
	header[0] = 0x42;
	header[1] = 0x4D;

	len = image->height * image->height * 3;
	i = 0;
	while ((len + i) % 4)
		i++;
	len += i;
	file_size = len + 14 + 40;
	tmp = (unsigned char*)&file_size;
	//printf("file size %x\n\n", file_size);
	header[2] = tmp[0];
	header[3] = tmp[1];
	header[4] = tmp[2];
	header[5] = tmp[3];
/*
 * offset : Adresse de la zone de définition de l’image
 */
	header[10] = 0x36;
	//header[11] = 0;
	//header[12] = 0;
	//header[13] = 0;
	/*i = 0;
	while (i < 14)
	{
		c= header[i];
		printf("%X\n", c);
		i++;
	}*/
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
	if (ret == -1)
		perror("write error");
	//ft_putchar('\n');
}

void	set_bitmapinfoheader(int fd, t_image *image)
{
	unsigned char	*header;
	unsigned char	*tmp;
	unsigned int		n;
	int		i;

	header = (unsigned char*)malloc(sizeof(unsigned char) * 40);
	ft_bzero(header, 40);
	
	header[0] = 0x28;

	n = image->width;
	tmp = (unsigned char*)&n;
	header[4] = tmp[0];
	header[5] = tmp[1];
	header[6] = tmp[2];
	header[7] = tmp[3];
	
	n = image->height;
	tmp = (unsigned char*)&n;
	header[8] = tmp[0];
	header[9] = tmp[1];
	header[10] = tmp[2];
	header[11] = tmp[3];

	header[12] = 0x01;
	//header[13] = 0;
	
	n = image->bits_per_pixel;
	tmp = (unsigned char*)&n;
	header[14] = 0x18; // !!!!!!!!!!!!!
	header[15] = 0;

/*compression
	header[16]
	header[17]
	header[18]
	header[19]
*/	
	n = image->height * image->width * 3;
	printf("bpp : %d\n", n);
	tmp = (unsigned char*)&n;
	header[20] = tmp[0];
	header[21] = tmp[1];
	header[22] = tmp[2];
	header[23] = tmp[3];

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
	
	i = 0;
	while (i < 40)
	{
		printf("%X\n", header[i]);
		i++;
	}
	write(fd, header, 40);
	ft_putchar ('\n');
}

void	set_bitmapdata(int fd, t_image *image)
{
	char	*bitmap;
	int		x;
	int		y;
	int		line;
	int		colonne;
	int		i;
	int		len;

	len = image->height * image->height * 3;
	i = 0;
	while ((len + i) % 4)
		i++;
	len += i;
	bitmap = (char*)malloc(sizeof(char) * len);
	ft_bzero(bitmap, sizeof(char) * len);
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
	write(fd, bitmap, sizeof(char) * len);
}

void	ft_bitmap(t_image *image)
{
	int		fd;
	unsigned char	c;
	int		i;

	fd = open("screenshot.bmp", O_RDWR | O_EXCL | O_CREAT | O_NONBLOCK, S_IRUSR | S_IWUSR);
	set_bitmapfileheader(fd, image);
	set_bitmapinfoheader(fd, image);
	set_bitmapdata(fd, image);
	close (fd);
	fd = open("screenshot.bmp", O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR);
	i = 0;
	while (read(fd, &c, 1) && i < 54)
	{
		if (i >= 14)
			printf("%X\n", c);
		i++;
	}
	ft_putendl("OK");
}
