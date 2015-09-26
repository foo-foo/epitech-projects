/*
** my_create_list.c for liblist.a in /home/menich_a/rendu/CPE_2013_push_swap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan  4 15:08:09 2014 menich_a
** Last update Sun Jan 19 19:21:55 2014 menich_a
*/

#include <stdlib.h>
#include "list.h"

t_list		*my_create_list(void)
{
  t_list	*origin;

  origin = malloc(sizeof(*origin));
  if (origin != NULL)
    {
      origin->data = NULL;
      origin->next = origin;
      origin->prev = origin;
    }
  return (origin);
}
