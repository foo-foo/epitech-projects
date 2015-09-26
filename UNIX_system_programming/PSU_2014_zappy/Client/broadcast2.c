/*
** actions.c for  in /home/menich_a/rendu/zappy/client_zappy
**
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
**
** Started on  Mon Jun 15 09:16:17 2015 Anatole Menichetti
** Last update Sun Jul  5 16:06:01 2015 Bastos-Fix
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Prepare a message to kick other players from current group.
**		Used to unit 2 groups.
*/
void	kick_if_needed(t_player *p)
{
  if (p->need_to_kick && p->nbr_broadcasts < 8)
    {
      prepare_answer(p, CAN_I_JOIN, -1, p->pid);
      p->need_to_kick = 0;
    }
}
