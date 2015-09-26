/*
** init_env.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:27:52 2015 Younes Iddahamou
** Last update Sun Jul  5 16:00:05 2015 Younes Iddahamou
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header/env.h"
#include "header/action.h"
#include "header/graphic.h"
#include "header/fptr_action.h"
#include "header/fonction.h"

int	init_map_ressource(t_env *env, int y, int x)
{
  int	i;

  if ((env->map.map[y][x] = malloc(sizeof(int) * (JOUEUR + 1))) == NULL)
    return (-1);
  i = 0;
  env->map.map[y][x][i] = rand() % 200;
  while (++i < 7)
    env->map.map[y][x][i] = (((rand() % 10) < 5) ? rand() % 10 : rand() % 5);
  env->map.map[y][x][JOUEUR] = 0;
  return (0);
}

int		init_map(t_env *env)
{
  size_t	y;
  size_t	x;

  y = 0;
  if ((env->map.map = malloc(sizeof(int**) * (env->map.height + 1))) == NULL)
    return (-1);
  while (env->map.height > y)
    {
      x = 0;
      if ((env->map.map[y] = malloc(sizeof(int*) * (env->map.width + 1)))
	  == NULL)
	return (-1);
      while (env->map.width > x)
	{
	  init_map_ressource(env, y, x);
	  ++x;
	}
      ++y;
    }
  return (0);
}

int	init_client(t_env *env)
{
  int i = 0;

  if ((env->clients = malloc(sizeof(t_env*) * (MAX_FD))) == NULL)
    return (-1);
  while (i < MAX_FD)
    {
      env->clients[i] = FD_FREE;
      ++i;
    }
  return (0);
}

int	init_stone_name(t_env *env)
{
  if ((env->stone_name = malloc(sizeof(char *) * 9)) == NULL
      || (env->stone_name[0] = strdup("nourriture")) == NULL
      || (env->stone_name[1] = strdup("linemate")) == NULL
      || (env->stone_name[2] = strdup("deraumere")) == NULL
      || (env->stone_name[3] = strdup("sibur")) == NULL
      || (env->stone_name[4] = strdup("mendiane")) == NULL
      || (env->stone_name[5] = strdup("phiras")) == NULL
      || (env->stone_name[6] = strdup("thystame")) == NULL
      || (env->stone_name[7] = strdup("joueur")) == NULL)
    return (-1);
  env->stone_name[8] = NULL;
  return (0);
}

int	init_env(t_env *env, int fd, f_action  **fptr_action)
{
  srand(time(NULL));
  env->fd_server = fd;
  env->graph_client = NULL;
  if (init_client(env) == -1
      || init_action(env, fptr_action) == -1
      || init_map(env) == -1
      || init_stone_name(env) == -1)
    return (-1);
  return (0);
}
