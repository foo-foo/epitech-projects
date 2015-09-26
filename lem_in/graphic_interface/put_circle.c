/*
** put_circle.c for anthill.c in /home/benoit_l/rendu/lem-in
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Fri Apr 25 14:32:53 2014 Benoit Leo
** Last update Sun May  4 19:47:48 2014 menich_a
*/

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include "graph.h"

int		put_circle(t_img *img, int x, int y, int r)
{
  double	a;
  int		x1;
  int		y1;
  int		compt;

  a = -0.5;
  compt = 0;
  while (a > -360)
    {
      while (++compt < r)
        {
          x1 = x + (compt * cos(a));
          y1 = y + (compt * sin(a));
          put_pixel_image(img, x1, y1, 7, 7, 49);
        }
      a = a - ((2 * 3.14)/(8 * r));
      compt = 0;
    }
  return (0);
}
