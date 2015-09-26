/*
** tunnel.c for tunnel.c in /home/benoit_l/rendu/lem-in
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Thu Apr 24 12:49:36 2014 Benoit Leo
** Last update Sun May  4 19:50:29 2014 menich_a
*/

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include "graph.h"

int	square_power(int x)
{
  return (x * x);
}

int	draw_line(t_img *img, int x1, int y1, int x2, int y2)
{
  if (x1 - x2 == 0 && y1 - y2 == 0)
    return (0);
  if (x2 - x1 == 0 && y2 - y1 == 0)
    return (0);
  if (square_power((x2 - x1)) > square_power((y2 - y1)))
    draw_case_one(img, x1, y1, x2, y2);
  else
    draw_case_two(img, x1, y1, x2, y2);
  return (0);
}

void	tunnel(t_img *img, int x, int y)
{
  put_pixel_image(img, x, y, 7, 7, 49);
  put_pixel_image(img, x + 1, y, 7, 7, 49);
  put_pixel_image(img, x + 2, y, 7, 7, 49);
  put_pixel_image(img, x + 3, y, 7, 7, 49);
  put_pixel_image(img, x + 4, y, 7, 7, 49);
  put_pixel_image(img, x + 5, y, 7, 7, 49);
  put_pixel_image(img, x + 6, y, 7, 7, 49);
  put_pixel_image(img, x + 7, y, 7, 7, 49);
  put_pixel_image(img, x, y + 1, 7, 7, 49);
  put_pixel_image(img, x, y + 2, 7, 7, 49);
  put_pixel_image(img, x, y + 3, 7, 7, 49);
  put_pixel_image(img, x, y + 4, 7, 7, 49);
  put_pixel_image(img, x, y + 5, 7, 7, 49);
  put_pixel_image(img, x, y + 6, 7, 7, 49);
  put_pixel_image(img, x, y + 7, 7, 7, 49);
}

void	draw_case_two(t_img *img, int x1,int y1,int x2,int y2)
{
  int	x;
  int	tmp;

  tmp = 0;
  if (y1 > y2)
    {
      tmp = y1;
      y1 = y2;
      y2 = tmp;
      tmp = x1;
      x1 = x2;
      x2 = tmp;
    }
  tmp = x1;
  x1 = y1;
  y1 = tmp;
  tmp = x2;
  x2 = y2;
  y2 = tmp;
  x = x1;
  while (x <= x2)
    {
      tunnel(img, y1+((y2-y1)*(x-x1))/(x2-x1), x);
      x = x + 5;
    }
}

void	draw_case_one(t_img *img, int x1,int y1,int x2,int y2)
{
  int	x;
  int	tmp;

  tmp = 0;
  if (x1 > x2)
    {
      tmp = x1;
      x1 = x2;
      x2 = tmp;
      tmp = y1;
      y1 = y2;
      y2 = tmp;
    }
  x = x1;
  while (x <= x2)
    {
      tunnel(img, x, y1+((y2-y1)*(x-x1))/(x2-x1));
      x = x + 5;
    }
}
