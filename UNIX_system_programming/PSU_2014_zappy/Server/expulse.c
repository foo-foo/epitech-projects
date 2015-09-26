/*
** expulse.c for zappy in /home/toma_i/rendu/PSU_2014_zappy
**
** Created by Ivan Toma
** Login   <@epitech.eu>
**
** Started on  Mon Jun 22 17:07:40 2015 Ivan Toma
** Last update Sat Jul  4 01:15:48 2015 Bastos-Fix
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/fonction.h"
#include "header/fptr_action.h"
#include "header/graphic.h"

short		getDirectionCase(t_player *target, t_player *shooter)
{
  static short	dir[4][4];

  dir[UP][UP] = DOWN;
  dir[UP][DOWN] = UP;
  dir[UP][LEFT] = LEFT;
  dir[UP][RIGHT] = RIGHT;
  dir[DOWN][UP] = UP;
  dir[DOWN][DOWN] = DOWN;
  dir[DOWN][LEFT] = RIGHT;
  dir[DOWN][RIGHT] = LEFT;
  dir[LEFT][UP] = RIGHT;
  dir[LEFT][DOWN] = LEFT;
  dir[LEFT][LEFT] = DOWN;
  dir[LEFT][RIGHT] = UP;
  dir[RIGHT][UP] = LEFT;
  dir[RIGHT][DOWN] = RIGHT;
  dir[RIGHT][LEFT] = UP;
  dir[RIGHT][RIGHT] = DOWN;
  return (dir[shooter->dir][target->dir]);
}

void		check_direction(t_env *env, t_client *target, t_client *shooter)
{
  static short	tab[4] = {1, 1, -1, -1};
  char		*from;
  size_t	dir_from;

  if ((from = malloc(sizeof(*from) * 18)) == NULL)
    return ;
  memset(from, 0, 16);
  env->map.map[target->player.coor.y][target->player.coor.x][JOUEUR] -= 1;
  if (shooter->player.dir == LEFT || shooter->player.dir == RIGHT)
    target->player.coor.x += tab[shooter->player.dir];
  if (shooter->player.dir == DOWN || shooter->player.dir == UP)
    target->player.coor.y += tab[shooter->player.dir];
  checkPos(&(target->player), &(env->map));
  env->map.map[target->player.coor.y][target->player.coor.x][JOUEUR] += 1;
  dir_from = getDirectionCase(&(target->player), &(shooter->player));
  dir_from = ((dir_from - 1) * 2 + 1) % 8;
  sprintf(from, "deplacement: %i\n", (int) dir_from);
  add_output(target, from);
}

int	check_case(t_client *target, t_client *shooter)
{
  int	x;
  int	y;

  if (target == NULL || target->role != IA
      || target->fd == shooter->fd)
    return (-1);
  x = target->player.coor.x;
  y = target->player.coor.y;
  if (x != shooter->player.coor.x || y != shooter->player.coor.y)
    return (-1);
  return (0);
}

void	expulse(t_env *env, t_action *action)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      pex(env, action->client);
      while (i < QPORT_LEN)
	{
	  if (check_case(env->clients[i], action->client) == 0)
	    {
	      check_direction(env, env->clients[i],
			      action->client);
	      ppo(env, env->clients[i]);
	      ++j;
	    }
	  ++i;
	}
      if (j == 0)
	add_output(action->client, strdup("ko\n"));
      else
	add_output(action->client, strdup("ok\n"));
      delete_action(action);
    }
}
