/*
** my_strcpy.c for  in /home/menich_a/rendu/Piscine-C-Jour_06
** 
** Made by menich_a
-** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 07:21:11 2013 menich_a
** Last update Tue Nov  5 17:32:04 2013 menich_a
*/

#include <stdlib.h>

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  if (src == NULL)
    {
      my_putstr("strcpy: try to copy empty string");
      return (NULL);
    }
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  return (dest);
}
