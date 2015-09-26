/*
** my_rm_from_list.c for liblist.a in /home/menich_a/rendu/CPE_2013_push_swap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan  4 15:09:29 2014 menich_a
** Last update Tue Jan 14 18:45:01 2014 menich_a
*/

#include <stdlib.h>
#include "list.h"

void		my_rm_from_list(t_list *origin, t_list *to_rm)
{
  t_list	*ptr;

  ptr = origin->next;
  while (ptr->next != to_rm)
    {
      ptr = ptr->next;
    }
  ptr->next = to_rm->next;
  free(to_rm);
}
