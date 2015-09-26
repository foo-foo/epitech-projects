/*
** my_put_end_list.c for liblist.a in /home/menich_a/rendu/CPE_2013_push_swap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan  4 15:10:16 2014 menich_a
** Last update Mon Jan  6 17:41:18 2014 menich_a
*/

#include <stdlib.h>
#include "push_swap.h"

void		my_put_end_list(t_list *ptr, int value)
{
  t_list	*elem;

  elem = malloc(sizeof(*elem));
  if (elem != NULL)
    {
      elem->value = value;
      elem->prev = ptr->prev;
      elem->next = ptr;
      ptr->prev->next = elem;
      ptr->prev = elem;
    }
}
