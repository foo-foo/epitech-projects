/*
** my_remove.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed May 21 11:52:10 2014 menich_a
** Last update Sat May 31 14:12:45 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

int	my_remove_ret(char **cmd, char **env, int check)
{
  int	ret;

  if (!cmd[0] || !cmd[1])
    return (msg_error("mysh: error: malloc failed.\n"));
  if ((ret = launch_exec_cmd(cmd, env)))
    return (ret);
  if (check)
    my_free_tab(env);
  return (0);
}

/*
**	Execute an rm of `file'
*/
int	my_remove(char **env, char *file)
{
  char	**cmd;
  int	check;

  check = 0;
  if (access(file, F_OK) < 0)
    return (0);
  if (my_find_in_env(env, "PATH") == NULL)
    {
      check = 1;
      if (!(env = malloc(sizeof(*env) * 2)) ||
	  !(env[0] = my_strdup("PATH=/usr/bin")))
	return (msg_error("mysh: error: malloc failed.\n"));
      env[1] = NULL;
    }
  cmd = malloc(sizeof(*cmd) * 3);
  if (cmd == NULL)
    return (msg_error("mysh: error: malloc failed.\n"));
  cmd[0] = my_strdup("rm");
  cmd[1] = my_strdup(file);
  cmd[2] = NULL;
  return (my_remove_ret(cmd, env, check));
}
