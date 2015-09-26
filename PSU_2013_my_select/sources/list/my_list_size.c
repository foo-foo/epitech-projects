/*
** my_list_size.c for j_12 in /home/menich_a/rendu/Piscine-C-Jour_12/ex_02
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct 22 16:27:11 2013 menich_a
** Last update Fri Jan 10 13:42:26 2014 menich_a
*/

#include "list.h"

int	my_list_size(t_list *origin)
{
  int		i;
  t_list	*ptr;

  ptr = origin;
  ptr = ptr->next;
  i = 0;
  while (ptr != origin)
    {
      ptr = ptr->next;
      i = i + 1;
    }
  return (i);
}
