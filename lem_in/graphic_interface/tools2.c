/*
** read_data2.c for  in /home/bencha_a/lem-in/v2./interface_graphique
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Sat May  3 18:18:48 2014 bencharif
** Last update Sun May  4 19:50:07 2014 menich_a
*/

#include <string.h>
#include <stdlib.h>
#include "graph.h"

char	**my_realloc(char **tab)
{
  char	**new;
  int	i;

  i = 0;
  while (tab[i])
    i = i + 1;
  new = malloc(sizeof(*new) * (i + 2));
  if (!new)
    {
      my_putstr("Malloc failed.\n");
      exit(-1);
    }
  i = 0;
  while (tab[i])
    {
      if ((new[i] = strdup(tab[i])) == NULL)
        exit(-1);
      free(tab[i]);
      i = i + 1;
    }
  free(tab);
  new[i] = NULL;
  return (new);
}

char	**my_tab_dup(char **tab)
{
  int	i;
  char	**tab_dup;

  i = 0;
  while (tab[i] != NULL)
    i++;
  tab_dup = malloc((i + 1) * sizeof(char*));
  if (tab_dup == NULL)
    return (NULL);
  i = 0;
  while (tab[i])
    {
      tab_dup[i] = strdup(tab[i]);
      i++;
    }
  tab_dup[i] = NULL;
  return (tab_dup);
}
