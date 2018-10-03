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

void initialize_key_events(t_env *env) {
	mlx_hook(WINDOW, 2, 1L << 0 | 1 << 1, &key_press, env);
	mlx_hook(WINDOW, 6, 1L << 6, &mouse_motion_hook, env);
	mlx_hook(WINDOW, 3, 1L << 1, &key_release, env);
	mlx_hook(WINDOW, 2, 1L << 0 | 1 << 1, &key_press, env);
	mlx_hook(WINDOW, 4, 0L, &focus_in, env);
}

void initilalize_x_server(t_env *env) {
	WINDOW_WIDTH = DEFAULT_WINDOW_WIDTH;
	WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

	X_SERVER = mlx_init();
	WINDOW = mlx_new_window(X_SERVER, WINDOW_WIDTH, WINDOW_HEIGHT, "FRACTOL");
	IMAGE = mlx_new_image(X_SERVER, WINDOW_WIDTH, WINDOW_HEIGHT);
	IMAGE_BUFFER = mlx_get_data_addr(IMAGE, &BPP, &SIZE_LINE, &ENDIAN);

	mlx_put_image_to_window(X_SERVER, WINDOW, IMAGE, 0, 0);

	initialize_key_events(env);
}

void initilalize_program_values(t_env *env)
{
	env->lock = 0;

	env->cursor.x = 0;
	env->cursor.y = 0;

	env->max_iteration = 250;

	if (env->f == &third_set)
		env->max_iteration = 200;

	env->offset.x = 0;
	env->offset.y = 0;

	RE(env->constante) = -0.7;
	I(env->constante) = 0.27015;

	env->zoom = 1;

	env->center.x = DEFAULT_WINDOW_WIDTH / 2;

	env->center.y = DEFAULT_WINDOW_HEIGHT / 2;
}

void	initialize_env(t_env *env)
{
	initilalize_x_server(env);
	initilalize_program_values(env);
	initialize_key_events(env);
}

void run(t_env *env) {
	mlx_loop(X_SERVER);
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
		error(USAGE);

	initialize_env(&env);

//	threads(&env);

	if (env.f == &julia_set)
		display_info_maths(&env);

	run(&env);

	return (0);
}
