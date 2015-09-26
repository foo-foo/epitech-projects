/*
** my_getnbr.c for libmy.a in /home/menich_a/rendu/PSU_2013_minishell1/lib/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec 30 12:10:45 2013 menich_a
** Last update Fri Feb  7 14:59:31 2014 menich_a
*/

#include <stdlib.h>

int	my_getnbr(char *str)
{
  int	res;
  int	i;

  i = 0;
  res = 0;
  if (str == NULL || str[0] == '\0')
    return (0);
  if (str[0] == '-')
    i = i + 1;
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
      res = (res * 10) + (str[i] - 48);
      i = i + 1;
    }
  if (str[i] != '\0' && (str[i] < '0' || str[i] > '9'))
    return (0);
  if (str[0] == '-')
    return (-res);
  return (res);
}
