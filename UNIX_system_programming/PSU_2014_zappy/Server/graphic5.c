/*
** graphic5.c for graphic in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:37:41 2015 Sebastien Lauret
** Last update Sun Jul  5 15:37:44 2015 Sebastien Lauret
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/fptr_action.h"
#include "header/graphic.h"
#include "header/env.h"

void	pin(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      pin_msg(env, client);
    }
}

void	pex(t_env *env, t_client *client)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pex "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      add_output(env->graph_client, strdup("\n"));
    }
}

void	pbc(t_env *env, t_client *client, char **input)
{
  int	i;

  if (env->graph_client != NULL)
    {
      i = 1;
      add_output(env->graph_client, strdup("pbc "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      while (input[i] != NULL)
	{
	  add_output(env->graph_client, strdup(" "));
	  add_output(env->graph_client, strdup(input[i]));
	  ++i;
	}
      add_output(env->graph_client, strdup("\n"));
    }
}

void	pic(t_env *env, t_client *client)
{
  int	i;

  if (env->graph_client != NULL)
    {
      i = 0;
      add_output(env->graph_client, strdup("pic "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.y)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.id)));
      while (i < MAX_FD)
	{
	  if (env->clients[i] && env->clients[i]->player.id != client->player.id
	      && client->player.coor.y == env->clients[i]->player.coor.y
	      && client->player.coor.x == env->clients[i]->player.coor.x)
	    {
	      add_output(env->graph_client, strdup(" "));
	      add_output(env->graph_client,
			 strdup(itoa(env->clients[i]->player.id)));
	    }
	  ++i;
	}
      add_output(env->graph_client, strdup("\n"));
    }
}

void	pie(t_env *env, t_client *client, int res)
{
  if (env->graph_client != NULL)
    {
      add_output(env->graph_client, strdup("pie "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.x)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(client->player.coor.y)));
      add_output(env->graph_client, strdup(" "));
      add_output(env->graph_client, strdup(itoa(res)));
      add_output(env->graph_client, strdup("\n"));
    }
}
