/*
** init_anthill.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Apr 20 12:10:24 2014 menich_a
** Last update Sat May  3 18:28:54 2014 menich_a
*/

#include <stdlib.h>
#include "lem_in.h"
#include "my.h"

/*
**		Init pipes (connections) for each room of the linked list.
**		Pipes is a linked list containing next rooms pointers.
*/
int		init_pipes(t_room *rooms, char **settings)
{
  int		i;
  t_room	*ptr;
  char		*p_name;

  i = 0;
  ptr = rooms;
  while (ptr && i++ <= 2000)
    ptr = ptr->next;
  if (i > 2000)
    return (msg_error("lem_in: error: cannot treat so much rooms.\n"));
  ptr = rooms;
  while (ptr)
    {
      i = 0;
      ptr->pipes = NULL;
      while (settings[i])
        {
          p_name = my_str_ispipe(ptr->name, settings[i]);
          if (add_one_pipe(rooms, &ptr->pipes, p_name, settings[i]))
            return (msg_error("lem_in: error: malloc failed.\n"));
          i = i + 1;
        }
      ptr = ptr->next;
    }
  return (0);
}

/*
**		Init a room linked list.
*/
int		init_rooms(t_anthill *hill, char **setings)
{
  int		i;

  i = 0;
  hill->rooms = NULL;
  while (setings[i + 1] && my_strcmp(setings[i], "##end"))
    i = i + 1;
  if (!setings[i + 1] || add_one_room(&hill->rooms, setings[i + 1]))
    return (msg_error("lem_in: invalid datas for last room.\n"));
  i = 0;
  while (setings[i])
    {
      if (!my_strcmp(setings[i], "##start") || !my_strcmp(setings[i], "##end"))
        i = i + 1;
      else
        if (add_one_room(&hill->rooms, setings[i]))
          return (msg_error("lem_in: error: malloc failed.\n"));
      if (setings[i])
        i = i + 1;
    }
  while (i >= 0 && my_strcmp(setings[i], "##start"))
    i = i - 1;
  if (i < 0 || !setings[i + 1] || add_one_room(&hill->rooms, setings[i + 1]))
    return (msg_error("lem_in: invalid datas for first room.\n"));
  return (init_pipes(hill->rooms, setings));
}

/*
**		Get number of ants and init hill->way and hill->save to a NULL value.
**		hill->way and hill->save are used by find_short_way.
*/
int		find_ants_nbr(t_anthill *hill, char **settings)
{
  int		i;
  int		nbr;

  i = 0;
  nbr = -42;
  while (settings[i])
    {
      if (my_str_isnum(settings[i]))
        if ((nbr = my_getnbr(settings[i])) <= 0)
          return (msg_error("lem_in: error: to few ants.\n"));
      i = i + 1;
    }
  if (nbr == -42)
    {
      msg_error("lem_in: ants number unspecified.");
      msg_error(" Launched process with 42 ants (enable by default).\n");
      nbr = 42;
    }
  hill->ants_nbr = nbr;
  hill->way = NULL;
  hill->save = NULL;
  my_free_tab(settings);
  return (0);
}

/*
**		Init the anthill (containing ants and rooms)
**		First, catch anthill settings in a char** then init anthill rooms \
**		and ants nbr.
**		The buff is displayed by get_next_line to be receive by ./visu.
*/
int		init_anthill(t_anthill *hill)
{
  char		*buff;
  char		**settings;
  int		i;

  i = 0;
  if ((settings = malloc(sizeof(*settings) * 2)) == NULL)
    return (msg_error("lem_in: error: malloc failed.\n"));
  while ((buff = get_next_line(0)) && !my_line_isvalid(buff))
    {
      if (!my_strcmp(buff, "##start") || !my_strcmp(buff, "##end") ||
          buff[0] != '#')
        {
          settings[i++] = my_strdup(buff);
          settings[i] = NULL;
          settings = my_realloc(settings);
        }
      free(buff);
      buff = NULL;
    }
  if (buff)
    free(buff);
  if (init_rooms(hill, settings) || find_ants_nbr(hill, settings))
    return (-1);
  return (0);
}
