/*
** my_tools.c for my_printf in /home/menich_a/rendu/PSU_2013_my_printf
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Nov 15 16:06:46 2013 menich_a
** Last update Sun Nov 17 20:46:19 2013 menich_a
*/

#include <stdlib.h>
#include "my.h"

unsigned int    my_nbrlen(unsigned int nb)
{
  unsigned int  div;
  unsigned int  size;

  div = 1;
  size = 0;
  while (nb / div > 9)
    {
      div = div * 10;
      size = size + 1;
    }
  return (size + 1);
}

char    *from_base_ten(int nbr, char *base_to)
{
  char	*res;
  char  *nb;
  int   b;
  int   i;
  int   div;

  b = my_strlen(base_to);
  i = 0;
  div = nbr;
  while (b <= div)
    {
      div = div / b;
      i = i + 1;
    }
  nb = malloc(i + 1);
  while (i >= 0)
    {
      nb[i] = base_to[nbr % b];
      nbr = nbr / b;
      i = i - 1;
    }
  return (nb);
}

int     my_showstr_oct(char *str)
{
  int   i;
  int   n;

  i = 0;
  n = 0;
  while (str[i] != '\0')
    {
      if (str[i] < 32 || str[i] > 126)
        {
          my_putchar(92);
	  my_putstr(from_base_ten(str[i], "01234567"));
        }
      else
        my_putchar(str[i]);
      i = i + 1;
    }
  return (0);
}

void            my_put_unsigned_nbr(unsigned int nb)
{
  unsigned int  res;
  unsigned int  div;

  div = 1;
  while (nb / div > 9)
    {
      div = div * 10;
    }
  while (div > 0)
    {
      res = nb / div + 48;
      nb = nb % div;
      div = div / 10;
      my_putchar(res);
    }
}
