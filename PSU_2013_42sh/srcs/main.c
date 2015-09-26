/*
** main.c for minishell1 in /home/menich_a/rendu/PSU_2013_minishell1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Dec 12 12:21:21 2013 menich_a
** Last update Sat May 31 12:50:52 2014 menich_a
*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "mysh.h"
#include "my.h"

/*
**			Display an prompt elaborated prompt (HOST_NAME ~ NBR_LINES).
**			If getnextline launch display prompt with check2 == 1:
**			    => there is ';' => don't display next prompt.
*/
int			display_prompt(char **env, int check, int check2)
{
  static char		*host;
  static unsigned int	line;
  static int		validity;

  if (validity == 1)
    return (validity = 0);
  if (check2 == 1)
    return ((validity = 1) - 1);
  if (env)
    host = my_find_in_env(env, "HOST");
  if (check2 == 2)
    return (my_nbrlen(line) + my_strlen(host) + 6);
  if (check)
    line = line + 1;
  my_putstr("\033[32m");
  if (host)
    my_putstr(host);
  else
    my_putchar('$');
  my_putstr(" \033[33m~\033[31m ");
  my_put_nbr(line);
  my_putstr(" \033[0m> ");
  return (0);
}

/*
**			If action is not 0
**				 => ret takes value of exit param
**				 => free env
**			Else => conf init (for shubshell mode) + path init
*/
int			mysh_process(int action, int *ret, int *conf, char **env)
{
  int			tmp;

  if (action)
    {
      if (env && env[0])
	*ret = my_getnbr(env[1]);
      my_free_tab(env);
      return (0);
    }
  *ret = 1;
  *conf = 1;
  if (!access(SUBSHELL_MODE, F_OK))
    {
      if ((tmp = my_remove(env, SUBSHELL_MODE)))
	return (-1);
      *conf = 0;
    }
  my_free_tab(my_path_to_tab(my_find_in_env(env, "PATH")));
  return (0);
}

/*
**			Main function: creates a loop (only way to break it is exit / EOT (ctrl+D)).
**			Each loop turn:
**				- Display prompt (if the shell is not running as subshell).
**				- Read one command line (then check main syntax errors)
**				- Launch command
*/
int			mysh(char **env)
{
  int			ret;
  int			conf;
  char			**tmp;
  char			*buff;

  if (mysh_process(0, &ret, &conf, env) < 0)
    return (-1);
  while (my_strcmp(env[0], "exit") != SUCCESS)
    {
      if (conf)
	display_prompt(env, ret, 0);
      if ((buff = get_next_line(0, env)) == NULL)
	if ((buff = my_strdup("exit")) == NULL)
	  return (1);
      if ((ret = my_check_syntax(buff, env)) >= 0 &&
	  (tmp = launch_cmd(buff, env, conf)))
	if (tmp != NULL + 1)
	  env = tmp;
      if (ret >= 0 && tmp == NULL)
	return (msg_error("\n"));
      ret = my_strlen(buff);
      buff = my_free(buff);
    }
  mysh_process(1, &ret, &conf, env);
  return (ret);
}

/*
**			Creates an allocated copy of environnement.
**			Init signals SIGINT and SIGTSTP
**			Launch shell with an env copy.
*/
int			main(__attribute__((unused))int ac, 
			     __attribute__((unused))char **av, char **env)
{
  char			**new_env;
  char			*cd_init;

  if (BUFF_SIZE <= 0)
    return (msg_error("mysh: invalid read size.\n"));
  if (env == NULL || *env == NULL)
    {
      if ((new_env = malloc(sizeof(*new_env) * 1)) == NULL)
	return (msg_error("mysh: malloc failed: insufficient storage space.\n"));
      new_env[0] = NULL;
    }
  else
    if ((new_env = my_tabdup(env)) == NULL)
      return (1);
  if (signal(SIGTSTP, &my_sigstop) == SIG_ERR ||
      signal(SIGINT, &my_sigint) == SIG_ERR)
    return (1);
  if (!(cd_init = my_strdup(INIT_CD)) ||
      !(new_env = launch_cmd(cd_init, new_env, 0)))
    return (1);
  free(cd_init);
  return (mysh(new_env));
}
