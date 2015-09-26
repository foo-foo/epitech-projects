/*
** setenv.c for minishell1 in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Dec 26 16:55:25 2013 menich_a
** Last update Sun May 25 21:24:46 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "mysh.h"
#include "my.h"

/*
**	Returns a new var with env syntax ("NAME=VALUE"): "AV[0]=AV[1]".
*/
char	*modificate_value(char **cmd, int size)
{
  char	*var;

  if (cmd[2] == NULL)
    var = malloc(sizeof(*var) * (size + 2));
  else
    var = malloc(sizeof(*var) * (size + my_strlen(cmd[2]) + 2));
  if (var == NULL)
    {
      msg_error("mysh: error: malloc failed.\n");
      return (NULL);
    }
  my_strcpy(var, cmd[1]);
  my_strcat(var, "=");
  if (cmd[2] != NULL)
    my_strcat(var, cmd[2]);
  return (var);
}

/*
**	Returns a ptr on a new env with ENV[i]=AV[1]'s value modificated. 
*/
char	**overwrite_var(char **env, char **cmd)
{
  int	i;
  int	size;
  char	**new_env;

  i = -1;
  size = my_strlen(cmd[1]);
  if ((new_env = malloc(sizeof(*new_env) * (my_tablen(env) + 1))) == NULL)
    {
      msg_error("mysh: setenv: command failed\n");
      return (env);
    }
  while (env[++i] && my_strncmp(cmd[1], env[i], size - 1))
    new_env[i] = env[i];
  if (env[i] != NULL)
    {
      free(env[i]);
      if ((new_env[i] = modificate_value(cmd, size)) == NULL)
	return (NULL);
      while (env[++i] != NULL)
	new_env[i] = env[i];
    }
  new_env[i] = NULL;
  free(env);
  return (new_env);
}

/*
**	Wait that user tape "y", or "n" to continue / cancel command.
*/
int	check_overwrite(char **cmd, char **env)
{
  char	buff[BUFF_SIZE + 1];
  int	ret;

  if (init_termios(env))
    return (0);
  my_putstr("mysh: setenv: ");
  my_putstr(cmd[1]);
  my_putstr(" already exist: do you really want to overwrite ");
  my_putstr(cmd[1]);
  my_putstr(" ? (y or n)\n");
  while ((ret = read(0, buff, BUFF_SIZE)) > 0)
    if (buff[0] == 'y' || buff[0] == 'n')
      break;
  if (ret == 0)
    return (0);
  if (ret < 0)
    return (msg_error("mysh: read error.\n"));
  if (buff[0] == 'n')
    return (1);
  init_termios(NULL);
  return (0);
}

/*
**	Init var with env syntax ("NAME=VALUE"): "AV[0]=AV[1]".
**	Returns an env cpy containing this var at the end.
*/
char	**add_new_var(char **cmd, char **env, int size)
{
  char	**new_env;
  char	*var;

  new_env = malloc(sizeof(*new_env) * (my_tablen(env) + 2));
  if (cmd[2] != NULL)
    var = malloc(sizeof(*var) * (size + my_strlen(cmd[2]) + 2));
  else
    var = malloc(sizeof(*var) * (size + 2));
  if (var == NULL || new_env == NULL)
    {
      msg_error("mysh: setenv: command failed\n");
      return (NULL);
    }
  my_strcpy(var, cmd[1]);
  my_strcat(var, "=");
  if (cmd[2] != NULL)
    my_strcat(var, cmd[2]);
  if (my_tabcpy(new_env, env) == NULL)
    return (NULL);
  if ((new_env[my_tablen(env)] = my_strdup(var)) == NULL)
    return (NULL);
  new_env[my_tablen(env) + 1] = NULL;
  my_free_tab(env);
  free(var);
  return (new_env);
}

/*
**	If specified var (av[1]) allready exists =>
**		- check_overwrite (overwrite confirmation message).
**		- overwrite_var (change old value with new value).
**	Else => add_new_var (create a new env with new variable).
*/
char	**my_setenv(char **cmd, char **env)
{
  int	size;

  size = my_strlen(cmd[1]);
  if (cmd[0] == NULL || cmd[1] == NULL)
    {
      msg_error("mysh: setenv: usage: setenv [NAME] [VALUE]\n");
      return (NULL + 1);
    }
  else if (cmd[1] != NULL && my_find_in_env(env, cmd[1]) != NULL)
    {
      size = check_overwrite(cmd, cmd);
      if (size == FAILURE)
	return (NULL + 1);
      else if (size == SUCCESS)
	env = overwrite_var(env, cmd);
      else
	return (msg_error_return("mysh: setenv: command canceled\n", NULL + 1));
    }
  else if (env && cmd[1] && my_find_in_env(env, cmd[1]) == NULL)
    env = add_new_var(cmd, env, size);
  return (env);
}
