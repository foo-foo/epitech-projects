/*
** init_player.c for init player in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:37:05 2015 Sebastien Lauret
** Last update Sun Jul  5 15:37:07 2015 Sebastien Lauret
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/env.h"
#include "header/fonction.h"
#include "header/graphic.h"

t_client	*alloc_client(t_env *env, char *msg)
{
  t_client	*client;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  env->teams[env->nb_team].clients.prev->next = client;
  client->prev = env->teams[env->nb_team].clients.prev;
  client->next = &env->teams[env->nb_team].clients;
  env->teams[env->nb_team].clients.prev = client;
  client->output = msg;
  client->fd = 0;
  client->id_egg = 0;
  client->root = 0;
  client->role = AUCUN;
  client->team = 0;
  client->egg = 0;
  return (client);
}

int		nb_client(t_team *team)
{
  t_client	*client;
  int		nb;

  nb = 0;
  client = team->clients.next;
  while (client->root != 1)
    {
      if (client->egg == 0)
	++nb;
      client = client->next;
    }
  return (nb);
}

void		init_var_player(t_env *env, t_client *client, int team)
{
  static int	id = 0;
  int		i;

  client->prev->next = client->next;
  client->next->prev = client->prev;
  env->teams[team].clients.prev->next = client;
  client->prev = env->teams[team].clients.prev;
  client->next = &env->teams[team].clients;
  env->teams[team].clients.prev = client;
  client->role = IA;
  client->player.id = ++id;
  client->player.lvl = DEFAULT_LVL;
  client->player.coor.x = rand() % env->map.width;
  client->player.coor.y = rand() % env->map.height;
  env->map.map[client->player.coor.y][client->player.coor.x]
    [JOUEUR] += 1;
  client->player.dir = rand() % 4;
  client->team = team;
  i = 0;
  client->player.inventaire[i] = DEFAULT_FOOD;
  while (++i < 7)
    client->player.inventaire[i] = 0;
}

t_client	*search_egg(t_env *env, int team)
{
  t_client	*client;

  client = env->teams[team].clients.next;
  while (client->root != 1)
    {
      if (client->role == EGG)
	return (client);
      client = client->next;
    }
  return (NULL);
}
