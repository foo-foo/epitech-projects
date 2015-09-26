/*
** action.c for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:23:41 2015 Younes Iddahamou
** Last update Sat Jul  4 19:33:21 2015 Bastos-Fix
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "header/action.h"
#include "header/fptr_action.h"

int		create_action(t_action *action, char **input,
		      t_client *client, int id_action)
{
  t_action	*new_action;

  if ((new_action = malloc(sizeof(t_action))) == NULL)
    return (-1);
  action->next->prev = new_action;
  new_action->prev = action;
  new_action->next = action->next;
  action->next = new_action;
  new_action->first = action;
  new_action->root = 0;
  new_action->input = input;
  new_action->client = client;
  new_action->time = time(NULL);
  new_action->action = id_action;
  new_action->id_client = (client != NULL)
    ? client->player.id : 0;
  return (0);
}

void	delete_action(t_action *action)
{
  int	i;

  if (action->root != 1)
    {
      i = 0;
      while (action->input && action->input[i] != NULL)
	{
	  free(action->input[i]);
	  i++;
	}
      free(action->input);
      action->prev->next = action->next;
      action->next->prev = action->prev;
      if (action->client && action->client->role == AUCUN)
	{
	  close(action->client->fd);
	  free(action->client);
	}
      free(action);
    }
}

void	delete_action_by_id(t_action *action, int id)
{
  action = action->next;
  while (action->root != 1)
    {
      action = action->next;
      if (action->prev->id_client == id)
	delete_action(action->prev);
    }
}
