/*
** death.c for zappy in /home/toma_i/rendu/PSU_2014_zappy
**
** Created by Ivan Toma
** Login   <@epitech.eu>
**
** Started on  Tue Jun 23 15:53:20 2015 Ivan Toma
** Last update Sat Jul  4 12:14:42 2015 Bastos-Fix
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "header/fptr_action.h"
#include "header/graphic.h"

void	delete_player(t_env *env, t_action *action)
{
  int	fd;

  (void)env;
  fd = action->client->fd;
  action->client->prev->next = action->client->next;
  action->client->next->prev = action->client->prev;
  close(fd);
  free(action->client);
  action->client = NULL;
  env->clients[fd] = FD_FREE;
  delete_action_by_id(action->first, action->id_client);
}

void	player_death(t_env *env, t_action *action)
{
   if (difftime(time(NULL), action->time) >= (126 / env->time)
       && action->client->player.inventaire[0] > 0)
    {
      action->client->player.inventaire[0] -= 1;
      action->time = time(NULL);
    }
   if (action->client->player.inventaire[0] <= 0)
     {
       if (action->client->role == EGG
	   && action->client->player.inventaire[0] == 0)
	 {
	   action->client->player.inventaire[0] -= 1;
	   edi(env, action->client);
	 }
       else if (action->client->role == IA)
	 {
	   add_output(action->client, strdup("mort\n"));
	   pdi(env, action->client);
	   env->map.map[action->client->player.coor.y]
	     [action->client->player.coor.x][JOUEUR] -= 1;
	   create_action(&env->action, NULL, action->client, DELETE_PLAYER);
	   delete_action(action);
	 }
     }
}
