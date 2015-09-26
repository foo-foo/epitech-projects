/*
** server.c for server.c in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:36:42 2015 Sebastien Lauret
** Last update Sun Jul  5 15:40:06 2015 Sebastien Lauret
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include "../Sockets/sockets.h"
#include "header/env.h"
#include "header/fptr_action.h"
#include "header/action.h"
#include "header/fonction.h"
#include "header/graphic.h"

extern int	g_exit_flag;

static void	set_fd_graph(int *fd_max, t_env *env,
			     fd_set *readfds, fd_set *writefds)
{
  if (env->graph_client)
    {
      *fd_max = (*fd_max > env->graph_client->fd)? *fd_max
	: env->graph_client->fd;
      FD_SET(env->graph_client->fd, readfds);
      FD_SET(env->graph_client->fd, writefds);
    }
}

static void	set_default_fd(fd_set *readfds, fd_set *writefds)
{
  FD_SET(0, readfds);
  FD_SET(0, writefds);
  FD_SET(1, readfds);
  FD_SET(1, writefds);
  FD_SET(2, readfds);
  FD_SET(2, writefds);
}
static void	set_fd_max(int *fd_max, t_env *env,
			   fd_set *readfds, fd_set *writefds)
{
  int		i;
  t_client	*client;

  i = 0;
  set_default_fd(readfds, writefds);
  *fd_max = env->fd_server;
  FD_SET(env->fd_server, readfds);
  FD_SET(env->fd_server, writefds);
  while (env->nb_team >= i)
    {
      client = env->teams[i].clients.next;
      while (!client->root)
	{
	  if (client->role != EGG)
	    {
	      *fd_max = (*fd_max > client->fd)? *fd_max : client->fd;
	      FD_SET(client->fd, readfds);
	      FD_SET(client->fd, writefds);
	    }
	  client = client->next;
	}
      i++;
    }
  set_fd_graph(fd_max, env, readfds, writefds);
}

int		check_end(t_env *env)
{
  int		nb;
  int		team;
  t_client	*client;

  team = 0;
  while (team < env->nb_team)
    {
      nb = 0;
      client = env->teams[team].clients.next;
      while (client->root != 1)
	{
	  if (client->player.lvl == 8)
	    ++nb;
	  if (nb >= 6)
	    {
	      printf("l'equipe gagnante est l'equipe n° %i : %s \n", team,
		     env->teams[team].name);
	      seg(env, team);
	      return (1);
	    }
	  client = client->next;
	}
      ++team;
    }
  return (0);
}

int		server(t_env *env, f_action *fptr_action)
{
  fd_set	readfds;
  fd_set	writefds;
  int		fd_max;
  t_action	*tmp, *tmp2;

  create_action(&env->action, NULL, NULL, REGENE);
  while (!g_exit_flag && !check_end(env))
    {
      FD_ZERO(&readfds);
      FD_ZERO(&writefds);
      set_fd_max(&fd_max, env, &readfds, &writefds);
      if (select(fd_max + 1, &readfds, &writefds, NULL, NULL) == -1)
        return (-1);
      check_fd(&readfds, &writefds, env);
      tmp = env->action.next;
      while (tmp->root != 1)
	{
	  tmp2 = tmp->next;
	  fptr_action[tmp->action](env, tmp);
	  tmp = tmp2;
	}
    }
  return (0);
}
