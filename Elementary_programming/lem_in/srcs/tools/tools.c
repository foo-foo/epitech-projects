/*
** tools.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Apr 25 12:16:48 2014 menich_a
** Last update Sat May  3 19:15:09 2014 menich_a
*/

#include <stdlib.h>
#include "lem_in.h"
#include "my.h"

/*
**		Same as my_list_size for pipes linked list.
*/
int		pipes_nbr(t_pipe *pipes)
{
  int		i;
  t_pipe	*pipe;

  i = 0;
  pipe = pipes;
  while (pipe)
    {
      pipe = pipe->next;
      i++;
    }
  return (i);
}

/*
**		Set state to OCCUPED for each room which correspond to an occuped_rooms.
**		find short way cannot acces to rooms which are OCCUPED.
*/
void		set_rooms_state(t_room *first_room, char **occuped_rooms)
{
  int		i;
  t_room	*room;

  room = first_room->next;
  while (room)
    {
      i = 0;
      while (occuped_rooms[i] && my_strcmp(room->name, occuped_rooms[i]))
        i = i + 1;
      if (occuped_rooms[i])
        room->state = OCCUPED;
      room = room->next;
    }
}

/*
**		Same as my_put_in_list but for ways linked list.
**		It add the first room name to first way case.
*/
int		add_one_way(t_way **ways, char **way, t_room *first_room)
{
  t_way		*new;
  int		i;

  i = 0;
  if ((new = malloc(sizeof(*new))) == NULL)
    return (msg_error("lem_in: error: malloc failed.\n"));
  while (way[i])
    i = i + 1;
  if ((new->way = malloc(sizeof(*new->way) * (i + 2))) == NULL)
    return (msg_error("lem_in: error: malloc failed.\n"));
  if ((new->way[0] = my_strdup(first_room->name)) == NULL)
    return (msg_error("lem_in: error: malloc failed.\n"));
  i = 1;
  while (way[i - 1])
    {
      if ((new->way[i] = my_strdup(way[i - 1])) == NULL)
	return (msg_error("lem_in: error: malloc failed.\n"));
      i = i + 1;
    }
  new->way[i] = NULL;
  set_rooms_state(first_room, new->way);
  new->wait = 0;
  new->next = *ways;
  *ways = new;
  return (0);
}
