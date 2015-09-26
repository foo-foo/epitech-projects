/*
** graphic7.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
**
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
**
** Started on  Sun Jul  5 15:37:34 2015 Sebastien Lauret
** Last update Sun Jul  5 16:16:07 2015 Bastos-Fix
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	enw(t_env *env, t_client *client, t_client *egg)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("enw "));
      add_output(env->graph_client, strdup(itoa(egg->id_egg)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.y)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	eth(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("eht "));
      add_output(env->graph_client, strdup(itoa(client->id_egg)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	ebo(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("ebo "));
      add_output(env->graph_client, strdup(itoa(client->id_egg)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	edi(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("edi "));
      add_output(env->graph_client, strdup(itoa(client->id_egg)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	sgt(t_env *env)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("sgt "));
      add_output(env->graph_client, strdup(itoa(env->time)));
      add_output(env->graph_client, strdup("\n"));
    }
}
