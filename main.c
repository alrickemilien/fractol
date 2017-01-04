/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:17:48 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/02 15:40:57 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	threads(t_env *env)
{
	pthread_t	*pthread;
	t_env		*tmp;
	int			i;

	pthread = (pthread_t*)malloc(sizeof(pthread_t) * 4);
	if(!(tmp = (t_env*)malloc(sizeof(t_env) * 4)))
		error("error malloc");
	i = 0;
	while(i < 4)
	{
		(tmp + i)->mlx = env->mlx;
		(tmp + i)->image = env->image;
		(tmp + i)->constante = env->constante;
		(tmp + i)->cursor = env->cursor;
		(tmp + i)->max_iter = env->max_iter;
		(tmp + i)->thread_index = i;
		(tmp + i)->offset = env->offset;
		(tmp + i)->thread_origin.y = (i % 2) * WIN_HEIGHT_HALF;
		if (i < 2)
			(tmp + i)->thread_origin.x = 0;
		else
			(tmp + i)->thread_origin.x = WIN_WIDTH_HALF;
		if((pthread_create(&(pthread[i]), NULL, &julia_set, tmp + i)))
			error("error pthread_create");
		if (tmp->image->numcolors > env->image->numcolors)
			env->image->numcolors = tmp->image->numcolors;
		i++;
	}
	i = 0;
	while(i < 4)
	{
		pthread_join(pthread[i], NULL);
		i++;
	}
	free(pthread);
	free(tmp);
}

int		main()
{
	t_env	*env;

	if(!(env = (t_env*)malloc(sizeof(t_env))))
		error("error malloc");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	if(!(env->image = (t_image*)malloc(sizeof(t_image))))
		error("error malloc");
	env->image->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->image->data = mlx_get_data_addr(env->image->img, &(env->image->bits_per_pixel), &(env->image->size_line), &(env->image->endian));
	env->lock = 0;
	env->image->zoom = 1;
	env->cursor.x = 0;
	env->cursor.y = 0;
	env->max_iter = 250;
	env->offset.x = 0;
	env->offset.y = 0;
	env->constante.re = -0.7;
	env->constante.im = 0.27015;
	env->image->cpp = 2;
	env->image->numcolors = 0;
	env->image->width = WIN_WIDTH;
	env->image->height = WIN_HEIGHT;
	env->center.x = WIN_WIDTH_HALF;
	env->center.y = WIN_HEIGHT_HALF;
	threads(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image->img, 0, 0);
	display_info_maths(env);
	mlx_hook(env->win, 6, 1L<<6, &mouse_motion_hook, env);
	mlx_hook(env->win, 3, 1L<<1 , &key_release, env);
	mlx_hook(env->win, 2, 1L<<0 | 1<<1, &key_press, env);
	mlx_hook(env->win, 4, 0L, &focus_in, env);
	mlx_loop(env->mlx);
	return (0);
}
