/*
** put_in_list.c for  in /home/bencha_a/lem-in/v1.6/interface_graphique
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri May  2 19:24:37 2014 bencharif
** Last update Sun May  4 19:20:38 2014 menich_a
*/

#include <stdlib.h>
#include "graph.h"
#include "get_next_line.h"

char		*getcoord(char *line)
{
  int		a;
  char		*tmp;
  static int	i;

  a = 0;
  tmp = malloc(my_strlen(line) * sizeof(char));
  if (tmp == NULL)
    return (NULL);
  while (line[i] && line[i] != ' ')
    tmp[a++] = line[i++];
  tmp[a] = '\0';
  if (line[i] != '\0')
    i++;
  if (line[i] =='\0')
    i = 0;
  return (tmp);
}

int		my_put_in_list(t_coord **begun, char *line, int check)
{
  t_coord	*elem;
  char		*tmp;

  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (0);
  elem->check = check;
  elem->room_name = getcoord(line);
  tmp = getcoord(line);
  elem->x = my_getnbr(tmp);
  free(tmp);
  tmp = getcoord(line);
  elem->y = my_getnbr(tmp);
  free(tmp);
  elem->connection = NULL;
  elem->next = *begun;
  *begun = elem;
  return (0);
}
