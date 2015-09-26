/*
** my2.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Apr 20 11:39:56 2014 menich_a
** Last update Fri May  2 19:26:11 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (s1 == NULL && s2 == NULL)
    return (0);
  if (s1 == NULL || s2 == NULL)
    return (-1);
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i = i + 1;
  return (s1[i] - s2[i]);
}

int	my_str_isnum(char *str)
{
  int	i;

  i = 0;
  if (!str)
    return (0);
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
        return (0);
      i = i + 1;
    }
  return (1);
}

int	my_getnbr(char *nb)
{
  int	i;
  int	nbr;

  i = 0;
  nbr = 0;
  if (nb)
    {
      while (nb[i] == ' ')
        i = i + 1;
      if (nb[i] == '-')
        i = i + 1;
      while (nb[i] != '\0' && nb[i] >= '0' && nb[i] <= '9')
        {
          nbr = (nbr * 10) + (nb[i] - 48);
          i = i + 1;
        }
      if (nb[0] == '-')
        return (-nbr);
    }
  return (nbr);
}

char	*my_strdup(char *str)
{
  char	*dup;
  int	i;

  i = 0;
  if (!str || (dup = malloc(sizeof(*dup) * (my_strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[i])
    {
      dup[i] = str[i];
      i = i + 1;
    }
  dup[i] = '\0';
  return (dup);
}

char	*my_strcatdup(char *s1, char *s2)
{
  char	*str;
  int	i;
  int	j;

  i = 0;
  j = 0;
  str = malloc(sizeof(*str) * (my_strlen(s1) + my_strlen(s2) + 1));
  if (str)
    {
      while (s1[i])
        str[j++] = s1[i++];
      i = 0;
      while (s2[i])
        str[j++] = s2[i++];
      str[j] = '\0';
      free(s1);
      free(s2);
    }
  return (str);
}
