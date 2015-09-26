/*
** fptr_action.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:14:33 2015 Younes Iddahamou
** Last update Sun Jul  5 16:16:27 2015 Ivan Toma
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/map.h"
#include "header/client.h"
#include "header/action.h"
#include "header/env.h"
#include "header/fonction.h"
#include "header/graphic.h"

char		*itoa(int nb)
{
  static char	tab[32] = {0};
  int		i = 30;

  if (nb == 0)
    {
      tab[i] = '0';
      return (&tab[i]);
    }
  while (nb && i)
    {
      tab[i] = (nb % 10) + 0x30;
      --i;
      nb /= 10;
    }
  return (&tab[i + 1]);
}

int	add_output(t_client *client, char *str)
{
  if (!client || !str)
    return (0);
  if (client->output == NULL)
    client->output = str;
  else
    {
      client->output = realloc(client->output, (size_t)
			       (strlen(client->output) + strlen(str) + 1));
      strcat(client->output, str);
      free(str);
    }
  return (0);
}

void	init_graphique(t_env *env, t_action *action)
{
  if (env->graph_client == NULL
      && action->client->role == AUCUN)
    {
      action->client->prev->next =  action->client->next;
      action->client->next->prev =  action->client->prev;
      action->client->role = GRAPHIQUE;
      action->client->graphic_init = 1;
      env->graph_client = action->client;
      msz(env);
      sgt(env);
      action->client->player.coor.y = 0;
      action->client->player.coor.x = 0;
      create_action(action, NULL, action->client, 14);
    }
  else
    {
      env->clients[action->client->fd]->next->prev
	= env->clients[action->client->fd]->prev;
      env->clients[action->client->fd]->prev->next
	= env->clients[action->client->fd]->next;
      close(action->client->fd);
      env->clients[action->client->fd] = NULL;
      free(env->clients[action->client->fd]);
     }
  delete_action(action);
}

void	inventaire(t_env *env, t_action *action)
{
  int	i;

  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      i = 0;
      add_output(action->client, strdup("{"));
      while (i < 7)
	{
	  if (i != 0)
	    add_output(action->client, strdup(","));
	  add_output(action->client, strdup(env->stone_name[i]));
	  add_output(action->client, strdup(" "));
	  add_output(action->client,
		     strdup(itoa(action->client->player.inventaire[i])));
	  i++;
	}
      add_output(action->client, strdup("}\n"));
      delete_action(action);
    }
}
