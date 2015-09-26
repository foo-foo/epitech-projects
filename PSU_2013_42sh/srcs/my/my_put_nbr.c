/*
** my_put_nbr.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:36:45 2013 menich_a
** Last update Fri May 16 20:01:32 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

int	my_put_nbr(int nb)
{
  int	div;
  char	res;

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
  while (div != 0)
    {
      res = nb / div + 48;
      nb = nb % div;
      div = div / 10;
      my_putchar(res);
    }
  return (0);
}

char	*my_nbr_to_str(int nb)
{
  int	i;
  int	div;
  char	*nbr;

  i = 0;
  div = 1;
  if (nb < 0)
    return (NULL);
  while (nb / div > 9)
    {
      i = i + 1;
      div = div * 10;
    }
  if ((nbr = malloc(sizeof(*nbr) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (div != 0)
    {
      nbr[i] = nb / div + 48;
      i = i + 1;
      nb = nb % div;
      div = div / 10;
    }
  nbr[i] = '\0';
  return (nbr);
}
