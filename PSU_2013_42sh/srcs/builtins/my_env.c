/*
** my_env.c for minishell1 in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan  3 11:40:40 2014 menich_a
** Last update Sun Jun  1 20:22:04 2014 menich_a
*/

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "mysh.h"
#include "my.h"

/*
**		Display environnement variable's value (av[1]'s value).
**		If av[1] is NULL: display the complete environnement.
*/
int		my_printenv(char **av, char **env, int i)
{
  char		*tmp;

  if (env && !my_strcmp(av[0], "printenv") && av[1])
    {
      tmp = my_find_in_env(env, av[1]);
      if (tmp)
	{
	  my_putstr(tmp);
	  my_putchar('\n');
	}
      return (0);
    }
  else if (env && (!av[1] || !my_strcmp(av[1], "-0")))
    {
      while (env[i])
        {
          my_putstr(env[i++]);
	  if (my_strcmp(av[1], "-0") || !env[i])
	    my_putchar('\n');
        }
      return (0);
    }
  return (1);
}

int		launch_options(char **av, char **env_cpy, char **path)
{
  int		i;
  char		**env;

  i = 0;
  if (!(env = my_tabdup(env_cpy)))
    return (-1);
  while (av[++i] && av[i][0] == '-')
    {
      if (!my_strcmp(av[i], "-i"))
        {
          if (!my_free_tab(env) && !(env = malloc(sizeof(*env) * 1)))
            return (msg_error("mysh: error: malloc failed.\n"));
          env[0] = NULL;
        }
      if (env && env[0] && !my_strcmp(av[i], "-u"))
        {
          if (!av[++i])
            if (!my_free_tab(env) && msg_error("env: option u need argument\n"))
              return (0);
          if (my_find_in_env(env, av[i]))
            if ((env = unset_env_option(env, i, av)) == NULL)
              return (-1);
        }
    }
  return (launch_options_process(path, env, av, i));
}

/*
**		Display env or execute a cmd in a modified env.
*/
char		**my_env(char **av, char **env)
{
  char		**path;
  char		*path_var;

  path_var = my_find_in_env(env, "PATH");
  if (path_var == NULL)
    path = NULL;
  else
    if ((path = my_path_to_tab(path_var)) == NULL)
      return (NULL);
  if (my_printenv(av, env, 0) == 0)
    return (env);
  if (launch_options(av, env, path))
    return (NULL);
  return (env);
}
