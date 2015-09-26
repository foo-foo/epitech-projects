/*
** fork.c for zappy in /home/toma_i/rendu/PSU_2014_zappy
**
** Created by Ivan Toma
** Login   <@epitech.eu>
**
** Started on  Tue Jun 23 17:01:59 2015 Ivan Toma
** Last update Sat Jul  4 13:34:32 2015 Bastos-Fix
*/

#include "header/func.h"
#include "header/fptr_action.h"
#include "header/graphic.h"

void	send_graph_egg(t_env *env, t_action *action, t_client *client)
{
  char	*str;

  str = NULL;
  if (env->graph_client != NULL)
    {
      asprintf(&str, "enw %d %d %d %d\n", client->id_egg,
	       action->client->player.id, client->player.coor.x,
	       client->player.coor.y);
      add_output(env->graph_client, str);
    }
}

void		new_player(t_env *env, t_action *action)
{
  t_client	*client;
  static int	id = 0;

  if (difftime(time(NULL), action->time) >= 42 / env->time)
    {
      add_output(action->client, strdup("ok\n"));
      if ((client = alloc_client(env, NULL)) != NULL)
	{
	  client->fd = 0;
	  client->team = action->client->team;
	  client->egg = action->client->player.id;
	  client->player.coor.x = action->client->player.coor.x;
	  client->player.coor.y = action->client->player.coor.y;
	  client->id_egg = ++id;
	  enw(env, action->client, client);
	  create_action(action->first, NULL, client, ECLOSE);
	}
      delete_action(action);
    }
}

void	send_graph_fork(t_env *env, t_action *action)
{
  pfk(env, action->client);
  create_action(action->first, NULL, action->client, FORK);
  delete_action(action);
}

void	eclose(t_env *env, t_action *action)
{
  int	x;
  int	y;

  if (difftime(time(NULL), action->time) >= (600 / env->time))
    {
      x = action->client->player.coor.x;
      y = action->client->player.coor.y;
      init_var_player(env, action->client, action->client->team);
      action->client->role = EGG;
      action->client->player.coor.x = x;
      action->client->player.coor.y = y;
      eth(env, action->client);
      create_action(action->first, NULL, action->client, DEATH);
      delete_action(action);
    }
}
