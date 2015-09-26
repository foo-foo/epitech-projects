/*
** magic_quotes.c for  in /home/bencha_a/rendu/mamamia/PSU_2013_minishell2/srcs/builtins
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri May  9 20:44:13 2014 bencharif
** Last update Sun May 25 23:37:37 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "mysh.h"
#include "my.h"

char	**read_magic_cmd(char **env)
{
  int	fd;
  char	*tmp;
  char	*buff;
  char	**magic_cmd;

  if ((tmp = my_strdup("")) == NULL)
    return (NULL);
  if ((fd = open(".mysh_tmp", O_RDONLY)) == FAILURE)
    return (NULL);
  while ((buff = fget_next_line(fd)) != NULL)
    {
      if (tmp[0])
	if ((tmp = my_strcatdup(tmp, my_strdup(" "))) == NULL)
	  return (NULL);
      if ((tmp = my_strcatdup(tmp, buff)) == NULL)
	return (NULL);
    }
  if (close(fd) < 0 || my_remove(env, ".mysh_tmp"))
    return (NULL);
  if ((magic_cmd = my_str_to_wordtab(tmp)) == NULL)
    return (NULL);
  free(tmp);
  return (magic_cmd);
}

void	ret_magic_cmd_process(char **cmd, char **m_cmd, char **magic_cmd, int i)
{
  int	j;
  int	save;

  j = 0;
  save = i;
  while (save < i + 3)
    {
      free(cmd[save]);
      save = save + 1;
    }
  while (magic_cmd[j] != NULL)
    {
      m_cmd[i] = magic_cmd[j];
      i = i + 1;
      j = j + 1;
    }
  while (cmd[save] != NULL)
    {
      m_cmd[i] = cmd[save];
      i = i + 1;
      save = save + 1;
    }
  m_cmd[i] = NULL;
}

char	**ret_magic_cmd(char **cmd, char **env)
{
  char	**magic_cmd;
  char	**m_cmd;
  int	i;

  i = 0;
  if ((magic_cmd = read_magic_cmd(env)) == NULL)
    return (NULL);
  m_cmd = malloc((my_tablen(magic_cmd) + my_tablen(cmd) - 2) * sizeof(char*));
  if (m_cmd == NULL)
    return (NULL);
  while (cmd[i] && (cmd[i][0] != MAGIC_QUOTE || cmd[i][1]))
    {
      m_cmd[i] = cmd[i];
      i = i + 1;
    }
  if (!cmd[i])
    return (NULL);
  ret_magic_cmd_process(cmd, m_cmd, magic_cmd, i);
  free(magic_cmd);
  free(cmd);
  return (m_cmd);
}

char	**clean_cmd(char **cmd, int index)
{
  char	**clean_cmd;
  int	i;

  i = 0;
  clean_cmd = malloc(sizeof(*clean_cmd) * (my_tablen(cmd) - 2));
  if (clean_cmd == NULL)
    return (NULL);
  while (cmd[i] && i < index)
    {
      clean_cmd[i] = cmd[i];
      i = i + 1;
    }
  my_free(cmd[i]);
  my_free(cmd[i + 1]);
  my_free(cmd[i + 2]);
  i = i + 3;
  while (cmd[i])
    {
      clean_cmd[i - 3] = cmd[i];
      i = i + 1;
    }
  clean_cmd[i - 3] = NULL;
  free(cmd);
  return (clean_cmd);
}

char	**get_magic_quotes(char **cmd, char ***env_cpy)
{
  int	i;
  char	**env;
  char	*redirection;

  i = 0;
  env = *env_cpy;
  while (cmd[i])
    {
      while (cmd[i] && (cmd[i][0] != MAGIC_QUOTE || cmd[i][1]))
	i = i + 1;
      if (cmd[i])
	{
	  if (cmd[i + 1][0] == '\0')
	    return (clean_cmd(cmd, i));
	  if (!(redirection = my_str_catdup(cmd[i + 1], " > .mysh_tmp")))
	    return (NULL);
	  if (!(env = launch_cmd(redirection, env, 0)) || env == NULL + 1)
	    return (env);
	  if ((cmd = ret_magic_cmd(cmd, env)) == NULL)
	    return (NULL);
	  i = 0;
	}
    }
  *env_cpy = env;
  return (cmd);
}
