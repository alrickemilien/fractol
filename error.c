#include "includes/fractol.h"

int		error(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	exit(0);
	return (0);
}
