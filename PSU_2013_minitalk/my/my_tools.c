/*
** my_tools.c for my in /home/menich_a/rendu/PSU_2013_minitalk/my/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 22 22:15:56 2014 menich_a
** Last update Sun Mar 23 14:07:45 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i = i + 1;
  return (s1[i] - s2[i]);
}

void	my_exit(char *msg, int *clients)
{
  free(msg);
  free(clients);
  exit(0);
}
