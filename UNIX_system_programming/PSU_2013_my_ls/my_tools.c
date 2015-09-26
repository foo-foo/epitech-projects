/*
** my_tools.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Nov 27 13:47:51 2013 menich_a
** Last update Sun Dec  1 21:27:44 2013 menich_a
*/

#include <stdlib.h>
#include "my_ls.h"

int     find_in_tab(char *str, char to_find)
{
  int   i;

  i = 0;
  while (str[i] != to_find && str[i] != '\0')
    {
      i = i + 1;
    }
  if (str[i] == '\0')
    {
      return (-1);
    }
  return (0);
}

char	*my_strdup(char *str)
{
  char	*cpy;
  int	i;

  i = 0;
  cpy = malloc(sizeof(*cpy) * (my_strlen(str) + 1));
  if (cpy == NULL)
    {
      exit(-1);
    }
  while (str[i] != '\0')
    {
      cpy[i] = str[i];
      i = i + 1;
    }
  cpy[i] = '\0';
  return (cpy);
}

char	*my_get_str(int nb)
{
  int	i;
  int	div;
  char	*res;

  i = 0;
  div = 1;
  while (nb / div > 0)
    {
      div = div * 10;
      i = i + 1;
    }
  if (nb == 0)
    i = i + 1;
  res = malloc(sizeof(*res) * (i + 1));
  if (res == NULL)
    exit(-1);
  res[i] = '\0';
  while (i >= 0)
    {
      i = i - 1;
      res[i] = nb % 10 + 48;
      nb = nb / 10;
    }
  return (res);
}
