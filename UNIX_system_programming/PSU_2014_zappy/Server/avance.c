/*
** fptr_action.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:14:33 2015 Younes Iddahamou
** Last update Mon Jun 29 15:01:40 2015 Bastos-Fix
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/action.h"
#include "header/fonction.h"
#include "header/graphic.h"

int	check_graph_answer_avance(t_action *action, t_env *env)
{
  char	*answer;

  if (env->graph_client != NULL)
    {
      if ((answer = malloc(30 * sizeof(char))) == NULL)
	{
	  delete_action(action);
	  return (1);
	}
      sprintf(answer, "ppo %d %d %d %d\n", action->client->player.id,
	      action->client->player.coor.x, action->client->player.coor.y,
	      action->client->player.dir);
      add_output(env->graph_client, answer);
    }
  return (0);
}

void		avance(t_env *env, t_action *action)
{
  static short	tab[4] = {1, 1, -1, -1};
  enum e_dir	dir;
  int		x;
  int		y;

  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      x = action->client->player.coor.x;
      y = action->client->player.coor.y;
      env->map.map[y][x][JOUEUR] -= 1;
      dir = action->client->player.dir;
      if (dir == LEFT || dir == RIGHT)
	action->client->player.coor.x += tab[dir];
      else if (dir == UP || dir == DOWN)
	action->client->player.coor.y += tab[dir];
      checkPos(&(action->client->player), &(env->map));
      x = action->client->player.coor.x;
      y = action->client->player.coor.y;
      env->map.map[y][x][JOUEUR] += 1;
      add_output(action->client, strdup("ok\n"));
      ppo(env, action->client);
      delete_action(action);
    }
}
