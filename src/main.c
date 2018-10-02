/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:17:48 by aemilien          #+#    #+#             */
/*   Updated: 2017/01/12 11:26:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void init_x_server(t_env *environ) {
// 	WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
// 	WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;
//
// 	X_SERVER = mlx_init();
// 	WINDOW = mlx_new_window(X_SERVER, WINDOW_WIDTH, WINDOW_HEIGHT, "FRACTOL");
// 	IMAGE = mlx_new_image(X_SERVER, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	IMAGE_BUFFER = mlx_get_data_addr(IMAGE, & BPP, & SIZE_LINE, & ENDIAN);
//
// 	mlx_put_image_to_window(X_SERVER, WINDOW, IMAGE, 0, 0);
//
// 	mlx_hook(WINDOW, 2, 1L << 0 | 1 << 1, & key_press, environ);
// }

void	init_env_values(t_env *env)
{
	// init_x_server(env);

	env->lock = 0;
	env->cursor.x = 0;
	env->cursor.y = 0;
	env->max_iter = 250;
	if (env->f == &third_set)
		env->max_iter = 200;
	env->offset.x = 0;
	env->offset.y = 0;
	env->constante.re = -0.7;
	env->constante.im = 0.27015;

	if (!(env->image = (t_image*)malloc(sizeof(t_image))))
		error("error malloc");

	env->image->zoom = 1;
	env->image->width = WIN_WIDTH;
	env->image->height = WIN_HEIGHT;
	env->center.x = WIN_WIDTH_HALF;
	env->center.y = WIN_HEIGHT_HALF;
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	env->image->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->image->data = mlx_get_data_addr(env->image->img,
		&(env->image->bpp), &(env->image->size_line), &(env->image->endian));
}


void	end_program(t_software_environ *environ)
{
	mlx_destroy_image(X_SERVER, IMAGE);
	mlx_destroy_window(X_SERVER, WINDOW);

	exit(0);
}

int key_press(int keycode, void *params)
{
	if (keycode == KEY_ESC)
	end_program(params);

	return (0);
}

int		parse(t_env *env, int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (!(ft_strcmp(argv[1], "--julia")))
		env->f = &julia_set;
	else if (!(ft_strcmp(argv[1], "--mandelbrot")))
		env->f = &mandelbrot_set;
	else if (!(ft_strcmp(argv[1], "--burningship")))
		env->f = &third_set;
	else
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (!parse(&env, argc, argv))
	{
		free(env);
		error(USAGE);
	}

	env.mlx = mlx_init();

	init_env_values(&env);
	threads(&env);

	mlx_put_image_to_window(env.mlx, env.win, env.image->img, 0, 0);

	if (env.f == &julia_set)
		display_info_maths(env);

	mlx_hook(env.win, 6, 1L << 6, &mouse_motion_hook, env);
	mlx_hook(env.win, 3, 1L << 1, &key_release, env);
	mlx_hook(env.win, 2, 1L << 0 | 1 << 1, &key_press, env);
	mlx_hook(env.win, 4, 0L, &focus_in, env);
	mlx_loop(env.mlx);

	return (0);
}
