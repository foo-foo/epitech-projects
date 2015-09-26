/*
** my_rm_list.c for liblist.a in /home/menich_a/rendu/CPE_2013_Pushswap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jan  6 23:10:16 2014 menich_a
** Last update Mon Jan  6 23:17:57 2014 menich_a
*/

#include <stdlib.h>
#include "push_swap.h"

void		my_rm_list(t_list *list)
{
  t_list	*ptr;

  ptr = list->next;
  while (ptr != list)
    {
      my_rm_from_list(list, ptr);
      ptr = list->next;
    }
  my_rm_from_list(list, ptr);
}
