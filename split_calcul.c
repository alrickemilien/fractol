/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_calcul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:33:28 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/05 18:16:24 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	threads(t_env *env)
{
	pthread_t	*pthread;
	t_env		*tmp;
	int			i;

	pthread = (pthread_t*)malloc(sizeof(pthread_t) * 8);
	if(!(tmp = (t_env*)malloc(sizeof(t_env) * 8)))
		error("error malloc");
	i = 0;
	while(i < 8)
	{
		(tmp + i)->mlx = env->mlx;
		(tmp + i)->image = env->image;
		(tmp + i)->constante = env->constante;
		(tmp + i)->cursor = env->cursor;
		(tmp + i)->max_iter = env->max_iter;
		(tmp + i)->thread_index = i;
		(tmp + i)->offset = env->offset;
		if((pthread_create(&(pthread[i]), NULL, env->f, tmp + i)))
			error("error pthread_create");
		i++;
	}
	i = 0;
	while(i < 8)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}
	free(pthread);
	free(tmp);
}
