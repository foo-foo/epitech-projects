/*
** tools.c for 42sh in /home/menich_a/rendu/PSU_2013_42sh
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May 29 12:08:33 2014 menich_a
** Last update Sun Jun  1 20:31:09 2014 menich_a
*/

#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include "alias.h"
#include "mysh.h"
#include "my.h"

/*
**		Inits a clean cmd tab from the buff previously read.
**		buff_to_cmdtab => cmd tab + syntax checked.
**		Replaces local vars by there values.
**		Replaces in-brackets expression by it translation.
**		Replaces globing expression '*' by it translation.
**		Replaces magic-quoted expression by it translation.
*/
char		**get_clean_cmd(char *buff, char ***env_cpy, int check)
{
  char		**cmd;
  char		**env;

  env = *env_cpy;
  if ((cmd = buff_to_cmdtab(buff, env)) == NULL)
    return (NULL);
  if (cmd == NULL + 1 || cmd[0] == NULL)
    return (NULL + 1);
  if (check && cmd[0][0] != '!')
    if (my_history(buff, env, 0))
      return (NULL);
  if (set_local(cmd, env, get_local_var(0)) == FAILURE)
    return (NULL);
  if (check_brackets(cmd) > 0)
    if ((cmd = exec_brackets(cmd)) == NULL)
      return (NULL);
  if (my_find_in_tab(cmd, '*') >= 0)
    if (!(cmd = get_globing_datas(cmd, 0, 0)))
      return (cmd);
  if (cmd == NULL + 1 || cmd[0] == NULL)
    return (NULL + 1);
  if (check_magic_quote(cmd) == SUCCESS)
    cmd = get_magic_quotes(cmd, &env);
  *env_cpy = env;
  return (cmd);
}

int		get_close_bracket(char *cmd, int i, int brackets)
{
  char		c;

  while (cmd[++i] && brackets)
    {
      if (cmd[i] == '(')
        brackets = brackets + 1;
      if (cmd[i] == ')' && cmd[i - 1] == '(')
	return (msg_error("mysh: syntax error near unexpected `(' token.\n"));
      if (cmd[i] == ')')
        brackets = brackets - 1;
      if ((c = cmd[i]) == '"' || c == '\'')
        {
          while (cmd[++i] && cmd[i] != c)
            if (cmd[i] == '\\' && cmd[i + 1] == c)
              i = i + 1;
          if (cmd[i])
            i = i + 1;
        }
      if (cmd[i] == '\\' && (cmd[i + 1] == '(' || cmd[i + 1] == ')' ||
                             cmd[i + 1] == '"' || cmd[i + 1] == '\''))
        i = i + 1;
    }
  if (brackets)
    return (msg_error("mysh: syntax error near unexpected `(' token.\n"));
  return (i);
}

int		get_open_bracket(char *cmd, int i)
{
  char		c;

  while (cmd[i] && cmd[i] != '(' && cmd[i] != ')' &&
         cmd[i] != '"' && cmd[i] != '\'')
    if (cmd[i++] == '\\' && (cmd[i] == '(' || cmd[i] == ')' ||
                             cmd[i] == '"' || cmd[i] == '\''))
      i = i + 1;
  if (cmd[i] == '"' || cmd[i] == '\'')
    {
      c = cmd[i];
      while (cmd[++i] && cmd[i] != c)
        if (cmd[i] == '\\' && cmd[i + 1] == c)
          i = i + 1;
      if (cmd[i])
        i = i + 1;
    }
  return (i);
}

void		jump_some_spaces(char *buff, int *tild, int *index, int action)
{
  int		i;

  i = *index;
  if (action == 1)
    while (buff[i] == ' ')
      i = i + 1;
  else
    {
      *tild = 0;
      while (buff[i] == ' ')
        i = i + 1;
      if (buff[i] == '~')
        *tild = 1;
    }
  *index = i;
}

char		*get_tild(char *str, char **env)
{
  int		i;
  char		*tild;
  char		*path;
  struct passwd	*check;

  i = 0;
  while (str[i] && str[i] != '/')
    i++;
  if ((tild = my_strndup(str, i)) == NULL)
    return (NULL);
  if (my_strlen(tild) == 1)
    {
      path = my_find_in_env(env, "HOME");
      if (!path)
	return (str);
      return (my_str_catdup(path, str + i));
    }
  setpwent();
  while ((check = getpwent()) != NULL)
    if (my_strcmp(check->pw_name, tild + 1) == 0)
      break;
  endpwent();
  if (check)
    return (my_str_catdup(check->pw_dir, str + i));
  return (str);
}