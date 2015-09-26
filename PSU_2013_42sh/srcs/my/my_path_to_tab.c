/*
** my_path_to_tab.c for minishell1l in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Dec 20 18:45:38 2013 menich_a
** Last update Fri May 30 19:10:40 2014 menich_a
*/

#include <stdlib.h>
#include "mysh.h"
#include "my.h"

char		**get_path(char **path)
{
  static char	**path_cpy = NULL;
  int		i;

  if (path)
    {
      i = 0;
      if (path_cpy)
	my_free_tab(path_cpy);
      path_cpy = malloc(sizeof(*path_cpy) * (my_tablen(path) + 1));
      if (!path_cpy)
	return (NULL);
      while (path[i])
	{
	  path_cpy[i] = my_strdup(path[i]);
	  i = i + 1;
	}
      path_cpy[i] = NULL;
    }
  return (path_cpy);
}

/*
**	Fill the tab previously initializated by `my_path_to_tab'.
*/
char		**my_create_path_tab(char *old_path, char **path, int size, int i)
{
  int		j;
  int		k;

  j = 0;
  while (old_path[i] != '\0')
    {
      k = 0;
      size = 0;
      while (old_path[i] != ':' && old_path[i++] != '\0')
        size = size + 1;
      i = i - size;
      if (old_path[i] != '/')
        i = i - 1;
      path[j] = malloc(sizeof(**path) * (size + 1));
      if (path[j] == NULL)
        return (NULL);
      while (old_path[i] != ':' && old_path[i] != '\0')
        path[j][k++] = old_path[i++];
      path[j++][k] = '\0';
      if (old_path[i] == ':')
        i = i + 1;
    }
  path[j] = NULL;
  return (path);
}

/*
**	Creates and returns a tab from path environnement variable.
**	Each compartment contains a path-way (separated by ':' by default).
*/
char		**my_path_to_tab(char *old_path)
{
  char		**path;
  int		size;
  int		i;

  size = 0;
  i = 0;
  if (old_path == NULL)
    return (NULL);
  while (old_path[i] != '\0')
    {
      if (old_path[i] == ':')
	size = size + 1;
      i = i + 1;
    }
  path = malloc(sizeof(*path) * (size + 2));
  if (path == NULL)
    return (NULL);
  path = my_create_path_tab(old_path, path, size, 0);
  get_path(path);
  return (path);
}
