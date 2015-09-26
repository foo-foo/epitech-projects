/*
** my_put_in_list.c for j_12 in /home/menich_a/rendu/Piscine-C-Jour_12/ex_01
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct 22 14:01:08 2013 menich_a
** Last update Sun Dec  1 21:31:04 2013 menich_a
*/

#include "my_ls.h"
#include <stdlib.h>

int	my_put_in_list(t_list **list, char *data, int type, char *dir)
{
  t_list	*elem;
  char		*way;

  elem = malloc(sizeof(*elem));
  way = malloc(sizeof(*way) * (my_strlen(data) + my_strlen(dir)));
  if (elem == NULL || way == NULL)
    {
      exit(-1);
    }
  way = my_strdup(dir);
  if (way[my_strlen(way) - 1] != '/')
    way[my_strlen(way)] = '/';
  my_strcat(way, data);
  way[my_strlen(way)] = '\0';
  elem->way = my_strdup(way);
  //  free(way);
  elem->name = my_strdup(data);
  elem->type = type;
  elem->next = *list;
  *list = elem;
  return (0);
}
