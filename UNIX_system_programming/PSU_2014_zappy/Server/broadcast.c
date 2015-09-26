/*
** broadcast.c for broadcast in /home/lauret_s/rendu/PSU_2014_zappy/Server
**
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
**
** Started on  Sun Jul  5 15:38:38 2015 Sebastien Lauret
** Last update Sun Jul  5 18:18:31 2015 Younes Iddahamou
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/env.h"
#include "header/action.h"
#include "header/fptr_action.h"
#include "header/graphic.h"

t_coor		define_vector(t_client *emeteur, t_client *recepteur,
			      t_map *map)
{
  t_coor	vec;
  int		base_x;
  int		base_y;

  base_x = emeteur->player.coor.x - recepteur->player.coor.x;
  base_y = emeteur->player.coor.y - recepteur->player.coor.y;
  vec.x = (base_x > 0)?
    -(map->width - emeteur->player.coor.x + recepteur->player.coor.x)
    : map->width - recepteur->player.coor.x + emeteur->player.coor.x;
  vec.y = (base_y > 0)?
    -(map->height - emeteur->player.coor.y + recepteur->player.coor.y)
    : map->height - recepteur->player.coor.y + emeteur->player.coor.y;
  vec.x = MIN(base_x, vec.x);
  vec.y = MIN(base_y, vec.y);
  return (vec);
}
/*
**  de la gauche vers le droite
**  1 indice : |Y|>|X|
**  2 indice : |X|>|Y|
**  3 indice : |X|==|Y|
**  4 indice : X>0
**  5 indice : Y>0
*/

void	init_tab_verite(int (*table_verite)[2][2][2][2][2])
{
  (*table_verite)[0][0][1][1][1] = 2;
  (*table_verite)[0][1][0][1][1] = 1;
  (*table_verite)[1][0][0][1][1] = 3;
  (*table_verite)[0][0][1][1][0] = 8;
  (*table_verite)[0][1][0][1][0] = 1;
  (*table_verite)[1][0][0][1][0] = 7;
  (*table_verite)[0][0][1][0][1] = 4;
  (*table_verite)[0][1][0][0][1] = 5;
  (*table_verite)[1][0][0][0][1] = 3;
  (*table_verite)[0][0][1][0][0] = 6;
  (*table_verite)[0][1][0][0][0] = 5;
  (*table_verite)[1][0][0][0][0] = 7;
}

void	send_msg(t_client *client, t_action *action, int angle)
{
  int	x;

  add_output(client, strdup("message "));
  add_output(client, strdup(itoa(angle)));
  add_output(client, strdup(" "));
  x = 1;
  while (action->input[x] != NULL)
    {
      add_output(client, strdup(action->input[x]));
      add_output(client, strdup(" "));
      ++x;
    }
  add_output(client, strdup("\n"));
}

void		broadcast_action(t_env *env, t_action *action,
			 int (*table_verite)[2][2][2][2][2])
{
  t_coor	vec;
  size_t	angle;
  int		i;

  i = 0;
  while (i < MAX_FD)
    {
      if (env->clients[i] != FD_FREE
	  && env->clients[i]->role == IA
	  && i != action->client->fd)
	{
	  vec = define_vector(action->client, env->clients[i], &env->map);
	  angle = (*table_verite)[(ABS(vec.y) > ABS(vec.x))]
	    [(ABS(vec.x) > ABS(vec.y))][(ABS(vec.y) == ABS(vec.x))]
	    [(vec.x > 0)][(vec.y > 0)];
	  angle = (vec.y == 0 && vec.x == 0) ?
	    0 : ((angle - ((env->clients[i]->player.dir * 2) + 1)) % 8 + 1);
	  send_msg(env->clients[i], action, angle);
	}
      ++i;
    }
}

void	broadcast(t_env *env, t_action *action)
{
  int	table_verite[2][2][2][2][2];

  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      init_tab_verite(&table_verite);
      pbc(env, action->client, action->input);
      broadcast_action(env, action, &table_verite);
      add_output(action->client, strdup("ok\n"));
      delete_action(action);
    }
}
