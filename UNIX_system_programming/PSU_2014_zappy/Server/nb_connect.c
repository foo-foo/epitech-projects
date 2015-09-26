/*
** nb_connect.c for nb_connect in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:36:57 2015 Sebastien Lauret
** Last update Sun Jul  5 15:36:58 2015 Sebastien Lauret
*/

#include <string.h>
#include <unistd.h>
#include "header/env.h"
#include "header/fptr_action.h"

int		free_slot(t_env*env, int team)
{
  int		nb;
  t_client	*tmp;

  nb = env->max_nb_team;
  tmp = env->teams[team].clients.next;
    while (tmp->root != 1)
      {
	if (tmp->role == EGG)
	  nb++;
	else
	  --nb;
	tmp = tmp->next;
      }
    return (nb);
}

void	nb_connect(t_env*env, t_action *action)
{
  add_output(action->client,
	     strdup(itoa(free_slot(env, action->client->team))));
  add_output(action->client, strdup("\n"));
  delete_action(action);
}
