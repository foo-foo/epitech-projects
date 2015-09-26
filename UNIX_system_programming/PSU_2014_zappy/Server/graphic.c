/*
** graphic.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:37:26 2015 Sebastien Lauret
** Last update Sun Jul  5 15:37:28 2015 Sebastien Lauret
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	suc(t_env *env)
{
  if (env->graph_client != NULL)
    add_output(env->graph_client, strdup("suc\n"));

}

void	sbp(t_env *env)
{
  if (env->graph_client != NULL)
    add_output(env->graph_client, strdup("sbp\n"));
}

void	msz(t_env *env)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("msz "));
      add_output(env->graph_client, strdup(itoa(env->map.width)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.height)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	fptr_msz(t_env *env, t_action *action)
{
  msz(env);
  delete_action(action);
}

void	bct(t_env *env, int y, int x)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("bct "));
      add_output(env->graph_client, strdup(itoa(x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(y)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][0])));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][1])));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][2])));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][3])));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][4])));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][5])));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(env->map.map[y][x][6])));
      add_output(env->graph_client, strdup("\n"));
    }
}
