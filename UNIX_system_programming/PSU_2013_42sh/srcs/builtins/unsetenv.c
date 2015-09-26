/*
** unsetenv.c for minishell1 in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Dec 26 16:58:03 2013 menich_a
** Last update Sat May 31 16:34:12 2014 menich_a
*/

#include <stdlib.h>
#include "mysh.h"
#include "my.h"

/*
**	Creates The new env not containing var.
*/
char    **remove_var(char **env, char *var)
{
  int   i;
  int   j;
  int   size;
  char  **new_env;

  i = 0;
  j = 0;
  size = my_strlen(var) - 1;
  new_env = malloc(sizeof(*new_env) * my_tablen(env));
  if (new_env == NULL)
    return (msg_error_return("mysh: unsetenv: malloc failed\n", 0));
  while (env[i] != NULL)
    {
      if (!my_strncmp(env[i], var, size) && env[i][size + 1] == '=')
        i = i + 1;
      if (env[i])
	if ((new_env[j++] = my_strdup(env[i++])) == NULL)
	  return (NULL);
    }
  new_env[j] = NULL;
  my_free_tab(env);
  return (new_env);
}

/*
**	Returns a ptr on a new env not containing var (av[1]).
*/
char    **my_unsetenv(char **av, char **env)
{
  int	i;

  i = 1;
  if (av[1] == NULL)
    return (msg_error_return("unsetenv: usage: unsetenv [NAME]\n", NULL + 1));
  while (av[i] != NULL)
    {
      if (my_find_in_env(env, av[i]) == NULL)
	{
	  msg_error("mysh: unsetenv: ");
	  msg_error(av[i]);
	  msg_error(": no such variable in environnement\n");
	  return (NULL + 1);
	}
      if ((env = remove_var(env, av[i])) == NULL)
	return (NULL);
      i = i + 1;
    }
  return (env);
}
