/*
** graphic2.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:38:59 2015 Sebastien Lauret
** Last update Sun Jul  5 15:39:00 2015 Sebastien Lauret
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	fptr_bct(t_env *env, t_action *action)
{
  int	x;
  int	y;
  char	*err1;
  char	*err2;

  err1 = NULL;
  err2 = NULL;
  if (action->input == NULL || action->input[0] == NULL
      || action->input[1] == NULL || action->input[2] == NULL)
    sbp(env);
  else
    {
      x = strtol(action->input[1], &err1, 10);
      y = strtol(action->input[2], &err2, 10);
      if (x < (int)env->map.height && y < (int)env->map.width
	  && err1[0] == '\0' && err2[0] == '\0')
	bct(env, y, x);
      else
	sbp(env);
    }
  delete_action(action);
}

void		send_pnw_player(t_env *env)
{
  int		i;
  t_client	*client;

  i = 0;
  while (env->nb_team > i)
    {
      client = env->teams[i].clients.next;
      while (client->root != 1)
        {
          if (client->role == IA)
            pnw(env, client);
          client = client->next;
        }
      ++i;
    }
}

void		send_pnw_egg(t_env *env)
{
  int		i;
  t_client	*client;

  i = 0;
  while (env->nb_team > i)
    {
      client = env->teams[i].clients.next;
      while (client->root != 1)
	{
	  if (client->role == EGG)
	    enw_init(env, client);
	  client = client->next;
	}
      ++i;
    }
}

void	init_graph_end(t_env *env, t_action *action)
{
  tna(env);
  send_pnw_player(env);
  send_pnw_egg(env);
  action->client->graphic_init = 0;
}

void	fptr_mct(t_env *env, t_action *action)
{
  bct(env, action->client->player.coor.y,
      action->client->player.coor.x++);

  if (action->client->player.coor.x >= (int)env->map.width)
    {
      action->client->player.coor.x = 0;
      action->client->player.coor.y++;
    }
  if (action->client->player.coor.y >= (int)env->map.height)
    {
      action->client->player.coor.y = 0;
      action->client->player.coor.x = 0;
      if (action->client->graphic_init == 1)
	init_graph_end(env, action);
      delete_action(action);
    }
}
