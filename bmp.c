#include "includes/fractol.h"

void	set_bitmapfileheader(int fd, t_image *image)
{
	char	*header;
	int		file_size;
	char	*tmp;

	header = (char*)malloc(sizeof(char) * 14);
	ft_bzero(header, 14);
	header[0] = 0x42;
	header[1] = 0x4D;
	file_size = image->size_line * image->height;
	tmp = (char*)&tmp;
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
	write(fd, header, 14);
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
	header[4] = tmp[1];
	header[5] = tmp[2];
	header[6] = tmp[3];
	header[7] = tmp[4];
	
	n = image->height;
	tmp = (char*)&n;
	header[8] = tmp[1];
	header[9] = tmp[2];
	header[10] = tmp[3];
	header[11] = tmp[4];

	header[12] = 0x01;
	//header[13] = 0;
	
	n = image->bits_per_pixel;
	tmp = (char*)&n;
	header[14] = tmp[0];
	header[15] = tmp[1];

/*compression
	header[16]
	header[17]
	header[18]
	header[19]
*/	
	n = image->size_line * image->height;
	tmp = (char*)&n;
	header[20] = tmp[0];
	header[21] = tmp[1];
	header[22] = tmp[2];
	header[23] = tmp[3];

	header[24] = 0;
	header[25] = 0;
	header[26] = 0x30;
	header[27] = 0xB1;

	header[28] = 0;
	header[29] = 0;
	header[30] = 0x30;
	header[31] = 0xB1;

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
	y = image->height;
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
		}
		y--;
	}
	write(fd, bitmap, sizeof(char) * image->size_line * image->height);
}

void	ft_bitmap(t_image *image)
{
	int		fd;

	fd = open("screenshot.bmp", O_RDWR | O_EXCL | O_CREAT);
	set_bitmapfileheader(fd, image);
	set_bitmapinfoheader(fd, image);
	set_bitmapdata(fd, image);
}
