/*
** extern_actions.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 09:17:52 2015 Anatole Menichetti
** Last update Wed Jun 24 01:48:28 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**	Unused for now.
**	Update pos according to the expulsion dir.
*/
int	have_been_expulsed(t_player *p, char *data)
{
  int	movement;

  movement = atoi(data + 13);
  if (movement == 2)
    turn_left(p, data);
  if (movement == 3)
    {
      turn_left(p, data);
      turn_left(p, data);
    }
  if (movement == 4)
    turn_right(p, data);
  if (movement == 4)
    turn_left(p, data);
  if (movement == 3)
    {
      turn_left(p, data);
      turn_left(p, data);
    }
  if (movement == 2)
    turn_right(p, data);
  return (1);
}

/*
**	Complete elevation if it successfully finished
**	=> increase lvl, update requirements...
*/
int	elevation_ended(t_player *p, char *data)
{
  int	new_level;

  p->rising = 0;
  new_level = data[strlen(data) - 1] - 48;
  if (new_level > (int)p->lvl)
    {
      p->lvl += 1;
      p->target_pid = 0;
      p->people_needed = p->requirements[p->lvl - 1][0] - 1;
      p->wait_before_broadcast = WAIT_BEFORE_BROADCAST;
      putstr("\033[32mElevation completed\033[0m\n");
    }
  else
    putstr("\033[31mElevation canceled\033[0m\n");
  return (1);
}

/*
**	Used for actions that need to be write but not to be perform.
*/
int	do_nothing(t_player *p, char *data)
{
  (void)p;
  (void)data;
  return (1);
}
