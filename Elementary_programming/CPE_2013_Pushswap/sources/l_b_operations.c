/*
** l_b_operations.c for l_b_operations.c in /home/menich_a/rendu/CPE_2013_push_swap/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec  9 16:22:38 2013 menich_a
** Last update Mon Jan  6 17:43:10 2014 menich_a
*/

#include <stdlib.h>
#include "push_swap.h"

int		sb(t_list *l_b)
{
  int           tmp;
  t_list        *ptr;

  my_putstr("sb ");
  tmp = 0;
  ptr = l_b;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->next;
  if (ptr != l_b && ptr->next != l_b)
    {
      tmp = ptr->value;
      ptr->value = ptr->next->value;
      ptr->next->value = tmp;
    }
  return (0);
}

int		pb(t_list *l_a, t_list *l_b)
{
  t_list        *ptr;

  my_putstr("pb ");
  ptr = l_a;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->next;
  if (ptr != l_a)
    {
      my_put_in_list(l_b, ptr->value);
      my_rm_from_list(l_a, ptr);
    }
  else
    {
      return (1);
    }
  return (0);
}

int		rb(t_list *l_b)
{
  t_list        *ptr;

  my_putstr("rb ");
  ptr = l_b;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->next;
  if (ptr != l_b)
    {
      my_put_end_list(l_b, ptr->value);
      my_rm_from_list(l_b, ptr);
    }
  return (0);
}

int		rrb(t_list *l_b)
{
  t_list        *ptr;

  my_putstr("rrb ");
  ptr = l_b;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->prev;
  if (ptr != l_b)
    {
      my_put_in_list(l_b, ptr->value);
      my_rm_from_list(l_b, ptr);
    }
  return (0);
}
