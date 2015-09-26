/*
** gere_img.c for gere_img.c in /home/benoit_l/rendu/lem-in/v2.0
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Fri May  2 11:26:57 2014 Benoit Leo
** Last update Sun May  4 19:44:25 2014 menich_a
*/

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include "graph.h"

t_img	*init_img(t_img *img, int width, int height)
{
  img->width = width;
  img->height = height;
  img->data = mlx_get_data_addr(img->img_ptr,
				&img->bpp, &img->szline, &img->end);
  return (img);
}

int	gereexpose_coord(t_img *lem, int x, int y)
{
  mlx_put_image_to_window(lem->init, lem->window, lem->img_ptr, x - 10, y - 10);
  return (0);
}

int	gereexpose(t_img *img)
{
  mlx_put_image_to_window(img->init, img->window, img->img_ptr, 0, 0);
  return (0);
}

t_img	*creat_img(t_img *img)
{
  img = malloc(sizeof(t_img));
  if (img == NULL)
    return (NULL);
  img->init = mlx_init();
  img->window = mlx_new_window(img->init, 1500, 1000, "lem-in");
  img->img_ptr = mlx_new_image(img->init, 1500, 1000);
  img = init_img(img, 1500, 1000);
  return (img);
}

t_img	*creat_ants(t_img *lem, t_img *img)
{
  lem = malloc(sizeof(t_img));
  if (lem == NULL)
    return (NULL);
  lem->init = mlx_init();
  lem->window = img->window;
  lem->img_ptr = mlx_new_image(lem->init, 20, 20);
  lem = init_img(lem, 20, 20);
  return (lem);
}
