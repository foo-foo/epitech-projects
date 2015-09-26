/*
** my_remove_spaces.c for libmy in /home/menich_a/rendu/PSU_2013_minishell2/sources/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 25 12:11:48 2014 menich_a
** Last update Fri May 30 19:13:51 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

char	*my_remove_spaces(char *str)
{
  int	i;
  int	size;
  char	*tmp;

  i = 0;
  size = 0;
  while (str[i] != '\0')
    {
      if (str[i] != ' ')
        size = size + 1;
      i = i + 1;
    }
  tmp = malloc(sizeof(*tmp) * size + 1);
  if (tmp == NULL)
    return (NULL);
  i = 0;
  size = 0;
  while (str[i] != '\0')
    {
      if (str[i] != ' ')
        tmp[size++] = str[i];
      i = i + 1;
    }
  tmp[size] = '\0';
  return (tmp);
}

int	validity_check(char **cmd, int j, int i)
{
  if (j < i || !my_strcmp(cmd[i], "cc/openmpi/lib64"))
    return (1);
  if (cmd[i] == NULL || cmd[i] == NULL + 1)
    return (1);
  return (0);
}
