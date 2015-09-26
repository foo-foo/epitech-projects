/*
** look.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 17:29:50 2015 Anatole Menichetti
** Last update Wed Jun 24 02:29:21 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Prepare for broadcast if it's needed to rise.
*/
static void	prepare_for_broadcast(t_player *p, int can_i_rise)
{
  if (!p->need_to_broadcast)
    {
      if (can_i_rise == FIND_PEOPLE && !p->waiting_answer)
	{
	  p->broadcasts[p->nbr_broadcasts][TYPE] = NEED_PEOPLE;
	  p->broadcasts[p->nbr_broadcasts][PID] = p->pid;
	  p->broadcasts[p->nbr_broadcasts][EXTERN_PID] = 0;
	  p->broadcasts[p->nbr_broadcasts][LVL] = p->lvl;
	  p->need_to_broadcast = 1;
	  if (p->nbr_broadcasts < 9)
	    p->nbr_broadcasts += 1;
	}
      if (can_i_rise == CALL_PEOPLE)
	prepare_answer(p, CALL, 0, p->pid);
    }
}

/*
**		Get the best way to survive and it's actions.
**		If the way priority is weak => turn and look for better way.
*/
static void	get_best_way_actions(t_player *p, t_view *view, int can_i_rise)
{
  int		visited_squares[10][2];
  int		priority;
  int		datas[3];

  datas[0] = 0;
  datas[1] = 0;
  datas[2] = 0;
  init_visited_squares(visited_squares);
  priority = get_best_way_to_survive(view, visited_squares, datas);
  if (priority <= MIN_PRIORITY)
    {
      if (++p->look_around >= 4)
	p->actions[0] = MOVE;
      else
	p->actions[0] = p->last_move;
      p->actions[1] = STUFF;
      p->actions[2] = LOOK;
    }
  else
    {
      p->look_around = 0;
      get_visited_squares_actions(p, view->vision,
				  visited_squares, p->actions);
    }
  prepare_for_broadcast(p, can_i_rise);
}

/*
**		Get the best actions according to can_i_rise.
*/
static void	get_best_actions(t_player *p, t_view *view, int can_i_rise)
{
  if (p->lvl == DEFAULT_LVL && !view->priorities[0][0] &&
      p->stuff[FOOD] >= MIN_FOOD && p->stuff[LINEMATE] > 0)
    {
      p->actions[0] = EXPULSION;
      p->actions[1] = PUT + LINEMATE;
      p->actions[2] = ELEVATION;
      p->actions[3] = STUFF;
      p->actions[4] = LOOK;
    }
  else
    {
      if (can_i_rise == 1)
	rise(p, view->vision[0][0]);
      else if (can_i_rise == WAIT_PEOPLE)
	wait_people(p);
      else if (p->target_pid && p->target_dir >= 0 &&
	       p->stuff[FOOD] >= MIN_FOOD)
	get_best_way_to_rise(p, view->vision);
      else
	get_best_way_actions(p, view, can_i_rise);
    }
  if (can_i_rise != WAIT_PEOPLE)
    p->waiting_time = 0;
  free_tab(view->vision);
  free_int_tab(view->priorities);
}

static int	stagn(t_player *p, char ***vision)
{
  p->actions[0] = STUFF;
  p->actions[1] = LOOK;
  if (vision)
    free_tab(vision);
  return (1);
}

/*
**		Prepare next actions according to vision and rise state.
*/
int		look(t_player *p, char *data)
{
  int		ret;
  int		tmp;
  t_view	view;

  tmp = 0;
  if (p->rising)
    return (stagn(p, NULL));
  if (!(view.vision = get_vision(p, data)))
    return (0);
  ret = can_i_rise(p, view.vision[0][0], 1, -1, 0);
  if (ret != 1 && !p->need_to_look_stuff--)
    return (stagn(p, view.vision));
  if (ret != 1 && (p->stuff[FOOD] < MIN_FOOD ||
		   p->target_pid || !p->people_needed))
    remove_stones(view.vision);
  else
    if (ret != 1 && !remove_stones_excess(p, view.vision))
      return (0);
  if (!p->target_pid && p->people_needed)
    tmp = PLAYER_PRIORITY;
  if (!(view.priorities = get_vision_priorities(view.vision, tmp)))
    return (0);
  get_best_actions(p, &view, ret);
  return (1);
}
