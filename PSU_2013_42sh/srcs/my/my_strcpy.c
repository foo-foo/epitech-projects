/*
** my_strcpy.c for libmy.a in /home/menich_a/rendu/PSU_2013_minishell1/lib/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Dec 26 22:30:35 2013 menich_a
** Last update Mon Feb  3 13:39:57 2014 menich_a
*/

#include <stdlib.h>

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  if (src == NULL)
    {
      dest = NULL;
      return (dest);
    }
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  return (dest);
}
