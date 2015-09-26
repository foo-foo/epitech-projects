/*
** my_strlen.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:51:51 2013 menich_a
** Last update Thu May  8 14:11:40 2014 menich_a
*/

#include <stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  return (i);
}

int	my_nbrlen(unsigned int nb)
{
  int	div;
  int	size;

  size = 0;
  div = 1;
  while (nb / div > 9)
    div = div * 10;
  while (div > 0)
    {
      nb = nb % div;
      div = div / 10;
      size = size + 1;
    }
  return (size);
}
