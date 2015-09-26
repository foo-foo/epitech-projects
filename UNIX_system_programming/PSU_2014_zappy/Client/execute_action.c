/*
** actions.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 09:16:17 2015 Anatole Menichetti
** Last update Wed Jun 24 02:36:54 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

static const t_action	g_actions[] =
  {
    {"voir", {"{ ", ""}, &look},
    {"inventaire", {"{nourriture ", ""}, &stuff},
    {"avance", {"ok", "ko"}, &do_nothing},
    {"gauche", {"ok", "ko"}, &turn_left},
    {"droite", {"ok", "ko"}, &turn_right},
    {"fork", {"", ""}, &do_nothing},
    {"incantation", {"", ""}, &do_nothing},
    {"expulsion", {"", ""}, &do_nothing},
    {"broadcast", {"", ""}, &do_nothing}
  };

/*
**		If asked to elevate:
**		Then check if it successfully begun.
*/
int		check_elevation(t_player *p, char *data)
{
  if (p->actions[0] == ELEVATION)
    {
      if (strcmp(data, "elevation en cours"))
	{
	  p->rising = 0;
	  fputstr(2, "\033[31mElevation failed!!\033[0m\n");
	}
      else
	{
	  p->rising = 1;
	  putstr("\033[32mElevation begun!!\033[0m\n");
	}
      return (1);
    }
  if (p->rising && !strcmp(data, "ko"))
    {
      p->rising = 0;
      fputstr(2, "\033[31mElevation failed!!\033[0m\n");
      return (0);
    }
  return (1);
}

/*
**		Write the previously prepared actions to the server.
*/
static int	write_actions(t_player *p, int const fd, int i)
{
  char		*part1;
  char		*part2;

  while (++i < 10 && p->actions[i] >= 0)
    {
      if (i == 9 && p->actions[i] != LOOK)
	p->actions[i] = LOOK;
      if (i < 9 &&  p->actions[i + 1] < 0 && p->actions[i] != LOOK)
	p->actions[i + 1] = LOOK;
      part1 = p->actions[i] > PUT + NBR_OBJS ? "prend " : "pose ";
      part2 = NULL;
      if (p->actions[i] > PUT + NBR_OBJS)
	part2 = p->objects[p->actions[i] - 49];
      else if (p->actions[i] < NBR_WR_ACTIONS)
	part1 = g_actions[p->actions[i]].name;
      else
	part2 = p->objects[p->actions[i] - 10];
      if (p->actions[i] != BROADCAST &&
	  (fputstr(fd, part1) == -1 || (part2 && fputstr(fd, part2) == -1) ||
	   fputstr(fd, "\n") == -1))
	return (EXIT_FAILURE);
      if (p->actions[i] == LOOK && i < 9)
	p->actions[i + 1] = -1;
    }
  return (1);
}

static int	process_action(t_player *p, char *data, t_action action)
{
  if (!strncmp(data, action.ret[0], 1) ||
      (action.ret[1][0] && !strncmp(data, action.ret[1], 1)))
    return (action.fptr(p, data));
  return (1);
}

/*
**		Execute the last action according the server ret.
**		If action is look => prepare next actions.
**		Look is every time last of the queue.
*/
int		execute_action(int const fd, t_player *p, char *data)
{
  int		i;
  int		action_id;

  i = 0;
  if (!check_elevation(p, data))
    return (1);
  while (p->actions[i] >= 0)
    i += 1;
  if (i > 0)
    {
      i = -1;
      action_id = p->actions[0];
      while (++i < 9 && p->actions[i + 1] >= 0)
	p->actions[i] = p->actions[i + 1];
      p->actions[i] = -1;
      if ((action_id < NBR_ACTIONS &&
	   (!process_action(p, data, g_actions[action_id]) ||
	    (!i && !broadcast_if_needed(fd, p)))) ||
	  write_actions(p, fd, i - 1) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  return (1);
}
