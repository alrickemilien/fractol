void	ft_write_n_bytes(unsigned char *dest, unsigned char *src, int i)
{
	int		j;

	j = 0;
	while (j < 4)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
}
