/*
** background.c for back.c in /home/benoit_l/rendu/lem-in
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Thu Apr 24 09:31:24 2014 Benoit Leo
** Last update Sun May  4 19:43:55 2014 menich_a
*/

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

void	gere_texture(t_img *img)
{
  int	x;
  int	y;

  srand(clock());
  x = rand();
  y = rand();
  put_pixel_image(img, x % 1500, 120 + (y % 1000), 3, 3, 53);
}

void	gere_texture_grass(t_img *img)
{
  int	x;
  int	y;

  srand(clock());
  x = rand();
  y = rand();
  put_pixel_image(img, x % 1500, 100 + (y % 120), 0, 102, 0);
  put_pixel_image(img, x % 1500 - 1, 99 + (y % 105), 203, 132, 97);
}

void	sky(t_img *img)
{
  int	x;
  int	y;

  x = 0;
  y = 0;
  while (y <= 100)
    {
      while (x <= 1500)
        {
          put_pixel_image(img, x, y, 203, 132, 97);
          x++;
        }
      x = 0;
      y++;
    }
}

void	grass(t_img *img)
{
  int	x;
  int	y;

  x = 0;
  y = 100;
  while (y <= 120)
    {
      while (x <= 1500)
        {
	  gere_texture_grass(img);
          put_pixel_image(img, x, y, 51, 255, 51);
          x++;
        }
      x = 0;
      y++;
    }
}

void	ground(t_img *img)
{
  int	x;
  int	y;

  x = 0;
  y = 120;
  while (y <= 1000)
    {
      while (x <= 1500)
        {
	  gere_texture(img);
          put_pixel_image(img, x, y, 51, 102, 153);
          x++;
        }
      x = 0;
      y++;
    }
}
