/*
** regen_food.c for Zappy in /home/toma_i/rendu/PSU_2014_zappy
**
** Created by Ivan Toma
** Login   <@epitech.eu>
**
** Started on  Fri Jul  3 12:29:06 2015 Ivan Toma
** Last update Sun Jul  5 16:04:09 2015 Ivan Toma
*/

#include <unistd.h>
#include <stdlib.h>
#include "header/env.h"
#include "header/graphic.h"

void		regen_food(t_env *env, t_action *action)
{
  size_t	mapx;
  size_t	mapy;

  if (difftime(time(NULL), action->time) >= REGEN_FOOD /env->time)
    {
      mapy = rand() % env->map.height;
      mapx = rand() % env->map.width;
      env->map.map[mapy][mapx][0] =
	(env->map.map[mapy][mapx][0] + rand() % 2) % 20;
      env->map.map[mapy][mapx][1] =
	(env->map.map[mapy][mapx][1] + rand() % 5) % 20;
      env->map.map[mapy][mapx][2] =
	(env->map.map[mapy][mapx][2] + rand() % 5) % 20;
      env->map.map[mapy][mapx][3] =
	(env->map.map[mapy][mapx][3] + rand() % 5) % 20;
      env->map.map[mapy][mapx][4] =
	(env->map.map[mapy][mapx][4] + rand() % 5) % 20;
      env->map.map[mapy][mapx][5] =
	(env->map.map[mapy][mapx][5] + rand() % 5) % 20;
      env->map.map[mapy][mapx][6] =
	(env->map.map[mapy][mapx][6] + rand() % 5) % 20;
      bct(env, mapy, mapx);
      action->time = time(NULL);
    }
}
