/*
** init_player.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:03 2015 Anatole Menichetti
** Last update Wed Jun 24 02:27:02 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		First actions done by player.
*/
static int	init_player_actions(int const fd, t_player *p,
				    int const connect_nbr)
{
  int		i;

  i = 0;
  if (!connect_nbr)
    {
      p->actions[i++] = FORK;
      if (fputstr(fd, "fork\n") == -1)
	return (0);
    }
  p->actions[i++] = LOOK;
  if (fputstr(fd, "voir\n") == -1)
    return (0);
  p->actions[i] = -1;
  return (1);
}

/*
**		Elevation requirements that differs from others.
*/
static void	init_special_requirements(size_t requirements[7][7])
{
  requirements[2][LINEMATE] = 2;
  requirements[6][LINEMATE] = 2;
  requirements[1][DERAUMERE] = 1;
  requirements[2][DERAUMERE] = 0;
  requirements[3][DERAUMERE] = 1;
  requirements[3][SIBUR] = 2;
  requirements[5][SIBUR] = 3;
  requirements[6][SIBUR] = 2;
  requirements[4][MENDIANE] = 3;
  requirements[6][MENDIANE] = 2;
  requirements[2][PHIRAS] = 2;
  requirements[3][PHIRAS] = 1;
  requirements[5][PHIRAS] = 1;
  requirements[6][PHIRAS] = 2;
  requirements[6][THYSTAME] = 1;
}

/*
**		Elevation requirements.
*/
static void	init_requirements(size_t requirements[7][7])
{
  int		i;

  i = 0;
  requirements[0][PEOPLE] = 1;
  requirements[1][PEOPLE] = 2;
  requirements[2][PEOPLE] = 2;
  requirements[3][PEOPLE] = 4;
  requirements[4][PEOPLE] = 4;
  requirements[5][PEOPLE] = 6;
  requirements[6][PEOPLE] = 6;
  while (i < 7)
    {
      requirements[i][LINEMATE] = 1;
      requirements[i][DERAUMERE] = 2;
      requirements[i][SIBUR] = 1;
      requirements[i][MENDIANE] = 0;
      requirements[i][PHIRAS] = 0;
      requirements[i][THYSTAME] = 0;
      i +=1 ;
    }
  i = 0;
  while (++i < 7)
    requirements[0][i] = 0;
  init_special_requirements(requirements);
}

/*
**		Stuff, actions, objects names, max_stuff.
*/
static void	init_tabs(t_player *p)
{
  int		i;

  i = 0;
  while (i < 10)
    {
      if (i < 7)
	p->stuff[i] = 0;
      p->actions[i] = -1;
      i += 1;
    }
  p->objects[0] = "nourriture";
  p->objects[1] = "linemate";
  p->objects[2] = "deraumere";
  p->objects[3] = "sibur";
  p->objects[4] = "mendiane";
  p->objects[5] = "phiras";
  p->objects[6] = "thystame";
  p->objects[7] = "joueur";
}

/*
**		Init every attributes of the player.
*/
int		init_player(int const fd, t_player *p,
			    int const connect_nbr)
{
  p->lvl = DEFAULT_LVL;
  p->rising = 0;
  p->target_dir = -1;
  p->target_pid = 0;
  p->look_for_target = 0;
  p->people_needed = 1;
  p->last_move = TURN_LEFT;
  p->look_around = 0;
  p->waiting_answer = 0;
  p->waiting_time = 0;
  p->wait_before_broadcast = 0;
  p->need_to_broadcast = 0;
  p->nbr_broadcasts = 0;
  p->nbr_broadcast_emitted = 0;
  p->preparing_to_rise = 0;
  p->need_to_kick = 0;
  if ((p->pid = getpid()) <= 0)
    return (0);
  init_tabs(p);
  p->need_to_look_stuff = UPDATE_STUFF_TIME;
  init_requirements(p->requirements);
  return (init_player_actions(fd, p, connect_nbr));
}
