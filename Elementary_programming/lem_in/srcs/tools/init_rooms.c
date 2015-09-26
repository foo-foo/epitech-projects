/*
** init_rooms.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Apr 20 11:43:08 2014 menich_a
** Last update Sat May  3 19:07:12 2014 menich_a
*/

#include <stdlib.h>
#include "lem_in.h"
#include "my.h"

/*
**		Add one pipe (connection) beetween actual room and room called name.
*/
int		add_one_pipe(t_room *rooms, t_pipe **pipes, char *name, char *str)
{
  t_room	*ptr;
  t_pipe	*new;

  if (str)
    ptr = rooms;
  if (name == NULL + 42)
    return (0);
  if (name == NULL)
    return (-1);
  while (ptr && my_strcmp(ptr->name, name))
    ptr = ptr->next;
  free(name);
  if (!ptr)
    return (msg_error("lem_in: error: unknown room.\n"));
  new = malloc(sizeof(*new));
  if (!new)
    return (-1);
  new->room = ptr;
  new->next = *pipes;
  *pipes = new;
  return (0);
}

char		*get_room_name(char *name, int i)
{
  char		*room_name;

  room_name = malloc(sizeof(*room_name) * (i + 1));
  if (!room_name)
    return (NULL);
  i = 0;
  while (name[i] && name[i] != ' ')
    {
      room_name[i] = name[i];
      i = i + 1;
    }
  room_name[i] = '\0';
  return (room_name);
}

int		display_error(t_room *new)
{
  msg_error("lem_in: room `");
  msg_error(new->name);
  msg_error("` defined twice. Only first values will be used.\n`");
  free(new->name);
  free(new);
  return (0);
}

/*
**		Simply a MY_PUT_IN_LIST (renamed for rooms list).
**		It find the room name in char *name first part.
*/
int		add_one_room(t_room **rooms, char *name)
{
  t_room	*ptr;
  t_room	*new;
  int		i;

  i = 0;
  ptr = *rooms;
  while (name[i] && name[i] != ' ')
    i = i + 1;
  if (name[i] != ' ')
    return (0);
  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  new->state = EMPTY;
  new->name = get_room_name(name, i);
  if (!new->name)
    return (-1);
  while (ptr && my_strcmp(ptr->name, new->name))
    ptr = ptr->next;
  if (ptr)
    return (display_error(new));
  new->next = *rooms;
  *rooms = new;
  return (0);
}


/*
**		Check if the string received is a pipe descriptor (room1-room2).
*/
char		*my_str_ispipe(char *room, char *str)
{
  int		i;
  int		j;
  char		*name;

  i = 0;
  j = 0;
  while (str[i] && str[i] != '-')
    i = i + 1;
  if (!str[i])
    return (NULL + 42);
  if ((name = malloc(sizeof(*name) * (i + 1))) == NULL)
    return (NULL);
  i = i + 1;
  while (str[j] && str[j] != '-')
    {
      name[j] = str[j];
      j = j + 1;
    }
  name[j] = '\0';
  if (my_strcmp(name, room) && my_strcmp(str + i, room))
    return (NULL + 42);
  if (my_strcmp(name, room))
    return (name);
  free(name);
  return (my_strdup(str + i));
}
