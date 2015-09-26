/*
** pose.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Mon Jun 22 15:39:35 2015 Younes Iddahamou
** Last update Sat Jul  4 00:43:08 2015 Bastos-Fix
*/

#include "header/func.h"
#include "header/fonction.h"
#include "header/graphic.h"

static int	checkIfExist(char *object, char **objects)
{
  int		i;

  i = 0;
  while (i < JOUEUR)
    {
      if (strcmp(objects[i], object) == 0)
	return (i);
      i = i + 1;
    }
  return (-1);
}

void		send_graph_prend(t_env *env, t_client *client, int object)
{
  pgt(env, client, object);
  pin(env, client);
  bct(env, client->player.coor.y, client->player.coor.x);
}

void		prend(t_env *env, t_action *action)
{
  int		obj;
  int		x;
  int		y;

  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      x = action->client->player.coor.x;
      y = action->client->player.coor.y;
      if (action->input[1] == NULL
	  || ((obj = checkIfExist(action->input[1], env->stone_name)) == -1
	      || env->map.map[y][x][obj] == 0))
	{
	  add_output(action->client, strdup("ko\n"));
	  delete_action(action);
	  return ;
	}
      action->client->player.inventaire[obj] += 1;
      env->map.map[y][x][obj] -= 1;
      send_graph_prend(env, action->client, obj);
      add_output(action->client, strdup("ok\n"));
      delete_action(action);
    }
}
