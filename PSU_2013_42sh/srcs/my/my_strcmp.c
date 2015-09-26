/*
** my_strcmp.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_05
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 16:43:06 2013 menich_a
** Last update Fri May 30 19:14:50 2014 menich_a
*/

#include <stdlib.h>

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (s1 == NULL && s2 == NULL)
    return (0);
  if (s1 == NULL || s2 == NULL)
    return (-1);
  while (s1[i] == s2[i] && s1[i] != '\0')
    {
      i = i + 1;
    }
  return (s1[i] - s2[i]);
}


int	my_strncmp(char *s1, char *s2, int size)
{
  int	i;

  i = 0;
  if (s1 == NULL && s2 == NULL)
    return (0);
  if (s1 == NULL || s2 == NULL)
    return (-1);
  while (i < size && s1[i] != '\0' && s1[i] == s2[i])
    {
      i = i + 1;
    }
  return (s1[i] - s2[i]);
}
