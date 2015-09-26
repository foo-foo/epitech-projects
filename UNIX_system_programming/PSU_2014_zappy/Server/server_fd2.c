/*
** server_fd2.c for server fd in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:39:55 2015 Sebastien Lauret
** Last update Sun Jul  5 15:39:56 2015 Sebastien Lauret
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "header/env.h"
#include "header/fonction.h"
#include "header/action.h"
#include "header/graphic.h"

int	check_fd_garphic(fd_set *readfds, fd_set *writefds,
				 t_env *env)
{
  if (env->graph_client != NULL)
    {
      if (FD_ISSET(env->graph_client->fd, readfds))
	server_reader(writefds, env->graph_client->fd, env);
      if (env->graph_client && FD_ISSET(env->graph_client->fd, writefds))
	{
	  if (env->graph_client->output != NULL)
	    {
	      if (write(env->graph_client->fd, env->graph_client->output,
			strlen(env->graph_client->output)) == -1)
		return (-1);
	      free(env->graph_client->output);
	      env->graph_client->output = NULL;
	    }
	}
    }
  return (0);
}

int		check_fd(fd_set *readfds, fd_set *writefds, t_env *env)
{
  int		i;
  t_client	*client;
  t_client	*tmp;

  i = 0;
  if (FD_ISSET(env->fd_server, readfds))
    add_client(env);
  while (i <= env->nb_team)
    {
      client = env->teams[i].clients.next;
      while (client->root != 1)
	{
	  tmp = client->next;
	  check_fd_player(readfds, writefds, env, client);
	  client = tmp;
	}
      i++;
    }
  check_fd_garphic(readfds, writefds, env);
  return (0);
}

int	check_fd_player(fd_set *readfds, fd_set *writefds,
				t_env *env, t_client *client)
{
  int	fd;

  fd = client->fd;
  if (FD_ISSET(fd, readfds))
    server_reader(writefds, fd, env);
  if (env->clients[fd] && FD_ISSET(fd, writefds))
    {
      if (client->output != NULL)
	{
	  if (write(client->fd, client->output, strlen(client->output)) == -1)
	    return (-1);
	  free(client->output);
	  client->output = NULL;
	}
    }
  return (0);
}

void	remove_cli(t_env *env, int fd_client)
{
  int	x;
  int	y;

  if (env->clients[fd_client]->role != GRAPHIQUE)
    {
      env->clients[fd_client]->prev->next = env->clients[fd_client]->next;
      env->clients[fd_client]->next->prev = env->clients[fd_client]->prev;
      x = env->clients[fd_client]->player.coor.x;
      y = env->clients[fd_client]->player.coor.y;
      if (env->clients[fd_client]->role == IA)
	env->map.map[y][x][JOUEUR] -= 1;
      delete_action_by_id(&env->action, env->clients[fd_client]->player.id);
    }
  else
    env->graph_client = NULL;
  close(fd_client);
  pdi(env, env->clients[fd_client]);
  free(env->clients[fd_client]);
  env->clients[fd_client] = FD_FREE;
}

int	check_space(char *input)
{
  int	i;

  i = 0;
  while (input[i] != '\0' && input[i] != '\n')
    {
      if (input[i] != '\t' && input[i] != ' ')
        return (1);
      ++i;
    }
  return (0);
}
