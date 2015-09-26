/*
** my_getnbr.c for libmy.a in /home/menich_a/rendu/PSU_2013_minishell1/lib/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec 30 12:10:45 2013 menich_a
** Last update Mon Dec 30 12:21:41 2013 menich_a
*/

#include <stdlib.h>

int	my_getnbr(char *str)
{
  int	res;
  int	i;
  int	j;

  i = 0;
  res = 0;
  if (str == NULL)
    return (0);
  while (str[i] != '\0' && (str[i] < '0' || str[i] > '9'))
    {
      i = i + 1;
    }
  j = i - 1;
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      res = (res * 10) + (str[i] - 48);
      i = i + 1;
    }
  if (j >= 0 && str[j] == '-')
    {
      return (-res);
    }
  return (res);
}
