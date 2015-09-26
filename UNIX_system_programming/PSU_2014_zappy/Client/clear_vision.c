/*
** clear_vision.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 17:29:50 2015 Anatole Menichetti
** Last update Wed Jun 24 05:37:50 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Proceed to the clear of excess stones.
*/
static int	clear_excess(char ***vision, int cpt, int x, int y)
{
  int		i;
  char		*tmp;

  if (!(tmp = malloc(sizeof(*tmp) * (strlen(vision[y][x]) - cpt + 1))))
    return (0);
  i = 0;
  cpt = 0;
  while (vision[y][x][i])
    {
      if (vision[y][x][i] != '#')
	tmp[cpt++] = vision[y][x][i];
      i += 1;
    }
  tmp[cpt] = '\0';
  free(vision[y][x]);
  vision[y][x] = tmp;
  return (1);
}

static int	get_excess(t_player *p, int obj)
{
  int		i;
  size_t	max;

  i = p->lvl - 1;
  max = 0;
  if (obj == 49 && p->stuff[FOOD] > MAX_FOOD)
    return (1);
  if (obj <= 49 || obj >= 56)
    return (0);
  obj -= 49;
  while (i < 7)
    {
      max += p->requirements[i][obj];
      i += 1;
    }
  if (p->stuff[obj] > max)
    return (1);
  return (0);
}

/*
**		Remove every stone from square if player don't need more.
*/
static int	remove_current_square_excess(t_player *p, char ***vision,
					      int x, int y)
{
  int		i;
  int		cpt;
  int		nbr_players;

  i = 0;
  cpt = 0;
  nbr_players = 0;
  while (vision[y][x][i])
    {
      if (vision[y][x][i] == 56)
	nbr_players += 1;
      if (get_excess(p, vision[y][x][i]))
	{
	  vision[y][x][i] = '#';
	  cpt += 1;
	}
      i += 1;
    }
  if (nbr_players > 1 || (y && x && nbr_players > 0))
    vision[y][x][0] = '\0';
  if (cpt && nbr_players <= 1 && (!y || !x || !nbr_players))
    return (clear_excess(vision, cpt, x, y));
  return (1);
}

/*
**		Remove every stone from vision if player don't need more.
*/
int		remove_stones_excess(t_player *p, char ***vision)
{
  int		y;
  int		x;

  y = 0;
  while (vision[y])
    {
      x = 0;
      while (vision[y][x])
	{
	  if (!remove_current_square_excess(p, vision, x, y))
	    return (0);
	  x += 1;
	}
      y += 1;
    }
  return (1);
}

/*
**		Remove every stone from vision.
*/
void		remove_stones(char ***vision)
{
  int		y;
  int		x;
  int		i;
  int		cpt;

  y = -1;
  while (vision[++y])
    {
      x = 0;
      while (vision[y][x])
	{
	  i = 0;
	  cpt = 0;
	  while (vision[y][x][i])
	    {
	      if (vision[y][x][i] == '1')
		vision[y][x][cpt++] = '1';
	      if (vision[y][x][i] == '8')
		vision[y][x][cpt++] = '8';
	      i += 1;
	    }
	  vision[y][x][cpt] = '\0';
	  x += 1;
	}
    }
}
