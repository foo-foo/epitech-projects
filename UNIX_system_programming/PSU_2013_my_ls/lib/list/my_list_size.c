/*
** my_list_size.c for j_12 in /home/menich_a/rendu/Piscine-C-Jour_12/ex_02
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct 22 16:27:11 2013 menich_a
** Last update Thu Nov 28 13:14:48 2013 menich_a
*/

#include "my_ls.h"
#include <stdlib.h>

int	my_list_size(t_list *begin)
{
  int		i;
  t_list	*tmp;

  tmp = begin;
  i = 0;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i = i + 1;
    }
  return (i);
}
