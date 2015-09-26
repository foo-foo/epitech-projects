/*
** actions.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 09:16:17 2015 Anatole Menichetti
** Last update Wed Jun 24 01:45:41 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Update the current obj quantity in stuff.
*/
static int	get_next_object(t_player *p, char *obj, int obj_id)
{
  int		i;
  int		tmp;
  char		cpy;

  i = 0;
  while (obj[i] && obj[i] != '}' && obj[i] != ' ')
    i += 1;
  obj[i] = '\0';
  while (obj_id < 7 && strcmp(obj, p->objects[obj_id]))
    obj_id += 1;
  obj[i] = ' ';
  while (obj[i++] == ' ');
  tmp = i - 1;
  while (obj[i] && obj[i] != ',')
    i += 1;
  if (obj_id < 7)
    {
      cpy = obj[i];
      obj[i] = '\0';
      p->stuff[obj_id] = atoi(obj + tmp);
      obj[i] = cpy;
    }
  if (obj[i])
    return (i + 1);
  return (i);
}

/*
**		Update the objects quantity in stuff.
*/
int		stuff(t_player *p, char *data)
{
  int		i;

  i = 1;
  p->need_to_look_stuff = UPDATE_STUFF_TIME;
  if (strlen(data) < 1 || data[0] != '{' ||
      data[strlen(data) - 1] != '}')
    return (1);
  while (data[i] && data[i] != '}')
    i += get_next_object(p, data + i, 0);
  return (1);
}

/*
**		Turn left, update dir & target_dir.
*/
int		turn_left(t_player *p, char *data)
{
  (void)data;
  if (p->target_dir > 0)
    {
      if (p->target_dir <= 2)
	p->target_dir += 6;
      else
	p->target_dir -= 2;
    }
  p->last_move = TURN_LEFT;
  return (1);
}

/*
**		Turn right, update dir & target_dir.
*/
int		turn_right(t_player *p, char *data)
{
  (void)data;
  if (p->target_dir > 0)
    {
      if (p->target_dir > 6)
	p->target_dir -= 6;
      else
	p->target_dir += 2;
    }
  p->last_move = TURN_RIGHT;
  return (1);
}
