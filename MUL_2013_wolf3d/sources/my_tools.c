/*
** my_tools.c for wolf3d in /home/menich_a/rendu/MUL_2013_wolf3d
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan  8 11:21:01 2014 menich_a
** Last update Sun Jan 12 20:34:57 2014 menich_a
*/

#include <stdlib.h>
#include <mlx.h>
#include "wolf3d.h"

int		gerekey(int keycode, void *param)
{
  t_mlx		*init;
  static int	nb = 5;

  init = (t_mlx*)param;
  if (keycode == ESCAPE)
    exit(0);
  if (keycode == UP)
    {
      if (nb + 5 > 200)
	return (1);
      nb = nb + 5;
    }
  if (keycode == DOWN)
    {
      if (nb - 5 < 0)
	return (1);
      nb = nb - 5;
    }
  draw_img(200 - nb, 200 + nb);
  expose(init);
  return (0);
}

int		expose(t_mlx *init)
{
  mlx_put_image_to_window(init->mlx_ptr, init->win_ptr, init->img_ptr, 0, 0);
  return (0);
}

void		init_img(t_mlx init, int x, int y)
{
  g_img.x = x;
  g_img.y = y;
  g_img.data = mlx_get_data_addr(init.img_ptr, &g_img.bpp, &g_img.sizeline, &g_img.endian);
}

int		mlx_pixel_put_img(int x, int y, t_color color)
{
  int		pos;

  if (g_img.x < x || g_img.y < y)
    {
      return (1);
    }
  pos = (y * g_img.sizeline) + (x * 4);
  g_img.data[pos] = color.b;
  g_img.data[pos + 1] = color.g;
  g_img.data[pos + 2] = color.r;
  return (0);
}

t_color		init_color(int red, int green, int blue)
{
  t_color	color;

  color.r = red;
  color.g = green;
  color.b = blue;
  return (color);
}
