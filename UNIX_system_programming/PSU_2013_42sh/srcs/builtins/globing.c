/*
** globing.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/match
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat May 10 02:30:23 2014 menich_a
** Last update Sun Jun  1 20:34:05 2014 menich_a
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "my.h"

int		check_extremities(char *s1, char *s2, int size)
{
  int		i;

  if (!s1 || !s2 || !s1[0])
    return (1);
  if (s1[0] == '*' && s1[my_strlen(s1) - 1] == '*')
    return (0);
  if (s1[0] != '*')
    {
      i = 0;
      while (s1[i] && s1[i] != '*')
	i = i + 1;
      if (my_strncmp(s1, s2, i))
	return (1);
    }
  if (s1[my_strlen(s1) - 1] != '*')
    {
      i = my_strlen(s1) - 1;
      while (i >= 0 && s1[i] != '*')
	i = i - 1;
      i = i + 1;
      size = my_strlen(s2) - 1 - ((my_strlen(s1) - 1) - i);
      if (my_strcmp(s1 + i, s2 + size))
	return (1);
    }
  return (0);
}

int		match(char *s1, char *s2, int i, int j)
{
  int		cpt;

  if (!my_strcmp(s1, s2))
    return (1);
  if (check_extremities(s1, s2, 0))
    return (0);
  while (s1[i] == '*')
    i = i + 1;
  while (s1[i])
    {
      j = i;
      while (s1[i] && s1[i] != '*')
	i = i + 1;
      if (s1[i])
	{
	  while (cpt < my_strlen(s2) && my_strncmp(s1 + j, s2 + cpt, i - j))
	    cpt = cpt + 1;
	  if (cpt == my_strlen(s2))
	    return (0);
	  while (s1[i] == '*')
	    i = i + 1;
	}
    }
  return (1);
}

char		**add_in_tab(char **tab, char *elem, char *path)
{
  int		i;

  i = 0;
  while (tab && tab[i])
    i = i + 1;
  tab = realloc(tab, sizeof(*tab) * (i + 2));
  if (!tab)
    return (msg_error_return("mysh: error: realloc failed.\n", NULL));
  if (!my_strcmp(path, "."))
    tab[i] = my_strdup(elem);
  else
    tab[i] = my_str_catdup(path, elem);
  if (!tab[i])
    return (NULL);
  tab[i + 1] = NULL;
  return (tab);
}

char		**glob_data_to_tab(char *globing, int i)
{
  char		**tab;
  char		*path;
  char		*str;
  DIR		*dir;
  struct dirent	*file;

  tab = NULL;
  while (i >= 0 && globing[i] != '/')
    i = i - 1;
  if (++i > 0)
    path = my_strndup(globing, i);
  else
    path = my_strdup(".");
  if (!path || !(str = my_strdup(globing + i)))
    return (NULL + 1);
  if ((dir = opendir(path)) == NULL)
    return (NULL + 1);
  while ((file = readdir(dir)) != NULL)
    if (file->d_name[0] != '.' && match(str, file->d_name, 0, 0))
      if ((tab = add_in_tab(tab, file->d_name, path)) == NULL)
	return (NULL + 1);
  if (closedir(dir) < 0)
    return (NULL + 1);
  return (tab);
}

char		**get_globing_datas(char **cmd, int i, int j)
{
  char		**new;
  char		**tmp;
  int		y;

  while ((y = my_find_in_tab(cmd, '*')) >= 0)
    {
      if ((i = -1) && !(tmp = glob_data_to_tab(cmd[y], my_strlen(cmd[y]) - 1)))
	return (cmd);
      if (tmp == NULL + 1 ||
	  !(new = malloc(sizeof(*new) * (my_tablen(cmd) + my_tablen(tmp)))))
	return (msg_error_return("mysh: error: malloc failed.\n", 0));
      while (++i < y)
	new[i] = cmd[i];
      while (tmp[j])
	new[i++] = tmp[j++];
      if (tmp || (cmd[y] = my_free(cmd[y])))
	free(tmp);
      while (cmd[++y])
	new[i++] = cmd[y];
      new[i] = NULL;
      if (cmd)
	free(cmd);
      cmd = new;
    }
  return (cmd);
}
