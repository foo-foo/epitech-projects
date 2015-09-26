/*
** main.c for wolf3d in /home/menich_a/rendu/MUL_2013_wolf3d
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan  8 11:28:36 2014 menich_a
** Last update Sun Jan 12 20:34:45 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "wolf3d.h"

int	main(__attribute__((unused))int ac, __attribute__((unused))char **av, char **env)
{
  t_mlx	init;

  if (env == NULL || env[0] == NULL)
    return (1);
  init.mlx_ptr = mlx_init();
  if (init.mlx_ptr == NULL)
    return (1);
  init.win_ptr = mlx_new_window(init.mlx_ptr, 750, 500, "Wolf3d");
  if (init.win_ptr == NULL)
    return (1);
  init.img_ptr = mlx_new_image(init.mlx_ptr, 750, 500);
  if (init.img_ptr == NULL)
    return (1);
  init_img(init, 750, 500);
  mlx_put_image_to_window(init.mlx_ptr, init.win_ptr, init.img_ptr, 0, 0);
  mlx_expose_hook(init.win_ptr, &expose, &init);
  mlx_key_hook(init.win_ptr, &gerekey, &init);
  mlx_loop(init.mlx_ptr);
  pause();
  return (0);
}
