/*
** graph_calcul.c for  in /home/bencha_a/PSU_2014_lemipc
** 
** Made by Aniss Bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri Mar  6 14:49:34 2015 Aniss Bencharif
** Last update Sun Mar  8 22:37:43 2015 Anatole Menichetti
*/

#include "../includes/graph.h"

int	get_nbr_player(char *map, int size)
{
  int	i;

  i = 0;
  if (map)
    while (i < (size * size))
      {
	if (map[i] != '\0')
	  return (0);
	i++;
      }
  return (-1);
}

void	adjust_size(int *x, int *y, int i, int map_size)
{
  *x = (i % map_size) * (1024 / map_size);
  *y = (i / map_size) * (1024 / map_size);
}

void	get_pos(int *x, int *y, char map, int i, int size)
{
  if (map >= 1 && map <= 6)
    adjust_size(x, y, i, size);
  else
    *x = -42;
}
