/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_calcul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:33:28 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 10:25:38 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		env_cpy(t_env *env, t_env *tmp, int i)
{
	tmp->mlx = env->mlx;
	tmp->image = env->image;
	tmp->constante = env->constante;
	tmp->cursor = env->cursor;
	tmp->max_iter = env->max_iter;
	tmp->thread_index = i;
	tmp->offset = env->offset;
}

void			threads(t_env *env)
{
	pthread_t	*pthread;
	t_env		*tmp;
	int			i;

	pthread = (pthread_t*)malloc(sizeof(pthread_t) * 8);
	if (!(tmp = (t_env*)malloc(sizeof(t_env) * 8)))
		error("error malloc");
	i = 0;
	while (i < 8)
	{
		env_cpy(env, tmp + i, i);
		if ((pthread_create(&(pthread[i]), NULL, env->f, tmp + i)))
			error("error pthread_create");
		i++;
	}
	i = 0;
	while (i < 8)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}
	free(pthread);
	free(tmp);
}
