/*
** plan.c for plan.c in /home/benoit_l/rendu/lem-in
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Thu Apr 24 19:54:02 2014 Benoit Leo
** Last update Sun May  4 19:47:19 2014 menich_a
*/

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include "graph.h"
#include "math.h"

void	square(t_img *img, int x, int y, int color)
{
  int	x2;
  int	y2;

  x2 = x;
  y2 = y;
  while (y2 < y + 1)
    {
      while (x2 < x + 1)
        {
          put_pixel_image_lem(img, x2, y2, color);
          x2 = x2 + 1;
        }
      x2 = x;
      y2 = y2 + 1;
    }
}

void	put_square(t_img *img, char *buff)
{
  int	x;
  int	y;
  int	i;

  x = 0;
  y = 0;
  i = 0;
  while (buff[i] != '\0')
    {
      while (y < 20)
        {
          while (x < 20)
            {
              if (buff[i] == '1')
                square(img, x, y, 1);
  	      else if (buff[i] == '0')
		square(img, x, y, 0);
              x = x + 1;
	      i = i + 1;
            }
          x = 0;
          y = y + 1;
  	  i = i + 1;
        }
    }
}

int	put_pixel_image_lem(t_img *img, int x, int y, int color)
{
  int	pos;
  int	c1;
  int	c2;
  int	c3;

  c1 = 0;
  c2 = 0;
  c3 = 255;
  if (color == 0)
    {
      c1 = 7;
      c2 = 7;
      c3 = 49;
    }
  if (x >= img->width || y >= img->height || x < 0 || y < 0)
    return (0);
  pos = (y * img->szline) + (x * 4);
  img->data[pos] = c1;
  img->data[pos + 1] = c2;
  img->data[pos + 2] = c3;
  return (0);
}
