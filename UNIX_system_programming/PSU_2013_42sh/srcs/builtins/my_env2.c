/*
** my_env2.c for  in /home/menich_a/rendu/PSU_2013_42sh/srcs/builtins
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun  1 17:44:06 2014 menich_a
** Last update Sun Jun  1 20:39:20 2014 menich_a
*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "mysh.h"
#include "my.h"

char	**set_env_option(char **av, char **env, int *index)
{
  char	**tmp;
  int	i;

  i = *index;
  tmp = malloc(sizeof(*tmp) * 4);
  if (!tmp)
    return (msg_error_return("mysh: error: malloc failed.\n", 0));
  tmp[0] = my_strdup("setenv");
  tmp[1] = my_strndup(av[i], my_find_in_str(av[i], '='));
  tmp[2] = my_strdup(av[i] + my_find_in_str(av[i], '=') + 1);
  tmp[3] = NULL;
  if (!tmp[0] || !tmp[1] || !tmp[2] || !(env = my_setenv(tmp, env)))
    return (NULL);
  if (env == NULL + 1)
    {
      if (!(env = malloc(sizeof(*env) * 1)))
	return (msg_error_return("mysh: error: malloc failed.\n", 0));
      env[0] = NULL;
    }
  tmp = my_free_tab(tmp);
  i = i + 1;
  *index = i;
  return (env);
}

char	**cut_env_cmd(char **av, int *index, int *index2)
{
  char	**tmp;
  int	i;
  int	j;

  i = *index;
  j = *index2;
  while (av[i] && av[i][0] != PIPE && av[i][0] != AND)
    i = i + 1;
  tmp = malloc(sizeof(*tmp) * (1 + i - j));
  if (!tmp)
    return (msg_error_return("mysh: error: malloc failed.\n", 0));
  i = 0;
  while (av[j] && av[j][0] != PIPE && av[j][0] != AND)
    {
      tmp[i] = my_strdup(av[j]);
      if (!tmp[i])
        return (NULL);
      i = i + 1;
      j = j + 1;
    }
  *index = i;
  *index2 = j;
  tmp[i] = NULL;
  return (tmp);
}

int	printenv_option(char **env)
{
  char	**tmp;

  tmp = malloc(sizeof(*tmp) * 2);
  if (!tmp)
    return (msg_error("mysh: error: malloc failed.\n"));
  tmp[0] = my_strdup("env");
  tmp[1] = NULL;
  if (!tmp[0])
    return (-1);
  my_printenv(tmp, env, 0);
  tmp = my_free_tab(tmp);
  env = my_free_tab(env);
  return (0);
}

char	**unset_env_option(char **env, int i, char **av)
{
  char	**tmp;

  tmp = malloc(sizeof(*tmp) * 3);
  if (!tmp)
    return (msg_error_return("mysh: error: malloc failed.\n", 0));
  tmp[0] = my_strdup("unsetenv");
  tmp[1] = my_strdup(av[i]);
  tmp[2] = NULL;
  if (!tmp[0] || !tmp[1] || !(env = my_unsetenv(tmp, env)))
    return (NULL);
  if (env == NULL + 1)
    {
      if (!(env = malloc(sizeof(*env) * 1)))
	return (msg_error_return("mysh: error: malloc failed.\n", 0));
      env[0] = NULL;
    }
  tmp = my_free_tab(tmp);
  return (env);
}

int	launch_options_process(char **path, char **env, char **av, int i)
{
  int	j;
  char	**tmp;
  char	*cmd_path;

  while (av[i] && my_find_in_str(av[i], '=') != -1)
    if ((env = set_env_option(av, env, &i)) == NULL)
      return (-1);
  if (!av[i])
    return (printenv_option(env));
  j = i;
  if ((tmp = cut_env_cmd(av, &i, &j)) == NULL)
    return (-1);
  if (!path || !(cmd_path = get_cmd_path(tmp[0], path)))
    return (0);
  my_free(tmp[0]);
  tmp[0] = cmd_path;
  env = launch_appropriate_cmd(tmp, env);
  if (!env)
    return (-1);
  if (env != NULL + 1)
    my_free_tab(env);
  return (0);
}
