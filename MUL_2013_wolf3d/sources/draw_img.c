/*
** draw_img.c for wolf3d in /home/menich_a/rendu/MUL_2013_wolf3d
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan  8 14:07:02 2014 menich_a
** Last update Sun Jan 12 20:23:17 2014 menich_a
*/

#include "wolf3d.h"

void		draw_sky(int y_max)
{
  int		x;
  int		y;
  t_color	color;

  y = 0;
  color = init_color(100, 150, 255);
  while (y < y_max)
    {
      x = 0;
      while (x < 750)
        {
          mlx_pixel_put_img(x, y, color);
          x = x + 1;
        }
      y = y + 1;
    }
}

void		draw_wall(int y_min, int y_max, int height)
{
  int		x;
  int		y;
  t_color	color;

  x = 0;
  y = y_min;
  color = init_color(0, 0, 0);
  while (x < 750)
    mlx_pixel_put_img(x++, y, color);
  while (y < y_max)
    {
      x = 0;
      y = y + 1;
      while (x < 750)
        {
          color = init_color(225, 225, 255);
          if (y > y_max - height / 2 && x > 375 - height / 4 && x < 375 + height / 4)
            color = init_color(0, 0, 0);
          mlx_pixel_put_img(x++, y, color);
        }
    }
  color = init_color(0, 0, 0);
  x = 0;
  while (x < 750)
    mlx_pixel_put_img(x++, y, color);
}

void		draw_ground(int y_min)
{
  int		x;
  int		y;
  t_color	color;

  color = init_color(125, 255, 125);
  y = y_min;
  while (y < 500)
    {
      x = 0;
      y = y + 1;
      while (x < 750)
        {
	  mlx_pixel_put_img(x, y, color);
          x = x + 1;
        }
    }
}

void            draw_way(int y_min, int max)
{
  int		min;
  int           nb;
  int           x;
  int           y;
  t_color       color;

  nb = 0;
  x = 0;
  y = y_min;
  min = 375 - max;
  max = 375 + max;
  color = init_color(0, 0, 0);
  while (y < 500)
    {
      x = min - nb;
      mlx_pixel_put_img(x++, y++, color);
      color = init_color(255, 255, 200);
      while (x < max + nb)
	mlx_pixel_put_img(x++, y, color);
      color = init_color(0, 0, 0);
      mlx_pixel_put_img(x, y++, color);
      if (y % 3 == 0)
        nb = nb + 1;
    }
}

int             draw_img(int y_min, int y_max)
{
  int		height;

  height = y_max - y_min;
  draw_sky(y_min);
  draw_ground(y_max);
  draw_wall(y_min, y_max, height);
  draw_way(y_max, height / 4);
  return (0);
}
