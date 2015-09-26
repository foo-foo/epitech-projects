/*
** gere_move_ant.c for gere_move_fourmis.c in /home/benoit_l/rendu/lem-in/v2.0
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Fri May  2 12:55:35 2014 Benoit Leo
** Last update Sun May  4 19:45:32 2014 menich_a
*/

#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include "graph.h"

int	draw_ant(t_img *lem, int x1, int y1, int x2, int y2, int i)
{
  if (square_power((x2 - x1)) > square_power((y2 - y1)))
    return (ant_case_one(lem, x1, y1, x2, y2, i));
  return (ant_case_two(lem, x1, y1, x2, y2, i));
}

int	ant_case_one(t_img *lem, int x1,int y1,int x2,int y2, int i)
{
  int	x;

  if (x1 + i == x2 || x1 + i == 0 || x1 - i == x2)
    return (-1);
  x = x1;
  if (x1 > x2)
    {
      if (x - i >= x2)
        {
          x = x - i;
          gereexpose_coord(lem, x, y1+((y2-y1)*(x-x1))/(x2-x1));
        }
      return (0);
    }
  if (x + i <= x2)
    {
      x = x + i;
      gereexpose_coord(lem, x, y1+((y2-y1)*(x-x1))/(x2-x1));
      x++;
    }
  return (0);
}

int	ant_case_two(t_img *lem, int y1, int x1, int y2, int x2, int i)
{
  int	x;

  x = x1;
  if (x1 - i == x2 || x1 + i == x2)
    return (-1);
  if (x1 > x2)
    {
      if ((x - i) >= x2)
        {
          x = x - i;
          gereexpose_coord(lem, y1+((y2-y1)*(x-x1))/(x2-x1), x);
        }
      return (0);
    }
  if ((x + i) <= x2)
    {
      x = x + i;
      gereexpose_coord(lem, y1+((y2-y1)*(x-x1))/(x2-x1), x);
      x++;
    }
  return (0);
}

void	move_in_tunnel(t_img *lem, t_ant *ptr)
{
  int	x;
  int	c;

  x = 0;
  c = 0;
  if (ptr->moving)
    {
      x = 0;
      c = 0;
      while (c == 0)
        {
          c =  draw_ant(lem, (ptr->old_x * 10 + 1) % 1500,
                       (ptr->old_y * 10 + 1) % 850 + 150,
                       (ptr->new_x * 10 + 1) % 1500,
                       (ptr->new_y * 10 + 1) % 850 + 150, x++);
          usleep(10000);
        }
      ptr->moving = 0;
    }
}

void	move_ants(char **way, t_coord *coord, t_ant *ants, t_img *lem)
{
  int	i;
  t_ant	*ptr;

  i = 0;
  while (way[i] != NULL)
    {
      adjust_list(coord, ants, way[i]);
      ptr = ants;
      while (ptr)
        {
          move_in_tunnel(lem, ptr);
          ptr = ptr->next;
        }
      i = i + 1;
    }
}
