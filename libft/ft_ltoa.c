/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 08:54:59 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/02 09:00:28 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int		len;

	if (n == -9223372036854775808)
		return (20);
	len = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_ltoa(long n)
{
	char	*s;
	size_t	len;

	if (n == -9223372036854775808)
		return (ft_strdup("-9223372036854775808"));
	len = ft_nbrlen(n) + 1;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (!n)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	s[len - 1] = '\0';
	while (n)
	{
		len--;
		s[len - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
