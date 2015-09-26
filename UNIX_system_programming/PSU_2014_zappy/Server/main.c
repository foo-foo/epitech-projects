/*
** main.c for serveur in /home/rosain_f/rendu/PSU_2014_myirc/serveur
**
** Made by Francois Rosain
** Login   <rosain_f@epitech.net>
**
** Started on  Tue Apr  7 13:26:44 2015 Francois Rosain
** Last update Sat Jul  4 11:04:11 2015 Bastos-Fix
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include "../Sockets/sockets.h"
#include "header/env.h"
#include "header/fonction.h"

int	g_exit_flag;

void	set_flag(int nb)
{
  (void)nb;
  g_exit_flag = 1;
}

static int		init_server_socket(int fd, int port)
{
  struct sockaddr_in	s_in;

  g_exit_flag = 0;
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      printf("Error : Can\'t perform bind.\n");
      return (-1);
    }
  if (listen(fd, QPORT_LEN) == -1)
    {
      printf("Error : Can\'t perform listen.\n");
      return (-1);
    }
  return (0);
}

void	debug(t_env *env)
{
  int	i;

  i = 0;
  printf("fd_server : %i\nport %i \ntime %i \nmax_nb_team %i \nnb_team %i \n",
	 env->fd_server, env->port, env->time, env->max_nb_team, env->nb_team);
  while (i <  env->nb_team)
    {
      printf("%s %i\n", env->teams[i].name, nb_client(&env->teams[i]));
      ++i;
    }
}

int		main(int ac, char **av)
{
  int		fd;
  t_env		env;
  f_action	*fptr_action;

  if (init_args(ac, av, &env) == -1)
    {
      error_arg();
      return (-1);
    }
  signal(SIGTERM, &set_flag);
  signal(SIGINT, &set_flag);
  if (verif_fd() == -1
      || create_socket(&fd) == -1
      || init_server_socket(fd, env.port) == -1
      || init_env(&env, fd, &fptr_action) == -1
      || server(&env, fptr_action) == -1)
    return (-1);
  printf("Bye Bye\n");
  delete_env(&env, fptr_action);
  return (0);
}
