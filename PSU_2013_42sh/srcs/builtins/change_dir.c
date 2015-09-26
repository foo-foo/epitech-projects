/*
** change_dir.c for minishell1 in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Dec 19 15:21:11 2013 menich_a
** Last update Sun May 25 23:38:52 2014 menich_a
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

char		*find_new_pwd(char **env)
{
  char		*pwd;
  int		pid;
  char		**cmd;
  int		fd[2];

  if (!env || pipe(fd) == FAILURE || (pid = fork()) == FAILURE)
    return (NULL);
  if (pid == 0)
    {
      if (!(cmd = malloc(sizeof(*cmd) * 2)) || !(cmd[0] = my_strdup("pwd")))
	exit(msg_error("mysh: error: malloc failed.\n"));
      cmd[1] = NULL;
      if (dup2(fd[1], 1) == FAILURE)
	exit(msg_error("mysh: duplication error.\n"));
      execve("/usr/bin/pwd", cmd, env);
      exit(msg_error("mysh: execution error: last command failed\n"));
    }
  if (wait(0) == FAILURE)
    return (msg_error_ret("mysh: wait error.\n"));
  pwd = fget_next_line(fd[0]);
  if (check_error(fd))
    return (NULL);
  return (pwd);
}

/*
**		Adapt PWD and OLDPWD in env.
*/
char		**adapt_pwd_process(char **env, char **cmd, char *pwd)
{
  free(cmd[1]);
  cmd[1] = my_strdup("OLDPWD");
  if (cmd[1] == NULL)
    return (NULL);
  if (pwd)
    {
      free(cmd[2]);
      cmd[2] = pwd;
    }
  else
    free(pwd);
  cmd[3] = NULL;
  if (my_find_in_env(env, "OLDPWD"))
    env = overwrite_var(env, cmd);
  else
    env = add_new_var(cmd, env, 6);
  my_free_tab(cmd);
  return (env);
}

char		**adapt_pwd(char **env, char *home)
{
  char		**cmd;
  char		*pwd;

  cmd = malloc(sizeof(*cmd) * 4);
  if (cmd == NULL)
    return (NULL);
  cmd[0] = my_strdup("setenv");
  cmd[1] = my_strdup("PWD");
  if (home == NULL)
    cmd[2] = find_new_pwd(env);
  else
    cmd[2] = my_strdup(home);
  cmd[3] = NULL;
  if (!cmd[0] || !cmd[1] || !cmd[2])
    return (NULL);
  if ((pwd = my_find_in_env(env, "PWD")) != NULL)
    {
      if ((pwd = my_strdup(my_find_in_env(env, "PWD"))) == NULL ||
	  (env = overwrite_var(env, cmd)) == NULL)
	return (NULL);
    }
  else
    if ((env = add_new_var(cmd, env, 3)) == NULL)
      return (NULL);
  return (adapt_pwd_process(env, cmd, pwd));
}

/*
**		chdir HOME / chdir OLDPWD for cd ~ or cd -
*/
char		*my_cd_options(char **env, char *arg)
{
  char		*var;
  char		*home;

  var = "HOME";
  if (arg && arg[0] == '-')
    var = "OLDPWD";
  if (*env == NULL || (home = my_find_in_env(env, var)) == NULL)
    {
      msg_error("mysh: cd: ");
      msg_error(var);
      msg_error(" not set.\n");
      return (NULL + 1);
    }
  if ((home = my_strdup(home)) == NULL)
    return (NULL);
  if (my_strcmp(var, "HOME"))
    {
      my_putstr(home);
      my_putchar('\n');
    }
  if (chdir(home) == FAILURE && my_perror(home, 0))
    return (NULL + 1);
  return (home);
}

/*
**		chdir av[1] if it's not NULL. Else my_cd_options.
*/
char		**my_change_dir(char **av, char **env)
{
  char		*home;

  home = NULL;
  if (!av[1] || !my_strcmp(av[1], "-"))
    {
      if ((home = my_cd_options(env, av[1])) == NULL)
	return (NULL);
      if (home == NULL + 1)
	return (NULL + 1);
    }
  else
    if (chdir(av[1]) == FAILURE && my_perror(av[1], 0))
      return (NULL + 1);
  env = adapt_pwd(env, home);
  if (home != NULL)
    free(home);
  return (env);
}
