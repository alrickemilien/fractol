/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:36:26 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/26 20:01:27 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizeofnbr(int n, int *m)
{
	int		size;

	size = 1;
	if (n < 0)
		size++;
	*m = 1;
	while (n / *m >= 10 || n / *m <= -10)
	{
		*m *= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		m;
	int		i;

	if (n < -2147483648 || n > 2147483647)
		return (NULL);
	str = ft_strnew(ft_sizeofnbr(n, &m));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		i = 1;
	}
	while (m > 0)
	{
		if (n >= 0)
			str[i] = ((n / m) % 10) + 48;
		if (n < 0)
			str[i] = -((n / m) % 10) + 48;
		m = m / 10;
		i++;
	}
	return (str);
}
