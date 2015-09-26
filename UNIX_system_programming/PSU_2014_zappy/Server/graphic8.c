/*
** graphic8.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:39:20 2015 Sebastien Lauret
** Last update Sun Jul  5 15:39:21 2015 Sebastien Lauret
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"
void	fptr_sgt(t_env *env, t_action *action)
{
  sgt(env);
  delete_action(action);
}

void	sst(t_env *env, int new_time)
{
  if (env->graph_client != NULL)
    {
      if (new_time > 0)
	env->time = new_time;
      sgt(env);
    }
}

void	fptr_sst(t_env *env, t_action *action)
{
  int	time;
  char	*err;

  err = NULL;
  if (action->input[1] == NULL)
    sbp(env);
  else
    {
      time = strtol(action->input[1], &err, 10);
      if (err[0] != '\0')
	sbp(env);
      else
	sst(env, time);
    }
  delete_action(action);
}

void	seg(t_env *env, int team)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("sgt "));
      add_output(env->graph_client, strdup(env->teams[team].name));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	smg(t_env *env, char *msg)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("smg "));
      add_output(env->graph_client, strdup(msg));
      add_output(env->graph_client, strdup("\n"));
    }
}
