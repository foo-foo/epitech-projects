/*
** rise.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 17:29:50 2015 Anatole Menichetti
** Last update Wed Jun 24 02:27:52 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Handle requirements before rising (take & put requires stones).
*/
static int	handle_requirements(t_player *p, char *current_square,
				    int requirements[6])
{
  int		i;
  int		n;
  char		obj;

  i = 0;
  n = 0;
  while (n < 9 && current_square[i])
    {
      obj = current_square[i];
      if (obj > 49 && obj < 56 && requirements[obj - 50] > 0)
	requirements[obj - 50]--;
      else
	if (obj != 56)
	  p->actions[n++] = obj;
      i += 1;
    }
  i = -1;
  while (++i < 6 && n < 9)
    while (n < 9 && requirements[i] > 0)
      {
	p->actions[n] = i + 11;
	requirements[i] -= 1;
	n += 1;
      }
  return (n);
}

/*
**		Rise (in team).
*/
void		rise(t_player *p, char *current_square)
{
  int		i;
  int		requirements[6];

  i = 0;
  if (!p->preparing_to_rise)
    {
      p->need_to_broadcast = 1;
      p->preparing_to_rise = 2;
      return ;
    }
  p->preparing_to_rise = 0;
  while (++i < 7)
    requirements[i - 1] = p->requirements[p->lvl - 1][i];
  i = handle_requirements(p, current_square, requirements);
  if (i < 9)
    p->actions[i++] = ELEVATION;
  else
    p->preparing_to_rise = 1;
  p->need_to_broadcast = 0;
  p->actions[i] = LOOK;
}

/*
**		Returns the best action to perform to rise.
*/
int		can_i_rise(t_player *p, char *current_square, int i, int j,
			   size_t nbr_players)
{
  if (p->lvl == 1 || p->stuff[FOOD] < MIN_FOOD ||
      (p->look_for_target == 2 && p->target_dir))
    {
      if (p->look_for_target == 2 && p->target_dir)
	p->look_for_target = 0;
      return (0);
    }
  while (i < 7 && p->stuff[i] >= p->requirements[p->lvl - 1][i])
    i += 1;
  if (i < 7 && !p->target_pid && !p->preparing_to_rise)
    return (0);
  if (p->people_needed && !p->target_pid)
    return (FIND_PEOPLE);
  while (current_square[++j])
    if (current_square[j] == 56)
      nbr_players += 1;
  if (nbr_players == p->requirements[p->lvl - 1][PEOPLE] && !p->target_pid)
    return (1);
  p->preparing_to_rise = 0;
  if (nbr_players > 1 && nbr_players <= p->requirements[p->lvl - 1][PEOPLE] &&
      (!p->people_needed || (p->target_pid && p->target_dir >= 0)))
    return (WAIT_PEOPLE);
  if (i >= 7 && !p->people_needed)
    return (CALL_PEOPLE);
  return (0);
}

/*
**		If someone is here, it's because he's on same square than
**		another player and that he is looking for his rise partners.
*/
int		wait_people(t_player *p)
{
  p->waiting_time += 1;
  p->actions[0] = STUFF;
  p->actions[1] = LOOK;
  if (!p->people_needed)
    prepare_answer(p, CALL, 0, p->pid);
  else
    if (p->waiting_time > WAIT_MAX && p->target_dir)
      p->look_for_target = 1;
  return (0);
}

/*
**		Go to target_dir.
**		If there is someone in the vision field => join him.
*/
int		get_best_way_to_rise(t_player *p, char ***vision)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (vision[0][0][j] && p->stuff[FOOD] < MAX_FOOD)
    {
      if (vision[0][0][j] != '8')
	p->actions[i++] = vision[0][0][j];
      j += 1;
    }
  if (p->target_pid && (p->target_dir == 7 || p->target_dir == 6 ||
			p->target_dir == 5))
    p->actions[i++] = TURN_RIGHT;
  if (p->target_pid && (p->target_dir == 3 || p->target_dir == 4))
    p->actions[i++] = TURN_LEFT;
  if (p->target_pid && p->target_dir == 5)
    p->actions[i++] = TURN_RIGHT;
  if (p->target_pid && p->target_dir)
    p->actions[i++] = MOVE;
  p->actions[i] = LOOK;
  return (0);
}
