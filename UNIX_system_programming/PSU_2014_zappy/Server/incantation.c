/*
** incantation.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Tue Jun 23 14:38:27 2015 Younes Iddahamou
** Last update Sun Jul  5 18:25:19 2015 Younes Iddahamou
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/fonction.h"

int	g_incantations[7][8] = {{0, 1, 0, 0, 0, 0, 0, 1},
				{0, 1, 1, 1, 0, 0, 0, 2},
				{0, 2, 0, 1, 0, 2, 0, 2},
				{0, 1, 1, 2, 0, 1, 0, 4},
				{0, 1, 2, 1, 3, 0, 0, 4},
				{0, 1, 2, 3, 0, 1, 0, 6},
				{0, 2, 2, 2, 2, 2, 1, 6}};

int	check_objects(int ***map, t_player *player)
{
  int	i;
  int	x;
  int	y;
  int	lvl;

  i = 0;
  x = player->coor.x;
  y = player->coor.y;
  lvl = player->lvl;
  while (++i < JOUEUR)
    {
      if (map[y][x][i] != g_incantations[lvl - 1][i])
	return (-1);
    }
  return (0);
}

int	check_players(t_client **clients, t_client *caster)
{
  int	i;
  int	nb_players;
  int	players;

  i = 0;
  players = g_incantations[caster->player.lvl - 1][JOUEUR];
  nb_players = 0;
  while (i < MAX_FD && nb_players != players)
    {
      if (clients[i] != NULL
	  && clients[i]->player.coor.x == caster->player.coor.x
	  && clients[i]->player.coor.y == caster->player.coor.y
	  && clients[i]->player.lvl == caster->player.lvl)
	++nb_players;
      i = i + 1;
    }
  if (nb_players < g_incantations[caster->player.lvl - 1][JOUEUR])
    return (-1);
  return (0);
}

void	check_incantation(t_env *env, t_action *action)
{
  int	i;

  i = -1;
  if (check_objects(env->map.map, &(action->client->player)) != 0
      && check_players(env->clients, action->client) != 0)
    {
      add_output(action->client, strdup("ko\n"));
      delete_action(action);
      return ;
    }
  while (++i < QPORT_LEN)
    {
      if (env->clients[i] != NULL
	  && env->clients[i]->player.coor.x == action->client->player.coor.x
	  && env->clients[i]->player.coor.y == action->client->player.coor.y
	  && env->clients[i]->player.lvl == action->client->player.lvl)
	add_output(env->clients[i], strdup("elevation en cours\n"));
    }
  if (env->graph_client != NULL)
    send_graph_check(env, env->clients, action->client);
  create_action(&env->action, NULL, action->client, INCANTATION);
  delete_action(action);
}

void	level_up(t_env *env, t_client *caster, char *str)
{
  int	i;
  int	x;
  int	y;

  i = 0;
  x = caster->player.coor.x;
  y = caster->player.coor.y;
  add_output(caster, strdup(str));
  while (i < QPORT_LEN)
    {
      if (env->clients[i] != NULL
	  && env->clients[i]->player.coor.x == caster->player.coor.x
	  && env->clients[i]->player.coor.y == caster->player.coor.y
	  && env->clients[i]->player.lvl + 1 == caster->player.lvl)
	{
	  env->clients[i]->player.lvl += 1;
	  add_output(env->clients[i], strdup(str));
	}
      i = i + 1;
    }
  i = 0;
  while (++i < 7)
    env->map.map[y][x][i] -= g_incantations[caster->player.lvl - 2][i];
  free(str);
}

void	incantation(t_env *env, t_action *action)
{
  char	*str;

  str = NULL;
  if (difftime(time(NULL), action->time) >= (300 / env->time))
    {
      str = malloc(sizeof(*str) * 20);
      memset(str, 0, 20);
      if (check_objects(env->map.map, &(action->client->player)) != 0
	  && check_players(env->clients, action->client) != 0)
	{
	  sprintf(str, "niveau actuel : %d\n", action->client->player.lvl);
	  if (env->graph_client != NULL)
	    send_graph_incant(env, action->client, 0, &env->map);
	  add_output_incantation(env->clients, action->client, str);
	  delete_action(action);
	  return ;
	}
      action->client->player.lvl += 1;
      sprintf(str, "niveau actuel : %d\n", action->client->player.lvl);
      level_up(env, action->client, str);
      if (env->graph_client != NULL)
	send_graph_incant(env, action->client, 1, &env->map);
      delete_action(action);
    }
}
