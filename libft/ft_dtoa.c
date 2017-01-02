/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 08:54:47 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/02 08:59:32 by aemilien         ###   ########.fr       */
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

static void	handle_no_number_after_decimal(int prec, char **s)
{
	char	*s_tmp;
	int		i;

	i = 0;
	if (!(s_tmp = (char *)malloc(sizeof(char) * (prec + 1))))
		return ;
	while (prec--)
		s_tmp[i++] = '0';
	s_tmp[i] = '\0';
	ft_strcat(*s, s_tmp);
	ft_strdel(&s_tmp);
}

static void	precision_smaller_than_10(double n, int prec, char **s)
{
	char	*s_tmp;
	int		prec_tmp;
	int		i;

	i = 0;
	n = n * ft_pow(10, prec);
	prec_tmp = prec - ft_longlen(n);
	if (!(s_tmp = (char *)malloc(sizeof(char) * (prec_tmp + 1))))
		return ;
	while (prec_tmp--)
		s_tmp[i++] = '0';
	s_tmp[i] = '\0';
	if ((long)((n - (long)n) * 10) > 4)
		n += 1;
	ft_strcat(*s, s_tmp);
	ft_strdel(&s_tmp);
	ft_strcat(*s, s_tmp = ft_ltoa(n));
	ft_strdel(&s_tmp);
}

static int	handle_precision(double n, int prec, char **s)
{
	char	*s_tmp;

	if ((n = n - (long)n))
	{
		if (prec < 10)
			precision_smaller_than_10(n, prec, s);
		else
		{
			while (prec--)
			{
				n *= 10;
				if (!prec && (long)((n - (long)n) * 10) > 4
							&& (long)((n - (long)n) * 10) != 9)
					n += 1;
				ft_strcat(*s, s_tmp = ft_ltoa(n));
				ft_strdel(&s_tmp);
				n -= (long)n;
			}
		}
	}
	else
		handle_no_number_after_decimal(prec, s);
	return (0);
}

char		*ft_dtoa(double n, int chiffres_sign)
{
	char	*str;
	char	*tmp;
	size_t	len;

	if (chiffres_sign < 0)
		chiffres_sign = 0;
	len = ft_nbrlen((long)n) + chiffres_sign + 1;
	if (!(str = ft_strnew(len)))
		return (NULL);
	s[0] = '\0';
	if (n < 0 ? 1 : 0)
	{
		n = -n;
		s[0] = '-';
		s[1] = '\0';
	}
	ft_strcat(str, tmp = ft_ltoa(n));
	ft_strdel(&tmp);
	if (chiffres_sign)
	{
		ft_strcat(str, ".");
		if (handle_precision(n, chiffres_sign, &str))
			return (NULL);
	}
	return (str);
}
