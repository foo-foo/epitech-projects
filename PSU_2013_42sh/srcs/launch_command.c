/*
** launch_command.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri May 16 19:39:19 2014 menich_a
** Last update Sun Jun  1 20:02:58 2014 menich_a
*/

#include <stdlib.h>
#include "alias.h"
#include "mysh.h"
#include "my.h"

/*
**		Init a t_builtin tab (builtin name - builtin fonction ptr).
**		If cmd is a builtin:
**			=> launch builtin fonction ptr.
**
**		Else	=> returns NULL + 2 (to launch a path cmd).
*/
char		**launch_builtins(char **cmd, char **env)
{
  t_builtin	builtins[13];
  int		i;

  i = 0;
  init_builtins_tab(builtins);
  while (i < 13 && my_strcmp(builtins[i].name, cmd[0]))
    i = i + 1;
  if (i == 13)
    return (NULL + 2);
  env = builtins[i].fptr(cmd, env);
  get_fd(0, 1, 2);
  if (env != NULL + 1)
    my_free_tab(cmd);
  return (env);
}

/*
**		If an alias is found in the command:
**			=> set_alias (alias replacement)
**		If command begins with a '!':
**			=> get_last_cmd (replace cmd by last cmd).
**		If launch_builtins returns NULL + 2
**			=> launch_exec_cmd (search then execute a path_cmd).
*/
char		**launch_appropriate_cmd(char **cmd, char **env)
{
  char		**tmp;
  int		ret;

  cmd = set_alias(cmd, get_alias(0, 0, 0, env));
  if (cmd == NULL)
    return (NULL);
  if (cmd[0] == NULL)
    return (NULL + 1);
  if (cmd[0][0] == '!')
    if ((cmd = get_last_cmd(cmd, NULL, env)) == NULL || cmd == NULL + 1)
      return (cmd);
  if ((tmp = launch_builtins(cmd, env)) != NULL + 2)
    return (tmp);
  else
    if ((ret = launch_exec_cmd(cmd, env)) != 0)
      {
	if (ret < 0)
	  return (NULL);
	return (NULL + 1);
      }
  return (env);
}

/*
**		While some pipes are countained in command line:
**			=> exec_pipe_cmd
**		Then launch_appropriate_cmd (builtin / path cmd).
*/
char		**execute_current_process(char **cmd, char **env)
{
  int		i;
  int		pipes;
  char		**p_cmd;

  i = -1;
  pipes = 0;
  while (cmd[++i] != NULL)
    if (cmd[i][0] == PIPE && !cmd[i][1])
      pipes = pipes + 1;

  get_pipes(pipes, 0);
  while (pipes > 0)
    {
      if ((p_cmd = get_next_cmd(cmd, env, 0)) == NULL || p_cmd == NULL + 1)
	return (p_cmd);
      if ((env = exec_pipe_cmd(p_cmd, env)) == NULL || env == NULL + 1)
	return (env);
      pipes = pipes - 1;
    }
  if ((p_cmd = get_next_cmd(cmd, env, 0)) == NULL || p_cmd == NULL + 1)
    return (p_cmd);
  env = launch_appropriate_cmd(p_cmd, env);
  return (env);
}


/*
**		While some binary operators are countained in command line:
**			=> execute command bit by bit (proccess_binary_ops).
**		When there is no operator any more => execute_current_process.
*/
char		**execute_current_cmd(char **cmdline, char **env)
{
  char		**cmd;
  int		y;

  y = 0;
  while (cmdline[y])
    {
      if (!(env = process_binary_ops(env, cmdline, y)) || env == NULL + 1)
        return (env);
      y = y + 1;
    }
  if ((cmd = cut_cmd(cmdline, y)) == NULL)
    return (NULL);
  env = execute_current_process(cmd, env);
  my_free_tab(cmdline);
  return (env);
}

/*
**		Get a cmd tab initialized by get_clean_cmd.
**		Check if user cmd is a local var definition.
**		Else => execute_current_cmd.
*/
char		**launch_cmd(char *buff, char **env, int check)
{
  char		**cmd;
  int		y;

  get_fd(0, 1, 2);
  cmd = get_clean_cmd(buff, &env, check);
  if (cmd == NULL)
    return (NULL);
  if (cmd == NULL + 1 || cmd[0] == NULL)
    return (NULL + 1);
  if ((y = check_valid_local_var(buff)) == SUCCESS)
    {
      if (get_local_var(buff) == NULL)
        return (NULL);
      return (env);
    }
  if (y == FAILURE)
    return (NULL);
  return (execute_current_cmd(cmd, env));
}
