/*
** push_swap.c for push_swap in /home/menich_a/rendu/CPE_2013_push_swap
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec  9 15:16:22 2013 menich_a
** Last update Mon Jan  6 23:19:03 2014 menich_a
*/

#include <stdlib.h>
#include "push_swap.h"
#include "list.h"
#include "my.h"

int		first_is_min(t_list *list)
{
  t_list	*ptr;
  int		tmp;

  ptr = list;
  ptr = ptr->next;
  tmp = ptr->value;
  while (ptr != list)
    {
      if (tmp > ptr->value)
	{
	  return (1);
	}
      ptr = ptr->next;
    }
  return (0);
}

int		display_states(t_list *l_a, t_list *l_b)
{
  my_putchar('\n');
  my_putstr("l_a: ");
  my_show_list(l_a);
  my_putchar('\n');
  my_putstr("l_b: ");
  my_show_list(l_b);
  my_putchar('\n');
  my_putchar('\n');
}

int		push_swap(t_list *l_a, t_list *l_b, int check_option, int check)
{
  t_list	*ptr;

  ptr = l_a->next;
  if (ptr == NULL || ptr == l_a)
    return (1);
  if (first_is_min(l_a) == 0)
    {
      check = pb(l_a, l_b);
      if (check_option == 42)
	display_states(l_a, l_b);
    }
  if (ptr->value > ptr->next->value)
    {
      check = sa(l_a);
      if (check_option == 42)
	display_states(l_a, l_b);
    }
  if (check == 42)
    {
      ra(l_a);
      if (check_option == 42)
	display_states(l_a, l_b);
    }
  return (0);
}

int		launch_pushswap(t_list *l_a, t_list *l_b, char *arg)
{
  int		check_option;

  check_option = 0;
  if (arg != NULL && my_strcmp(arg, "-v") == 0)
    {
      check_option = 42;
    }
  while (my_is_sorted(l_a) != 0)
    {
      push_swap(l_a, l_b, check_option, 42);
    }
  while (my_list_size(l_b) > 0)
    {
      pa(l_a, l_b);
      if (check_option == 42)
	{
	  display_states(l_a, l_b);
	}
    }
  my_putchar('\n');
  return (0);
}
int		main(int ac, char **av)
{
  int		i;
  t_list	*l_a;
  t_list	*l_b;

  i = 1;
  if (av[1] != NULL && my_strcmp(av[1], "-v") == 0)
    {
      i = 2;
    }
  l_a = my_create_list();
  l_b = my_create_list();
  if (l_a == NULL || l_b == NULL)
    return (1);
  while (i < ac)
    {
      my_put_after_list(l_a, my_getnbr(av[i++]));
    }
  if (ac < 3 || my_is_sorted(l_a) == 0)
    {
      return (0);
    }
  my_putstr("\r");
  launch_pushswap(l_a, l_b, av[1]);
  my_rm_list(l_a);
  return (0);
}
