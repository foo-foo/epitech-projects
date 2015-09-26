/*
** fptr_action.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:14:33 2015 Younes Iddahamou
** Last update Mon Jun 29 15:07:04 2015 Bastos-Fix
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/action.h"
#include "header/fonction.h"
#include "header/graphic.h"

void	droite(t_env *env, t_action *action)
{
  if (difftime(time(NULL), action->time) >= 7 / env->time)
    {
      action->client->player.dir = (action->client->player.dir - 1) % 4;
      add_output(action->client, strdup("ok\n"));
      ppo(env, action->client);
      delete_action(action);
    }
}
