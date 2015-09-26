/*
** last_history_cmd.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue May 20 11:14:08 2014 menich_a
** Last update Sun Jun  1 12:13:52 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

int		init_substitute_index(char *sub, int *index1, int *index2)
{
  int		i;
  int		j;

  i = 0;
  while (sub[i] && sub[i] != '/')
    i = i + 1;
  if (!sub[i++] && msg_error("mysh: substitution failed.\n"))
    return (-1);
  j = i;
  while (sub[j] && sub[j] != '/')
    j = j + 1;
  if ((!sub[j] || !sub[j + 1]) && msg_error("mysh: substitution failed.\n"))
    return (1);
  *index1 = i;
  *index2 = j;
  return (0);
}

int		substitute(char **cmd, char *sub)
{
  int		i;
  int		j;
  char		*to_replace;
  char		*replace;

  if (init_substitute_index(sub, &i, &j))
    return (1);
  to_replace = my_strndup(sub + i, j - i);
  replace = my_strdup(sub + j + 1);
  if (!to_replace || !replace)
    return (msg_error("mysh: error: malloc failed.\n"));
  i = 0;
  while (cmd[i] && (j = hidenp(cmd[i], to_replace)) < 0)
    i = i + 1;
  if (!cmd[i] && msg_error("mysh: substitution failed.\n"))
    return (0);
  free(sub);
  if (!(sub = my_strndup(cmd[i], j)) || !(sub = my_strcatdup(sub, replace)) ||
      !(sub = my_strcatdup(sub, my_strdup(cmd[i] + j + my_strlen(to_replace)))))
    return (-1);
  free(cmd[i]);
  cmd[i] = sub;
  return (0);
}

char		**add_last_cmd_failure(int ret)
{
  if (ret == 1)
    return (NULL + 1);
  return (NULL);
}

char		**add_last_cmd(char **cmd, char **lastcmd, char *substitution)
{
  char		**new;
  int		i;
  int		j;

  if (substitution)
    if ((i = substitute(lastcmd, substitution)) != 0)
      return (add_last_cmd_failure(i));
  j = 1;
  i = -1;
  if ((new = malloc(sizeof(*new) * (my_tablen(cmd) + my_tablen(lastcmd)))) == 0)
    return (NULL);
  while (lastcmd && lastcmd[++i])
    new[i] = lastcmd[i];
  if (lastcmd)
    free(lastcmd);
  if (cmd)
    {
      free(cmd[0]);
      while (cmd[j])
	new[i++] = cmd[j++];
      free(cmd);
    }
  new[i] = NULL;
  return (new);
}

char		**get_last_cmd(char **cmd, char *substitution, char **env)
{
  char		**htab;
  char		**last_cmd;
  int		i;

  if ((htab = get_history()) == NULL || htab == NULL + 1)
    return (htab);
  if ((i = hidenp(cmd[0], ":s/")) >= 0)
    if (!(substitution = my_strdup(cmd[0] + i)) || (cmd[0][i] = '\0'))
      return (NULL);
  if ((i = my_tablen(htab) - 1) >= 0 && my_strcmp(cmd[0], "!!"))
    {
      if ((cmd[0][1] != '-' || cmd[0][2] < '0' || cmd[0][2] > '9') &&
	  (cmd[0][1] < '0' || cmd[0][1] > '9'))
	while (i >= 0 && my_strncmp(htab[i], cmd[0] + 1, my_strlen(cmd[0]) - 2))
	  i = i - 1;
      else
	if ((i = my_getnbr(cmd[0] + 1) - 1) < 0)
	  i = my_tablen(htab) + i + 1;
    }
  if (i >= my_tablen(htab) || i < 0)
    return (NULL + 1);
  if ((!(last_cmd = buff_to_cmdtab(htab[i], env)) ||
       last_cmd == NULL + 1) && !my_free_tab(htab))
    return (last_cmd);
  return (add_last_cmd(cmd, last_cmd, substitution));
}
