/*
** tab.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Apr 25 12:15:58 2014 menich_a
** Last update Sat May  3 19:10:38 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

char	**my_tab_dup(char **tab)
{
  int	i;
  char	**save;

  i = 0;
  if (tab == NULL)
    return (NULL);
  while (tab[i])
    i = i + 1;
  save = malloc(sizeof(*save) * (i + 1));
  if (save == NULL)
    return (NULL);
  i = 0;
  while (tab[i] != NULL)
    {
      if ((save[i] = my_strdup(tab[i])) == NULL)
	return (NULL);
      i = i + 1;
    }
  save[i] = NULL;
  return (save);
}

char	**my_free_tab(char **tab)
{
  int	i;

  i = 0;
  if (tab == NULL)
    return (NULL);
  while (tab[i])
    {
      free(tab[i]);
      i = i + 1;
    }
  free(tab);
  return (NULL);
}

int	my_tabcmp(char **tab1, char **tab2)
{
  int	i;

  i = 0;
  if (!tab1 || !tab2)
    return (0);
  while (tab1[i] && tab2[i] && !my_strcmp(tab1[i], tab2[i]))
    i = i + 1;
  return (my_strcmp(tab1[i], tab2[i]));
}

int	tab_len(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    i = i + 1;
  return (i);
}
