/*
** my_strndup.c for libmy.a in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan  3 11:48:41 2014 menich_a
** Last update Sun May 25 11:47:49 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

char	*my_strndup(char *str, int size)
{
  char	*cpy;
  int	i;

  i = 0;
  if (size > my_strlen(str) || size < 0)
    size = my_strlen(str);
  cpy = malloc(sizeof(*cpy) * (size + 1));
  if (cpy == NULL)
    {
      msg_error("mysh: error: malloc failed\n");
      return (NULL);
    }
  while (str[i] != '\0' && i < size)
    {
      cpy[i] = str[i];
      i = i + 1;
    }
  cpy[i] = '\0';
  return (cpy);
}

char	*my_xstrndup(char *str, int size)
{
  char	*dup;

  if (!str)
    return (NULL);
  dup = my_strndup(str, size);
  free(str);
  return (dup);
}
