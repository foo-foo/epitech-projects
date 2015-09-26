/*
** incantation_send.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 25 12:56:00 2015 Younes Iddahamou
** Last update Sat Jul  4 13:35:15 2015 Bastos-Fix
*/

#include "header/func.h"
#include "header/fonction.h"

void	send_graph_check(t_env *env, t_client **clients, t_client *caster)
{
  char	*str;
  int	x;
  int	y;
  int	lvl;
  int	i;

  i = -1;
  x = caster->player.coor.x;
  y = caster->player.coor.y;
  lvl = caster->player.lvl;
  asprintf(&str, "pic %d %d %d %d", x, y, lvl, caster->player.id);
  add_output(env->graph_client, str);
  while (++i < QPORT_LEN)
    {
      if (clients[i] != NULL
	  && clients[i]->player.coor.x == caster->player.coor.x
	  && clients[i]->player.coor.y == caster->player.coor.y
	  && clients[i]->player.lvl == caster->player.lvl
	  && clients[i]->player.id != caster->player.id)
	{
	  asprintf(&str, " %d", clients[i]->player.id);
	  add_output(env->graph_client, str);
	}
    }
  add_output(env->graph_client, strdup("\n"));
}

void	send_graph_incant(t_env *env, t_client *caster, int fail,
			  t_map *map)
{
  char	*str;
  int	x;
  int	y;
  int	i;

  i = -1;
  x = caster->player.coor.x;
  y = caster->player.coor.y;
  asprintf(&str, "pie %d %d %d\n", x, y, fail);
  add_output(env->graph_client, str);
  while (++i < QPORT_LEN && fail != 0)
    {
      if (env->clients[i] != NULL
	  && env->clients[i]->player.coor.x == caster->player.coor.x
	  && env->clients[i]->player.coor.y == caster->player.coor.y
	  && env->clients[i]->player.lvl == caster->player.lvl)
	{
	  asprintf(&str, "plv %d %d\n", caster->player.id, caster->player.lvl);
	  add_output(env->graph_client, str);
	}
    }
  asprintf(&str, "bct %d %d %d %d %d %d %d %d %d\n", x, y, map->map[y][x][0],
	   map->map[y][x][1], map->map[y][x][2], map->map[y][x][3],
	   map->map[y][x][4], map->map[y][x][5], map->map[y][x][6]);
  add_output(env->graph_client, str);
}

void	add_output_incantation(t_client **clients, t_client *caster, char *str)
{
  int	i;

  i = -1;
  while (++i < QPORT_LEN)
    {
      if (clients[i] != NULL
	  && clients[i]->player.coor.x == caster->player.coor.x
	  && clients[i]->player.coor.y == caster->player.coor.y
	  && clients[i]->player.lvl == caster->player.lvl)
	add_output(clients[i], strdup(str));
    }
  free(str);
}
