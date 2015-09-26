/*
** dynamic_completion.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs/termcaps
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May  8 23:07:31 2014 menich_a
** Last update Fri May 30 19:48:33 2014 menich_a
*/

#include <dirent.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "alias.h"
#include "my.h"

char		**alias_completion(char *name, char **env)
{
  t_alias	*list;
  char		**tab;

  tab = NULL;
  if ((list = get_alias(0, 0, 0, env)) == NULL + 1)
    return (NULL);
  while (list)
    {
      if (!name[0] || !my_strncmp(name, list->alias, my_strlen(name) - 1))
	if ((tab = add_one_choice(tab, list->alias, 0)) == NULL)
	  return (NULL);
      list = list->next;
    }
  return (tab);
}

char		**path_completion_process(char *path, char *name, char **tab)
{
  DIR		*dir;
  struct dirent	*file;

  if ((dir = opendir(path)) == NULL)
    return (NULL);
  while ((file = readdir(dir)) != NULL)
    if (!name[0] || !my_strncmp(name, file->d_name, my_strlen(name) - 1))
      if ((tab = add_one_choice(tab, file->d_name, 1)) == NULL)
	return (NULL);
  if (closedir(dir) < 0)
    return (my_warn_ret("close error"));
  free(path);
  free(name);
  return (tab);
}

char		**path_completion(char *name)
{
  char		**tab;
  char		*path;
  char		*tmp;
  int		i;

  tab = NULL;
  i = my_strlen(name) - 1;
  while (i >= 0 && name[i] != '/')
    i = i - 1;
  if (i < 0)
    path = my_strdup(".");
  else
    {
      path = my_strndup(name, i);
      tmp = name;
      if (!(name = my_strdup(name + i + 1)))
	return (NULL);
      free(tmp);
    }
  if (!path)
    return (NULL);
  if (path[0] == '\0')
    if (!my_free(path) && (path = my_strdup("/")) == NULL)
      return (NULL);
  return (path_completion_process(path, name, tab));
}

char		**command_completion(char **tab, char *cmd, char **path)
{
  DIR		*dir;
  struct dirent	*file;
  int	i;

  i = 0;
  while (path && path[i])
    {
      dir = opendir(path[i]);
      if (dir)
	{
	  while ((file = readdir(dir)) != NULL)
	    if (!cmd[0] || !my_strncmp(cmd, file->d_name, my_strlen(cmd) - 1))
	      if ((tab = add_one_choice(tab, file->d_name, 0)) == NULL)
		return (NULL);
	  if (closedir(dir) < 0)
	    {
	      msg_error("mysh: close error.\n");
	      return (NULL);
	    }
	}
      i = i + 1;
    }
  return (tab);
}

int		dynamic_completion(t_line *line, char **env)
{
  char		**tab;
  char		*word;

  if ((word = get_word(line->line, line->i)) == NULL)
    return (-1);
  if (my_word_iscmd(line->line, line->i))
    {
      tab = alias_completion(word, env);
      tab = command_completion(tab, word, get_path(NULL));
    }
  else
    tab = path_completion(word);
  if (!tab)
    return (-1);
  if (my_tablen(tab) == 0)
    return (0);
  if (my_tablen(tab) == 1)
    return (complete_line(line, tab));
  if (my_tablen(tab) > 100)
    if (check_before_display(tab))
      return (0);
  if (is_line_half_completed(line, tab))
    return (half_complete_line(line, tab));
  display_choice_tab(tab, line);
  return (0);
}
