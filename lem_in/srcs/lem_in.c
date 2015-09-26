/*
** lem_in.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Apr 20 12:15:03 2014 menich_a
** Last update Sun May  4 20:14:15 2014 menich_a
*/

#include <stdlib.h>
#include "lem_in.h"
#include "my.h"

/*
**		If an ant change way, other ants will wait one turn less.
**		And next ant to take the same new way will wait one more turn.
*/
void		adjust_waits(t_ant *ant, t_way *ways)
{
  t_ant		*tmp;
  t_way		*way;

  tmp = ant->next;
  while (tmp)
    {
      tmp->wait = tmp->wait - 1;
      tmp = tmp->next;
    }
  way = ways;
  while (way && my_tabcmp(way->way, ant->way))
    way = way->next;
  if (way)
    {
      ant->wait = way->wait;
      way->wait = way->wait + 1;
    }
}

/*
**		For each ant, according to it waiting time (in turns) and to the size of
**		it way (in turns) compared to the size and waiting time of each way in list
**			=> ants change way and waits if it need to wait to long.
*/
int		assign_appropriate_ways(t_ant *ants, t_way *ways, t_way *shortest_way)
{
  t_ant		*ant;
  t_way		*way;
  int		check;

  ant = ants;
  while (ant)
    {
      check = 1;
      way = ways;
      while (way && check)
	{
	  if (ant->wait + tab_len(ant->way) > tab_len(way->way) + way->wait)
	    {
	      check = 0;
	      my_free_tab(ant->way);
	      if ((ant->way = my_tab_dup(way->way)) == NULL)
		return (msg_error("lem_in: error: malloc failed.\n"));
	      adjust_waits(ant, ways);
	      shortest_way->wait = shortest_way->wait - 1;
	    }
	  way = way->next;
	}
      ant = ant->next;
    }
  return (0);
}

/*
**		Create a way linked list. When adding a way, it block rooms used by this way
**		=> linked list containing each way possible.
**		Then assign_appropriate_ways according to list, the shortest way, and ants.
*/
int		adjust_ways(t_anthill *hill, unsigned int wait)
{
  t_way		*ptr;
  char		**way;
  int		i;

  hill->ways = NULL;
  while ((way = find_short_way(hill, hill->rooms, 0)))
    {
      i = 0;
      hill->save = NULL;
      while (way[i] && my_str_isprintable(way[i]))
	i = i + 1;
      if (way[i] && !my_free_tab(way))
	break;
      if (add_one_way(&hill->ways, way, hill->rooms))
	return (-1);
      my_free_tab(way);
    }
  if ((ptr = hill->ways) == NULL)
    return (0);
  while (ptr && my_tabcmp(ptr->way, hill->ants->way))
    ptr = ptr->next;
  if (ptr && (ptr->wait = wait) != -1)
    if (assign_appropriate_ways(hill->ants, hill->ways, ptr))
      return (-1);
  return (0);
}

/*
**		Get the shortest way then assign this way to each ant in the hill.
**		If first / last room have only one connection every ants will take this way.
**		Else => adjust_ways
*/
int		assign_way(t_anthill *hill)
{
  char		**way;
  t_ant		*ant;
  t_room	*room;
  unsigned int	wait;

  wait = 0;
  ant = hill->ants;
  room = hill->rooms;
  if ((way = find_short_way(hill, hill->rooms, 0)) == NULL)
    return (msg_error("lem_in: error: cannot reach last room.\n"));
  set_rooms_state(hill->rooms, way);
  hill->save = NULL;
  while (ant)
    {
      if ((ant->way = my_tab_dup(way)) == NULL)
	return (msg_error("lem_in: error: malloc failed.\n"));
      ant->wait = wait++;
      ant = ant->next;
    }
  my_free_tab(way);
  while (room->next)
    room = room->next;
  if (pipes_nbr(hill->rooms->pipes) > 1 && pipes_nbr(room->pipes) > 1)
    return (adjust_ways(hill, wait));
  return (0);
}

/*
**		Main function: it launch the game turn by turn.
**		First creates an ant list then assign a way to each ant in the list.
**		When each ants get its task to perform: launch game.
**		Each turn, if the ant need to wait, it doesn't move and wait = wait - 1
**		Else if the ant isn't to the end and that its doesn't need to wait:
**		=> aff_ants (ant->i++ and display(ant->way[ant->i]))
*/
int		lem_in(t_anthill *hill)
{
  t_ant		*ant;
  t_room	*last_room;

  last_room = hill->rooms;
  while (last_room->next)
    last_room = last_room->next;
  if (init_ant_list(hill) || assign_way(hill))
    return (-1);
  while (hill->ants_nbr)
    {
      ant = hill->ants;
      while (hill->ants_nbr && ant)
	{
	  if (ant->state != ARRIVED)
	    {
	      if (!ant->wait && ant->i++ >= 0)
		hill->ants_nbr = display_ant(ant, last_room->name, hill->ants_nbr);
	      else
		ant->wait--;
	    }
	  ant = ant->next;
	}
    }
  return (0);
}
