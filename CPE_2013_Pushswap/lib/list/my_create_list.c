/*
** my_create_list.c for liblist.a in /home/menich_a/rendu/CPE_2013_push_swap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan  4 15:08:09 2014 menich_a
** Last update Sat Jan  4 15:09:20 2014 menich_a
*/

#include <stdlib.h>
#include "push_swap.h"

t_list		*my_create_list(void)
{
  t_list	*origin;

  origin = malloc(sizeof(*origin));
  if (origin != NULL)
    {
      origin->next = origin;
      origin->prev = origin;
    }
  return (origin);
}
