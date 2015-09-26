/*
** my_strncat.c for  in /home/menich_a/rendu/Piscine-C-Jour_07/ex_01
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 15:53:06 2013 menich_a
** Last update Sun Jan 19 17:54:24 2014 menich_a
*/

#include "my.h"

char	*my_strncat(char *dest, char *src, int nb)
{
  int	i;
  int	j;

  i = my_strlen(dest);
  j = 0;
  if (nb > my_strlen(src) || nb < 0)
    {
      nb = my_strlen(src);
    }
  while (j < nb)
    {
      dest[i] = src[j];
      i = i + 1;
      j = j + 1;
    }
  dest[i] = '\0';
  return (dest);
}
