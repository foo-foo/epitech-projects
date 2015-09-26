/*
** graphic3.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
**
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
**
** Started on  Sun Jul  5 15:37:50 2015 Sebastien Lauret
** Last update Sun Jul  5 17:42:42 2015 Bastos-Fix
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	tna(t_env *env)
{
  int	i;

  i = 0;
  if (env->graph_client != NULL)
    {
      while (i < env->nb_team)
	{
	  add_output(env->graph_client, strdup("tna "));
	  add_output(env->graph_client, strdup(env->teams[i].name));
	  add_output(env->graph_client, strdup("\n"));
	  ++i;
	}
    }
}

void	fptr_tna(t_env *env, t_action *action)
{
  tna(env);
  delete_action(action);
}

void	pnw(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pnw "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.y)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client,
		 strdup(itoa(((client->player.dir + 1) % 4) + 1))); /// a test
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.lvl)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(env->teams[client->team].name));
      add_output(env->graph_client, strdup("\n"));
    }
}

t_client	*find_by_id(t_env *env, int id)
{
  t_client	*client;
  int		i;

  i = 0;
  while (i < env->nb_team)
    {
      client = env->teams[i].clients.next;
      while (client->root != 1)
	{
	  if (client->player.id == id)
	    return (client);
	  client = client->next;
	}
      ++i;
    }
  return (NULL);
}

void		fptr_ppo(t_env *env, t_action *action)
{
  int		id;
  char		*err;
  t_client	*client;

  err = NULL;
  if (action->input[1] == NULL)
    sbp(env);
  else
    {
      id = strtol(action->input[1], &err, 10);
      if (err[0] != '\0' || (client = find_by_id(env, id)) == NULL)
	sbp(env);
      else
	ppo(env, client);
    }
  delete_action(action);
}
