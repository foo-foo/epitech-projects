/*
** my_putstr.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:45:28 2013 menich_a
** Last update Tue Oct  8 10:51:27 2013 menich_a
*/

#include <stdlib.h>

int	my_putstr(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    {
      return (0);
    }
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i = i + 1;
    }
  return (0);
}
