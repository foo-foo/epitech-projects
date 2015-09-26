/*
** actions.c for  in /home/menich_a/rendu/zappy/client_zappy
**
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
**
** Started on  Mon Jun 15 09:16:17 2015 Anatole Menichetti
** Last update Sun Jul  5 16:04:58 2015 Bastos-Fix
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

static int	free_broadcast_resources(char *pid, char *extern_pid, char *lvl)
{
  free(pid);
  free(extern_pid);
  free(lvl);
  return (1);
}

/*
**		Write the broadcast previously prepared (p->broadcast).
*/
static int	broadcast(int const fd, t_player *p, int b[6], int i)
{
  char		*pid;
  char		*extern_pid;
  char		*lvl;

  kick_if_needed(p);
  p->actions[i] = BROADCAST;
  if (!(lvl = malloc(sizeof(*lvl) * 2)) ||
      !(pid = nbr_to_str(b[PID])) || !(extern_pid = nbr_to_str(b[EXTERN_PID])))
    return (0);
  lvl[0] = p->lvl + 48;
  lvl[1] = '\0';
  if (fputstr(fd, "broadcast ") == -1 ||
      (b[TYPE] == NEED_PEOPLE &&
       (fputstr(fd, p->team_name) == -1 || fputstr(fd, " ") == -1 ||
	fputstr(fd, pid) == -1 || fputstr(fd, " ") == -1 ||
	fputstr(fd, lvl) == -1)) ||
      ((b[TYPE] == CAN_I_JOIN || b[TYPE] == U_CAN_JOIN) &&
       (fputstr(fd, extern_pid) == -1 || fputstr(fd, " ") == -1 ||
	fputstr(fd, pid) == -1)) ||
      (b[TYPE] == CALL && fputstr(fd, pid) == -1) ||
      (b[TYPE] == U_CAN_JOIN && fputstr(fd, "!") == -1) ||
      fputstr(fd, "\n") == -1)
    return (0);
  return (free_broadcast_resources(pid, extern_pid, lvl));
}

static int	broadcast_as_possible(t_player *p, int add, int check, int fd)
{
  int		i;
  int		n;

  n = 0;
  while (n < p->nbr_broadcasts)
    {
      i = 10;
      if (p->broadcasts[n][TYPE] == NEED_PEOPLE)
	p->nbr_broadcast_emitted += 1;
      if ((!check || p->broadcasts[n][TYPE] != CAN_I_JOIN) &&
	  (p->nbr_broadcasts == 1 || p->broadcasts[n][TYPE] != NEED_PEOPLE))
	while (--i > 0)
	  {
	    if (p->actions[i - 1] == ELEVATION)
	      return (1);
	    p->actions[i] = p->actions[i - 1];
	  }
      if (i != 9 && (!check || p->broadcasts[n][TYPE] != CAN_I_JOIN) &&
	  (p->nbr_broadcasts == 1 || p->broadcasts[n][TYPE] != NEED_PEOPLE))
	if (!broadcast(fd, p, p->broadcasts[n], i))
	  return (0);
      if (!add || --add == 0)
	n += 1;
    }
  return (1);
}

static int	complete_broadcasts(t_player *p)
{
  int		i;
  int		n;

  i = 0;
  while (i < 9 && p->actions[i] != LOOK && p->actions[i] >= 0)
    i += 1;
  p->actions[i] = LOOK;
  p->need_to_broadcast = 0;
  n = p->nbr_broadcasts;
  p->nbr_broadcasts = 0;
  while (--n > 8)
    prepare_answer(p, p->broadcasts[n][TYPE],
		   p->broadcasts[n][EXTERN_PID], p->broadcasts[n][PID]);
  return (1);
}

/*
**		Check if broadcast if needed. If it is, then broadcast.
*/
int		broadcast_if_needed(int const fd, t_player *p)
{
  int		i;
  int		add;
  int		check;

  i = 0;
  add = 0;
  check = 0;
  if (!p->need_to_broadcast || p->preparing_to_rise == 1)
    return (1);
  if (p->nbr_broadcasts == 1 &&
      p->broadcasts[0][TYPE] == NEED_PEOPLE && p->wait_before_broadcast)
    {
      p->wait_before_broadcast -= 1;
      return (1);
    }
  if (p->nbr_broadcasts == 1 &&
      p->broadcasts[0][TYPE] == CALL && p->stuff[FOOD] >= MIN_FOOD)
    add = p->stuff[FOOD] > MAX_FOOD ? 6 : 3;
  while (i < p->nbr_broadcasts && p->broadcasts[i][TYPE] != U_CAN_JOIN)
    i += 1;
  if (i < p->nbr_broadcasts)
    check = 1;
  broadcast_as_possible(p, add, check, fd);
  return (complete_broadcasts(p));
}
