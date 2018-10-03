#include "fractol.h"

void	render(t_env *env)
{
		pthread_t	*pthread;
		t_env		*tmp;
		int			i;

		if (!(pthread = (pthread_t*)malloc(sizeof(pthread_t) * NUMBER_OF_THREADS)))
			error("error malloc in threads");

		if (!(tmp = (t_env*)malloc(sizeof(t_env) * NUMBER_OF_THREADS)))
			error("error malloc in tmp env");

		i = 0;
		while (i < NUMBER_OF_THREADS)
		{
			ft_memcpy(tmp, env, sizeof(t_env));

			tmp[i].thread_index = i;

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

		mlx_put_image_to_window(X_SERVER, WINDOW, IMAGE, 0, 0);

		free(pthread);
		free(tmp);
}
