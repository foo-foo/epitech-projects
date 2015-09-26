/*
** find_short_way.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Apr 26 18:35:04 2014 menich_a
** Last update Sat May  3 18:23:55 2014 menich_a
*/

#include <stdlib.h>
#include "lem_in.h"
#include "my.h"

/*
**		Add the room called room_name to the temporary way
*/
char		**build_way(t_anthill *hill, char *room_name)
{
  int		i;

  i = 0;
  if (!hill->way)
    {
      if ((hill->way = malloc(sizeof(*hill->way) * 2)) == NULL)
	exit(msg_error("lem_in: error: malloc failed.\n"));
      hill->way[0] = NULL;
    }
  else
    if ((hill->way = my_realloc(hill->way)) == NULL)
      exit(msg_error("lem_in: error: malloc failed.\n"));
  while (hill->way[i])
    i = i + 1;
  hill->way[i] = room_name;
  hill->way[i + 1] = NULL;
  return (hill->way);
}

/*
**		Remove the last room of the temporary way because:
**		find_short_way goes to previous room and temporary way needs to follow.
*/
char		**backtrack_way(t_anthill *hill)
{
  char		**new_way;
  int		i;

  i = 0;
  if (hill->way)
    {
      while (hill->way && hill->way[i])
	i = i + 1;
      if (i < 2)
	{
	  hill->way = my_free_tab(hill->way);
	  return (hill->save);
	}
      if ((new_way = malloc(sizeof(*new_way) * i)) == NULL)
	exit(msg_error("lem_in: error: malloc failed.\n"));
      i = i - 1;
      new_way[i] = NULL;
      while (--i >= 0)
	new_way[i] = hill->way[i];
      free(hill->way);
      hill->way = new_way;
    }
  return (hill->save);
}

/*
**		Save the temporary way in hill->save.
*/
char		**save_way(t_anthill *hill)
{
  my_free_tab(hill->save);
  hill->save = my_tab_dup(hill->way);
  if (!hill->save)
    exit(msg_error("lem_in: error: malloc failed.\n"));
  return (backtrack_way(hill));
}

int		check_next_room_way(t_anthill *hill, t_room *room, int n)
{
  t_pipe	*pipe;

  pipe = room->pipes;
  while (pipe && n > 0)
    {
      pipe = pipe->next;
      n = n - 1;
    }
  if (!pipe)
    return (0);
  find_short_way(hill, pipe->room, 0);
  pipe = pipe->room->pipes;
  while (pipe && pipe->room->next)
    pipe = pipe->next;
  if (pipe)
    return (0);
  return (1);
}

/*
**		Recursive function to find the shortest way.
**		It check the way of the n-ième pipe (intersection) of room
**		If it find a way shorter than the saved one => save way => backtrack way
**		If the way is useless => backtrack way
**		Backtrack way = go to previous room
**		If the way is usefull => build way (add this room to way)
*/
char		**find_short_way(t_anthill *hill, t_room *room, int n)
{
  t_pipe	*pipe;
  int		i;

  i = 0;
  while (hill->way && hill->way[i] && my_strcmp(hill->way[i], room->name))
    i = i + 1;
  if ((hill->way && hill->way[i]) || room->state == OCCUPED || !room->pipes)
    return (hill->save);
  build_way(hill, room->name);
  if (tab_len(hill->way) >= tab_len(hill->save) && hill->save)
    return (backtrack_way(hill));
  pipe = room->pipes;
  while (pipe && pipe->room->next)
    pipe = pipe->next;
  if (pipe)
    return (save_way(hill));
  while (check_next_room_way(hill, room, n))
    n = n + 1;
  return (backtrack_way(hill));
}
