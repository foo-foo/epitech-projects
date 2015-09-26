/*
** my_tablen.c for libmy in /home/menich_a/rendu/PSU_2013_minishell1/sources/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 29 13:10:05 2014 menich_a
** Last update Thu May 29 15:56:05 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

int	my_tablen(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    i = i + 1;
  return (i);
}

char	**my_tabdup(char **tab)
{
  int	i;
  char	**tab_dup;

  i = 0;
  if (!tab)
    return (NULL);
  tab_dup = malloc((my_tablen(tab) + 1) * sizeof(char*));
  if (tab_dup == NULL)
    {
      msg_error("mysh: malloc failed: insufficient storage space.\n");
      return (NULL);
    }
  while (tab[i])
    {
      tab_dup[i] = my_strdup(tab[i]);
      if (tab_dup[i] == NULL)
	return (NULL);
      i++;
    }
  tab_dup[i] = NULL;
  return (tab_dup);
}

