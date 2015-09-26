/*
** my_strdup.c for libmy in /home/menich_a/rendu/CPE-2013-BSQ/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Dec  7 02:19:46 2013 menich_a
** Last update Sun Jan 19 23:15:18 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *str)
{
  char	*cpy;
  int	i;

  i = 0;
  if (str == NULL)
    return (NULL);
  cpy = malloc(sizeof(*cpy) * (my_strlen(str) + 1));
  if (cpy == NULL)
    exit(-1);
  while (str[i] != '\0')
    {
      cpy[i] = str[i];
      i = i + 1;
    }
  cpy[i] = '\0';
  return (cpy);
}
