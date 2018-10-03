#include "fractol.h"

int random_moves(void *param)
{
  t_env	*env;
  double n;
  double random_value;

  n = 1;

	env = (t_env *)param;

  if (rand() % 2)
    n = -1;

  random_value = (double)rand() / RAND_MAX * 2.0 - 1.0;

  (void)random_value;


    I(env->constante) = I(env->constante) +  n * 0.0001;
    RE(env->constante) = RE(env->constante) + n * 0.0001;

    render(env);

  usleep(300000);


  return (0);
}
