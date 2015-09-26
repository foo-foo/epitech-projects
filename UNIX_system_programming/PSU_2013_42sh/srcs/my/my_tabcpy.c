/*
** my_tabcpy.c for libmy in /home/menich_a/rendu/PSU_2013_minishell1/sources/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 29 13:11:33 2014 menich_a
** Last update Sat May 24 21:42:02 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

char	**my_tabcpy(char **dest, char **src)
{
  int	i;

  i = 0;
  while (src[i] != NULL)
    {
      if ((dest[i] = my_strdup(src[i])) == NULL)
	return (NULL);
      i = i + 1;
    }
  dest[i] = NULL;
  return (dest);
}
