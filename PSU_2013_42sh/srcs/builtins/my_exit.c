/*
** my_exit.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May 15 19:58:19 2014 menich_a
** Last update Sun May 25 13:12:00 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

/*                                                                                                                 
**	Free old_env then copy av in env. Like this, `launch_builtins' \
**	will free av and `mysh' will break the loop (env[0] = "exit").
*/
char	**my_exit(char **av, char **env)
{
  if (my_history(0, env, 1))
    return (NULL);
  my_free_tab(env);
  my_free_tab(get_path(NULL));
  my_free(get_history_path(NULL));
  if (av)
    {
      env = my_tabdup(av);
      if (!env)
        return (msg_error_return("mysh: error: malloc failed.\n", 0));
    }
  else
    {
      env = malloc(sizeof(*env) * 2);
      if (!env)
        return (msg_error_return("mysh: error: malloc failed.\n", 0));
      if ((env[0] = my_strdup("exit")) == NULL)
	return (NULL);
      env[1] = NULL;
    }
  return (env);
}
