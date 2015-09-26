/*
** graphic6.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:39:12 2015 Sebastien Lauret
** Last update Sun Jul  5 15:39:15 2015 Sebastien Lauret
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	pfk(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pfk "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	pdr(t_env *env, t_client *client, int id_ressource)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pdr "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(id_ressource)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	pgt(t_env *env, t_client *client, int id_ressource)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pgt "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(id_ressource)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	pdi(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pdi "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	enw_init(t_env *env, t_client *egg)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("enw "));
      add_output(env->graph_client, strdup(itoa(egg->id_egg)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(egg->egg)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(egg->player.coor.x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(egg->player.coor.y)));
      add_output(env->graph_client, strdup("\n"));
    }
}
