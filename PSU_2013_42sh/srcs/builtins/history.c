/*
** history.c for 42sh in /home/decomb_s/rendu/PSU_2013_minishell2/42sh
** 
** Made by Sylvain Decombe
** Login   <decomb_s@epitech.net>
** 
** Started on  Wed May  7 11:03:27 2014 Sylvain Decombe
** Last update Thu May 29 17:30:05 2014 menich_a
*/

#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mysh.h"
#include "my.h"

char		*get_history_path(char **env)
{
  static char	*path = NULL;
  char		*tmp;

  if (path == NULL)
    {
      if (env == NULL)
	return (NULL);
      tmp = my_find_in_env(env, "PWD");
      if ((path = malloc(sizeof(char) * (my_strlen(tmp) + 13))) == NULL)
	{
	  msg_error("mysh: error: malloc failed.\n");
	  return (NULL + 1);
	}
      my_strcpy(path, tmp);
      if (path[my_strlen(path) - 1] == '\n')
	path[my_strlen(path) - 1] = '\0';
      my_strcat(path, "/");
      my_strcat(path, ".my_history");
    }
  return (path);
}

char		**get_history(void)
{
  int		i;
  int		fd;
  char		*buff;
  char		**tab;

  if ((buff = get_history_path(0)) == NULL + 1)
    return (NULL + 1);
  if (buff == NULL)
    return (NULL + 1);
  if ((fd = open(buff, O_RDONLY)) < 0)
    return (NULL);
  i = get_file_size(fd);
  if ((tab = malloc(sizeof(*tab) * (i + 1))) == NULL || close(fd) < 0 ||
      (buff = get_history_path(0)) == NULL || (fd = open(buff, O_RDONLY)) < 0)
    return (NULL);
  i = 0;
  while ((buff = fget_next_line(fd)) != NULL)
    tab[i++] = buff;
  if (close(fd) < 0)
    return (NULL);
  tab[i] = NULL;
  return (tab);
}

char		**display_history(char **cmd, char **env)
{
  int		line;
  char		**history;

  history = get_history();
  if (history == NULL)
    return (NULL);
  if (history == NULL + 1)
    return (NULL + 1);
  line = 0;
  if (cmd[1])
    line = my_tablen(history) - my_getnbr(cmd[1]);
  if (line >= 0 && line < my_tablen(history))
    while (history[line])
      {
	my_putchar(' ');
	my_put_nbr(line + 1);
	my_putchar('\t');
	my_putstr(history[line]);
	my_putchar('\n');
	line = line + 1;
      }
  my_free_tab(history);
  return (env);
}

int		my_put_hist(char *cmd, char **env)
{
  int		fd;
  char		*path;

  path = get_history_path(env);
  if (path == NULL + 1)
    return (-1);
  if (path == NULL)
    return (0);
  if ((fd = open(path, O_WRONLY | O_APPEND | O_CREAT,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    {
      warn("open error: %s", path);
      return (-1);
    }
  write(fd, cmd, my_strlen(cmd));
  write(fd, "\n", 1);
  if (close(fd) == -1)
    {
      warn("close error: %d", fd);
      return (-1);
    }
  return (0);
}

int		my_history(char *cmd, char **env, int action)
{
  char		*path;

  if (action == 0)
    return (my_put_hist(cmd, env));
  path = get_history_path(NULL);
  if (path == NULL + 1)
    return (-1);
  if (!path)
    return (0);
  return (my_remove(env, path));
}
