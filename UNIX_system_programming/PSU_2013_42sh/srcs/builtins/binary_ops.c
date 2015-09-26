/*
** binary_ops.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri May 16 19:44:17 2014 menich_a
** Last update Fri May 30 19:29:22 2014 menich_a
*/

#include <stdlib.h>
#include "mysh.h"
#include "my.h"

char	**cut_cmd(char **cmd, int i)
{
  char	**tmp;
  int	j;
  int	y;

  y = 0;
  j = i - 1;
  if (j < 0)
    return (NULL);
  while (j >= 0 && (cmd[j][0] != AND || cmd[j][1] != AND) &&
         (cmd[j][0] != PIPE || cmd[j][1] != PIPE))
    j = j - 1;
  tmp = malloc(sizeof(char *) * (i - j));
  if (tmp == NULL)
    return (NULL);
  j = j + 1;
  while (j < i && cmd[j])
    {
      tmp[y] = my_strdup(cmd[j]);
      if (tmp[y] == NULL)
        return (NULL);
      y = y + 1;
      j = j + 1;
    }
  tmp[y] = NULL;
  return (tmp);
}

char	**process_binary_ops(char **env, char **cmdline, int y)
{
  char	**cmd;
  char	**env_cpy;

  env_cpy = NULL;
  if (env && !(env_cpy = my_tabdup(env)))
    return (NULL);
  cmd = NULL;
  if (cmdline[y][0] == AND && cmdline[y][1] == AND && !cmdline[y][2])
    if ((cmd = cut_cmd(cmdline, y)) == NULL ||
        (env = execute_current_process(cmd, env)) == NULL + 1)
      return (NULL + 1);
  if (cmdline[y][0] == PIPE && cmdline[y][1] == PIPE && !cmdline[y][2])
    if ((cmd = cut_cmd(cmdline, y)) == NULL ||
	(env = execute_current_process(cmd, env)) != NULL + 1)
      return (NULL + 1);
  if (env == NULL + 1)
    return (env_cpy);
  my_free_tab(env_cpy);
  return (env);
}
