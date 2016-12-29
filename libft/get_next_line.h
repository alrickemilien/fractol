#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

#define BUFF_SIZE 1

// BUF_SIZE peut changer

int		get_next_line(const int fd, char **line);

typedef  struct	s_file
{
	int				fd;
	char			*buf;
}				t_file;

#endif
