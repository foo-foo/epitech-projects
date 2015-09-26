/*
** l_a_operations.c for push_swap in /home/menich_a/rendu/CPE_2013_push_swap
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec  9 15:45:47 2013 menich_a
** Last update Mon Jan  6 22:23:34 2014 menich_a
*/

#include <stdlib.h>
#include "push_swap.h"

int		sa(t_list *l_a)
{
  int		tmp;
  t_list	*ptr;

  my_putstr("sa ");
  tmp = 0;
  ptr = l_a;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->next;
  if (ptr != l_a && ptr->next != l_a)
    {
      tmp = ptr->value;
      ptr->value = ptr->next->value;
      ptr->next->value = tmp;
    }
  return (0);
}

int		pa(t_list *l_a, t_list *l_b)
{
  t_list        *ptr;

  my_putstr("pb ");
  ptr = l_b;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->next;
  if (ptr != l_b)
    {
      my_put_in_list(l_a, ptr->value);
      my_rm_from_list(l_b, ptr);
    }
  else
    {
      return (1);
    }
  return (0);
}

int		ra(t_list *l_a)
{
  t_list	*ptr;

  my_putstr("ra ");
  ptr = l_a;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->next;
  if (ptr != l_a)
    {
      my_put_end_list(l_a, ptr->value);
      my_rm_from_list(l_a, ptr);
    }
  return (0);
}

int		rra(t_list *l_a)
{
  t_list	*ptr;

  my_putstr("rra ");
  ptr = l_a;
  if (ptr == NULL)
    {
      return (1);
    }
  ptr = ptr->prev;
  if (ptr != l_a)
    {
      my_put_in_list(l_a, ptr->value);
      my_rm_from_list(l_a, ptr);
    }
  return (0);
}
