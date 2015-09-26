/*
** init_player2.c for init player in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:39:43 2015 Sebastien Lauret
** Last update Sun Jul  5 15:39:44 2015 Sebastien Lauret
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/env.h"
#include "header/graphic.h"
#include "header/fonction.h"

void	msg_init_player(t_env *env, t_action *action)
{
  add_output(action->client,
	     strdup(itoa(free_slot(env, action->client->team))));
  add_output(action->client, strdup("\n"));
  add_output(action->client, strdup(itoa(env->map.width)));
  add_output(action->client, strdup(" "));
  add_output(action->client, strdup(itoa(env->map.height)));
  add_output(action->client, strdup("\n"));
  pnw(env, action->client);
}

int	search_team(t_env *env, t_action *action)
{
  int	i;

  i = 0;
  while (strcmp(env->teams[i].name, action->input[0]) != 0)
    ++i;
  return (i);
}

void		select_init_player(t_env *env, t_action *action)
{
  t_client	*client;
  int		i;

  i = search_team(env, action);
  if (env->max_nb_team  > nb_client(&env->teams[i]))
    {
      init_var_player(env, action->client, i);
      create_action(action->first, NULL, action->client, DEATH);
    }
  else if ((client = search_egg(env, i)) != NULL)
    {
      env->clients[action->client->fd] = client;
      client->role = IA;
      client->fd = action->client->fd;
      action->client->prev->next = action->client->next;
      action->client->next->prev = action->client->prev;
      free(action->client);
      action->client = client;
      ebo(env, client);
    }
}

void	init_player(t_env *env, t_action *action)
{
  if (action->client->role == AUCUN)
    select_init_player(env, action);
  if (action->client->role == AUCUN)
    {
      action->client->prev->next = action->client->next;
      action->client->next->prev = action->client->prev;
      env->clients[action->client->fd] = FD_FREE;
    }
  else
    msg_init_player(env, action);
  delete_action(action);
}
