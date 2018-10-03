/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_calcul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:33:28 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:26:51 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		env_cpy(t_env *env, t_env *tmp, int i)
{
	tmp->x_server = X_SERVER;
	tmp->image = IMAGE;
	tmp->constante = env->constante;
	tmp->cursor = env->cursor;
	tmp->max_iteration = env->max_iteration;
	tmp->thread_index = i;
	tmp->offset = env->offset;
}

void			threads(t_env *env)
{
	pthread_t	*pthread;
	t_env		*tmp;
	int			i;

	pthread = (pthread_t*)malloc(sizeof(pthread_t) * NUMBER_OF_THREADS);

	if (!(tmp = (t_env*)malloc(sizeof(t_env) * NUMBER_OF_THREADS)))
		error("error malloc in threads");

	i = 0;
	while (i < NUMBER_OF_THREADS)
	{
		env_cpy(env, tmp + i, i);
		if ((pthread_create(&(pthread[i]), NULL, env->f, tmp + i)))
			error("error pthread_create");
		i++;
	}

	i = 0;
	while (i < NUMBER_OF_THREADS)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}

	free(pthread);
	free(tmp);
}
