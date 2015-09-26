/*
** get_vision.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 11:12:03 2015 Anatole Menichetti
** Last update Wed Jun 24 00:00:36 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Returns the current square priority.
*/
static int	get_current_square_priority(char *square_objs,
					    int const need_to_rise)
{
  int		i;
  int		priority;

  i = 0;
  priority = 0;
  if (square_objs)
    while (square_objs[i])
      {
	if (square_objs[i] > 48)
	  {
	    if (square_objs[i] - 49 == FOOD)
	      priority += FOOD_PRIORITY;
	    else if (square_objs[i] - 49 == PLAYER)
	      priority += !i ? 0 : PLAYER_PRIORITY - need_to_rise;
	    else
	      priority += STONE_PRIORITY;
	  }
	i += 1;
      }
  return (priority);
}

/*
**		Creates a tab containing the sum of objects priorities \
**		for each square in the vision field.
*/
int		**get_vision_priorities(char ***vision, int const need_to_rise)
{
  int		**priorities;
  int		size;
  int		y;
  int		x;

  y = 0;
  size = tablen(vision);
  if (!(priorities = malloc(sizeof(*priorities) * (size + 1))))
    return (NULL);
  while (y < size)
    {
      x = 0;
      if (!(priorities[y] = malloc(sizeof(*priorities[y]) * (2 * y + 2))))
	return (NULL);
      while (x < 2 * y + 1)
	{
	  priorities[y][x] = get_current_square_priority(vision[y][x],
							 need_to_rise);
	  x += 1;
	}
      priorities[y][x] = -1;
      y += 1;
    }
  priorities[y] = NULL;
  return (priorities);
}
