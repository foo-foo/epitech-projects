/*
** fptr_voir.c for voir in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:38:13 2015 Sebastien Lauret
** Last update Sun Jul  5 15:38:14 2015 Sebastien Lauret
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/env.h"
#include "header/action.h"
#include "header/fptr_action.h"

void	element_case(int *map, t_client *client, char **stone_name)
{
  int	i;
  int	j;

  i = 0;
  while (i <= JOUEUR)
    {
      j = 0;
      if (map[i] >= 0)
	{
	  while (j < map[i])
	    {
	      add_output(client, strdup(" "));
	      add_output(client, strdup(stone_name[i]));
	      ++j;
	    }
	}
      ++i;
    }
}

t_coor		voir_select_coor(t_action *action, int largeur, int deep)
{
  t_coor	coor;
  int		dir;

  dir = action->client->player.dir;
  if (dir == RIGHT)
    {
      coor.x = (int)(action->client->player.coor.x) + deep;
      coor.y = (int)(action->client->player.coor.y) - largeur;
    }
  else if (dir == LEFT)
    {
      coor.x = (int)(action->client->player.coor.x) - deep;
      coor.y = (int)(action->client->player.coor.y) + largeur;
    }
  else if (dir == UP)
    {
      coor.y = (int)(action->client->player.coor.y) + deep;
      coor.x = (int)(action->client->player.coor.x) + largeur;
    }
  else if (dir == DOWN)
    {
      coor.y = (int)(action->client->player.coor.y) - deep;
      coor.x = (int)(action->client->player.coor.x) - largeur;
    }
  return (coor);
}

void		voir_case(t_env *env, t_action *action, int largeur, int deep)
{
  t_coor	coor;

  coor = voir_select_coor(action, largeur, deep);
  if (coor.x < 0)
    coor.x = env->map.width + coor.x;
  if (coor.y < 0)
    coor.y = env->map.height + coor.y;
  element_case(env->map.map[coor.y % env->map.height][coor.x % env->map.width],
	       action->client, env->stone_name);
}

void	voir(t_env *env, t_action *action)
{
  int	largeur;
  int	deep;

  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      add_output(action->client, strdup("{"));
      deep = 0;
      while (deep <= action->client->player.lvl)
	{
	  largeur = -deep;
	  while (largeur < deep + 1)
	    {
	      if (deep != 0)
		add_output(action->client, strdup(","));
	      voir_case(env, action, largeur, deep);
	      ++largeur;
	    }
	  ++deep;
	}
      add_output(action->client, strdup("}\n"));
      delete_action(action);
    }
}
