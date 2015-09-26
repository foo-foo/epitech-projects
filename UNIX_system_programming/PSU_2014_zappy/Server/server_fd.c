/*
** server_fd.c for server fd in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:36:24 2015 Sebastien Lauret
** Last update Sun Jul  5 15:36:25 2015 Sebastien Lauret
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

int			add_client(t_env *env)
{
  struct sockaddr_in	client_s_in;
  socklen_t		s_in_size;
  int			fd_client;

  s_in_size = sizeof(client_s_in);
  if ((fd_client = accept(env->fd_server, (struct sockaddr *)&client_s_in,
  			  &s_in_size)) == -1)
   {
      printf("Error : 1 Can\'t perform connect.\n");
      return (-1);
    }
  if ((env->clients[fd_client] = alloc_client(env, strdup("BIENVENUE\n")))
      == NULL)
    return (-1);
  env->clients[fd_client]->fd = fd_client;
  return (0);
}

int	find_action(t_env *env, char *input, int role)
{
  int	i;

  i = 0;
  while (i <= 12 && role == IA)
    {
      if (strcmp(env->msg_action[i], input) == 0)
	return (i);
      ++i;
    }
  i = 13;
  while (env->msg_action[i] != NULL && role == GRAPHIQUE)
    {
      if (strcmp(env->msg_action[i], input) == 0)
	return (i);
      ++i;
    }
  if (strcmp("GRAPHIC", input) == 0 && role == AUCUN)
    return (INIT_GRAPH);
  i = -1;
  while (++i < env->nb_team && role == AUCUN)
    if (strcmp(input, env->teams[i].name) == 0)
      return (INIT_PLAY);
  return (-1);
}

int	delete_client_without_role(t_env *env, int id_action, int role,
				   int fd_client)
{
  if (id_action == -1 && role == AUCUN)
    {
      env->clients[fd_client]->prev->next = env->clients[fd_client]->next;
      env->clients[fd_client]->next->prev = env->clients[fd_client]->prev;
      close(fd_client);
      free(env->clients[fd_client]);
      env->clients[fd_client] = FD_FREE;
    }
  return (0);
}

int	server_interpreter(char **input_tab, int fd_client,
				   t_env *env)
{
  int	id_action;
  int	role;

  if (env->clients[fd_client] != NULL)
    {
      role = env->clients[fd_client]->role;
      if ((id_action = find_action(env, input_tab[0], role)) != -1)
	{
	  if (create_action(&env->action, input_tab,
			    env->clients[fd_client], id_action) == -1)
	    return (-1);
	}
      else
	if (role == GRAPHIQUE)
	  suc(env);
	else
	  add_output(env->clients[fd_client], strdup("ko\n"));
      delete_client_without_role(env, id_action, role, fd_client);
    }
  return (0);
}

int	server_reader(fd_set *writefds,
			      int fd_client, t_env *env)
{
  char	*input;

  if (!(input = get_next_line(fd_client)))
    {
      remove_cli(env, fd_client);
      FD_CLR(fd_client, writefds);
      return (-1);
    }
  if (strlen(input) > 1 && check_space(input))
    {
      input[strlen(input) - 1] = 0;
      server_interpreter(str_to_wordtab(input), fd_client, env);
    }
  free(input);
  return (0);
}
