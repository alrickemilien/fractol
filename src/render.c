#include "fractol.h"

void	render(t_env *env)
{
		t_env		*tmp;
		int			i;
		int			ret;

		if (!(tmp = (t_env*)malloc(sizeof(t_env) * NUMBER_OF_THREADS)))
			error("error malloc in tmp env");

		i = 0;
		while (i < NUMBER_OF_THREADS)
		{
			ft_memcpy(&tmp[i], env, sizeof(t_env));

			tmp[i].thread_index = i;

			if (pthread_create(&(THREADS[i]), NULL, env->f, tmp + i))
				error("error pthread_create");
			i++;
		}

		i = 0;
		while (i < NUMBER_OF_THREADS)
		{
			if ((ret = pthread_join(THREADS[i], NULL)) != 0)
				error("error pathread join");

			i++;
		}

		mlx_put_image_to_window(X_SERVER, WINDOW, IMAGE, 0, 0);

		free(tmp);
}
