/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 17:00:48 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/05 16:01:10 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstpushback(t_list **alist, t_list *list)
{
	t_list  *tmp;

	if(!*alist)
		*alist = list;
	else
	{
		tmp = *alist;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = list;
	}
}
