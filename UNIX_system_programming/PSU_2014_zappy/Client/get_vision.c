/*
** get_vision.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 11:12:03 2015 Anatole Menichetti
** Last update Wed Jun 24 01:07:34 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Returns the nbr of lines in vision field.
*/
static size_t	get_line_nbr(char *data)
{
  int		i;
  int		line_len;
  int		nbr_line;
  size_t	nbr_squares;

  i = 0;
  nbr_squares = 1;
  line_len = 1;
  nbr_line = 0;
  while (data[i])
    {
      if (data[i] == ',')
	nbr_squares += 1;
      i += 1;
    }
  while (nbr_squares > 0)
    {
      i = 0;
      while (i++ < line_len)
	nbr_squares -= 1;
      nbr_line += 1;
      line_len += 2;
    }
  return (nbr_line);
}

/*
**		Returns the nbr of objs pn the current line & column.
*/
static size_t	get_obj_nbr(char *data)
{
  int		i;
  size_t	cpt;

  i = 0;
  cpt = 0;
  while (data[i] && data[i] != ',')
    {
      if (data[i] == ' ')
	{
	  while (data[i + 1] == ' ')
	    i += 1;
	  cpt += 1;
	}
      i += 1;
    }
  return (cpt);
}

/*
**		Returns the current obj of the current line & column.
*/
static char	get_current_obj(t_player *p, char *data, int const obj_len)
{
  int		i;

  i = 0;
  while (i < 8 && strncmp(data, p->objects[i], obj_len))
    i += 1;
  if (i < 8)
    return (i + 1 + 48);
  return (0 + 48);
}

/*
**		Returns the objs from the current line & column.
*/
static char	*get_current_square_objs(t_player *p, char *square,
					char *data, int *index)
{
  size_t	obj_nbr;
  size_t	cpt;
  int		tmp;
  int		i;

  i = *index;
  cpt = 0;
  obj_nbr = get_obj_nbr(data + i);
  if (!(square = malloc(sizeof(*square) * (obj_nbr + 1))))
    return (NULL);
  while (data[i] && data[i] != ',' && cpt < obj_nbr)
    {
      while (data[i++] == ' ');
      tmp = i - 1;
      while (data[i] && data[i] != ',' && data[i] != '}' && data[i] != ' ')
	i += 1;
      square[cpt] = get_current_obj(p, data + tmp, i - tmp);
      cpt += 1;
    }
  square[cpt] = '\0';
  if (data[i] == ',')
    i += 1;
  *index = i;
  return (square);
}

/*
**		Returns the vision field as char *** (line, column, obj).
*/
char		***get_vision(t_player *p, char *data)
{
  char		***vision;
  int		size;
  int		pos[2];
  int		i;

  i = 1;
  pos[Y] = 0;
  size = get_line_nbr(data);
  if (!(vision = malloc(sizeof(*vision) * (size + 1))))
    return (NULL);
  while (pos[Y] < size)
    {
      pos[X] = -1;
      if (!(vision[pos[Y]] = malloc(sizeof(*vision[pos[Y]]) *
				    (2 * pos[Y] + 2))))
	return (NULL);
      while (++pos[X] < 2 * pos[Y] + 1)
	if (!(vision[pos[Y]][pos[X]] =
	      get_current_square_objs(p, vision[pos[Y]][pos[X]], data, &i)))
	  return (NULL);
      vision[pos[Y]][pos[X]] = NULL;
      pos[Y] += 1;
    }
  vision[pos[Y]] = NULL;
  return (vision);
}
