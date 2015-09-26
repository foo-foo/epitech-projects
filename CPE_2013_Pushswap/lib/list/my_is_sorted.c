/*
** my_is_sorted.c for liblist.a in /home/menich_a/rendu/CPE_2013_push_swap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan  4 15:12:56 2014 menich_a
** Last update Mon Jan  6 15:40:16 2014 menich_a
*/

#include "push_swap.h"

int		my_is_sorted(t_list *origin)
{
  t_list	*ptr;

  ptr = origin->next;
  while (ptr->next != origin)
    {
      if (ptr->value > ptr->next->value)
	{
	  return (1);
	}
      ptr = ptr->next;
    }
  return (0);
}
