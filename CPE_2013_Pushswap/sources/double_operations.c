/*
** double_operations.c for push_swap in /home/menich_a/rendu/CPE_2013_push_swap/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec  9 16:25:22 2013 menich_a
** Last update Mon Jan  6 22:07:12 2014 menich_a
*/

#include "push_swap.h"

int		ss(t_list *l_a, t_list *l_b)
{
  if (sa(l_a) == 1)
    {
      return (1);
    }
  if (sb(l_b) == 1)
    {
      return (1);
    }
  return (0);
}

int		rr(t_list *l_a, t_list *l_b)
{
  if (ra(l_a) == 1)
    {
      return (1);
    }
  if (rb(l_b) == 1)
    {
      return (1);
    }
  return (0);
}

int		rrr(t_list *l_a, t_list *l_b)
{
  if (rra(l_a) == 1)
    {
      return (1);
    }
  if (rrb(l_b) == 1)
    {
      return (1);
    }
  return (0);
}
