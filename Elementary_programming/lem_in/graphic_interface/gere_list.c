/*
** gere_list.c for gere_list.c in /home/benoit_l/rendu/lem-in/v3.0/interface_graphique
** 
** Made by Benoit Leo
** Login   <benoit_l@epitech.net>
** 
** Started on  Sun May  4 16:00:40 2014 Benoit Leo
** Last update Sun May  4 19:44:59 2014 menich_a
*/

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int		my_put_ant_list(t_ant **list, int ant_nbr, int x, int y)
{
  t_ant		*elem;

  elem = malloc(sizeof(*elem));
  if (!elem)
    return (-1);
  elem->old_x = x;
  elem->old_y = y;
  elem->new_x = x;
  elem->new_y = y;
  elem->moving = 0;
  elem->nbr = ant_nbr;
  elem->next = *list;
  *list = elem;
  return (0);
}

t_ant		*create_ants_list(int ants_nbr, t_coord *rooms)
{
  t_coord	*ptr;
  t_ant		*list;

  list = NULL;
  ptr = rooms;
  while (ptr && ptr->check != 1)
    ptr = ptr->next;
  if (ptr == NULL)
    return (NULL);
  while (ants_nbr > 0)
    {
      my_put_ant_list(&list, ants_nbr, ptr->x, ptr->y);
      ants_nbr = ants_nbr - 1;
    }
  return (list);
}

int		adjust_list_process(t_ant *ptr, t_coord *rooms, char *turn, int i)
{
  int		j;
  t_coord	*ptr2;
  char		*tmp;

  j = i;
  while (turn[i] && turn[i] != ' ')
    i = i + 1;
  tmp = strndup(turn + j, i - j);
  ptr2 = rooms;
  while (ptr2 && strcmp(ptr2->room_name, tmp))
    ptr2 = ptr2->next;
  if (!ptr2)
    return (-1);
  ptr->old_x = ptr->new_x;
  ptr->old_y = ptr->new_y;
  ptr->new_x = ptr2->x;
  ptr->new_y = ptr2->y;
  ptr->moving = 1;
  free(tmp);
  return (i);
}

int		adjust_list(t_coord *rooms, t_ant *list, char *turn)
{
  t_ant		*ptr;
  char		*tmp;
  int		nbr;
  int		i;
  int		j;

  i = 0;
  while (turn[i])
    {
      while (turn[i] && (turn[i] < '0' || turn[i] > '9'))
        i = i + 1;
      j = i;
      while (turn[i] && turn[i] >= '0' && turn[i] <= '9')
        i = i + 1;
      tmp = strndup(turn + j, i - j);
      nbr = my_getnbr(tmp);
      free(tmp);
      ptr = list;
      while (ptr && ptr->nbr != nbr)
        ptr = ptr->next;
      if (!ptr || (i = adjust_list_process(ptr, rooms, turn, i + 1)) < 0)
	return (-1);
    }
  return (0);
}
