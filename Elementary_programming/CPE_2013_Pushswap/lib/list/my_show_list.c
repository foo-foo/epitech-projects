/*
** my_show_list.c for liblist in /home/menich_a/rendu/CPE_2013_push_swap/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan  4 15:07:08 2014 menich_a
** Last update Mon Jan  6 21:50:07 2014 menich_a
*/

#include "push_swap.h"
#include "my.h"

void		display(char c)
{
  write(1, &c, 1);
}

void		my_putnbr(int nb)
{
  int		div;
  int		res;

  div = 1;
  if (nb < 0)
    {
      my_putchar('-');
      nb = -nb;
    }
  while (nb / div > 9)
    {
      div = div * 10;
    }
  while (div > 0)
    {
      res = nb / div + 48;
      nb = nb % div;
      div = div / 10;
      display(res);
    }
}

void		my_show_list(t_list *origin)
{
  t_list	*ptr;

  ptr = origin;
  ptr = ptr->next;
  while (ptr != origin)
    {
      my_putnbr(ptr->value);
      if (ptr->next != origin)
	{
	  my_putchar(' ');
	}
      ptr = ptr->next;
    }
}
