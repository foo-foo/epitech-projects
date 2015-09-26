/*
** delete_env.c for delete env in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:38:49 2015 Sebastien Lauret
** Last update Sun Jul  5 15:38:50 2015 Sebastien Lauret
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header/env.h"
#include "header/action.h"
#include "header/fptr_action.h"

void		delete_map(t_env *env)
{
  size_t	y;
  size_t	x;

  y = 0;
  while (env->map.height > y)
    {
      x = 0;
      while (env->map.width > x)
	{
	  free(env->map.map[y][x]);
	  x++;
	}
      free(env->map.map[y]);
      y++;
    }
  free(env->map.map);
}

void	delete_clients(t_env *env)
{
  int	i;

  i = 0;
  while (i < MAX_FD)
    {
      if (env->clients[i] != FD_FREE)
	{
	  close(i);
	  free(env->clients[i]);
	}
      ++i;
    }
  free(env->clients);
}
void		delete_actions(t_env *env, f_action *fptr_action)
{
  t_action	*tmp;
  int		i;

  tmp = env->action.next;
  while (tmp->root != 1)
    {
      tmp = tmp->next;
      delete_action(tmp->prev);
    }
  i = 0;
  while (env->msg_action[i] != NULL)
    {
      free(env->msg_action[i]);
      i++;
    }
  free(env->msg_action);
  free(fptr_action);
}
void	delete_stone(t_env *env)
{
  int	i;

  i = 0;
  while (env->stone_name[i] != NULL)
    {
      free(env->stone_name[i]);
      i++;
    }
  free(env->stone_name);
}

void	delete_env(t_env *env, f_action *fptr_action)
{
  delete_map(env);
  delete_actions(env, fptr_action);
  delete_clients(env);
  delete_stone(env);
  free(env->teams);
  close(env->fd_server);
}
