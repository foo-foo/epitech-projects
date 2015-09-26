/*
** graphic4.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
**
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
**
** Started on  Sun Jul  5 15:39:05 2015 Sebastien Lauret
** Last update Sun Jul  5 17:38:46 2015 Bastos-Fix
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	ppo(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("ppo "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.y)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client,
		 strdup(itoa(((client->player.dir + 1) % 4) + 1)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void		fptr_plv(t_env *env, t_action *action)
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
	plv(env, client);
    }
  delete_action(action);
}

void	plv(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("plv "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.lvl)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void		fptr_pin(t_env *env, t_action *action)
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
	pin(env, client);
    }
  delete_action(action);
}

void	pin_msg(t_env *env, t_client *client)
{
  add_output(env->graph_client, strdup("pin "));
  add_output(env->graph_client, strdup(itoa(client->player.id)));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.coor.x)));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.coor.y)));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[0])));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[1])));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[2])));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[3])));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[4])));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[5])));
  add_output(env->graph_client, strdup(" "));
  add_output(env->graph_client, strdup(itoa(client->player.inventaire[6])));
  add_output(env->graph_client, strdup("\n"));
}
