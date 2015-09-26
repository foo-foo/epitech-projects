/*
** my_strdup.c for libmy in /home/menich_a/rendu/CPE-2013-BSQ/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Dec  7 02:19:46 2013 menich_a
** Last update Fri May 30 19:15:56 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *str)
{
  char	*cpy;
  int	i;

  i = 0;
  if (str == NULL)
    return (NULL);
  cpy = malloc(sizeof(*cpy) * (my_strlen(str) + 1));
  if (cpy == NULL)
    {
      msg_error("mysh: malloc failed: insufficient storage space.\n");
      return (NULL);
    }
  while (str[i] != '\0')
    {
      cpy[i] = str[i];
      i = i + 1;
    }
  cpy[i] = '\0';
  return (cpy);
}

char	*my_str_catdup(char *s1, char *s2)
{
  int	size;
  char	*str;

  if (s1 == NULL && s2 == NULL)
    return (NULL);
  if (s1 == NULL && s2)
    return (my_strdup(s2));
  if (s2 == NULL && s1)
    return (my_strdup(s1));
  size = my_strlen(s1) + my_strlen(s2);
  if ((str = malloc(sizeof(*str) * (size + 1))) == NULL)
    {
      msg_error("mysh: malloc failed: insufficient storage space.\n");
      return (NULL);
    }
  my_strcpy(str, s1);
  my_strcat(str, s2);
  str[size] = '\0';
  return (str);
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
