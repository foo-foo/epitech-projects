/*
** my_syntax.c for mysh in /home/menich_a/rendu/PSU_2013_minishell2/sources/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 25 12:13:05 2014 menich_a
** Last update Sun Jun  1 12:09:32 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

int	my_syntax(char *cmd, int i, char *to_check, int nb_max)
{
  int	check;

  check = 0;
  if (i == FAILURE)
    return (FAILURE);
  while (check <= nb_max && cmd[i] == to_check[0])
    {
      check = check + 1;
      i = i + 1;
    }
  if (check > 0 &&
      (check > nb_max || cmd[i] == to_check[1] || !cmd[i]))
    {
      msg_error("mysh: syntax error near unexpected `");
      if (cmd[i - 1] == '\n' || cmd[i - 1] == '\0')
        msg_error("newline");
      else
	write(2, &cmd[i - 1], 1);
      msg_error("' token\n");
      return (FAILURE);
    }
  return (i);
}

int	check_brackets_syntax(char *cmd)
{
  int	i;

  i = 0;
  while (cmd[i])
    {
      i = get_open_bracket(cmd, i);
      if (!cmd[i])
	return (0);
      if (cmd[i] == ')')
	return (msg_error("mysh: syntax error near unexpected `)' token.\n"));
      if (cmd[i] == '(' && (i == 0 || (i > 0 && cmd[i - 1] != ' ')))
	if ((i = get_close_bracket(cmd, i, 1)) < 0)
	  return (-1);
      if (cmd[i])
	i = i + 1;
    }
  return (0);
}

int	rev_redirection_syntax(char *buff, int index, char **env)
{
  int  i;
  char	red;
  char	**cmd;

  red = '>';
  i = index;
  if (buff[i] == '>')
    red = '<';
  while (buff[i] == buff[index])
    i = i + 1;
  if (i - index <= 2 && buff[i] != '|' && buff[i] != ';' &&
      buff[i] != '&' && buff[i] != red)
    {
      cmd = buff_to_cmdtab(buff, env);
      if (cmd == NULL)
	return (-1);
      if (cmd[0] && cmd[1] && cmd[2])
	if (cmd[2][0] != PIPE && cmd[2][0] != AND)
	  return (0);
    }
  msg_error("mysh: Syntax error near unexpected `");
  write(2, &buff[index], 1);
  return (msg_error("' token\n"));
}

int	init_check_syntax(char *cmd, int *index, char **env)
{
  int	i;

  i = 0;
  *index = 0;
  while (cmd[i] == ' ')
    i = i + 1;
  if (cmd[0] == '\0')
    return (-1);
  if (!my_str_isprintable(cmd))
    return (msg_error("command nor found.\n"));
  if (cmd[i] == '<' || cmd[i] == '>')
    if (rev_redirection_syntax(cmd, i, env))
      return (-1);
  return (0);
}

int	my_check_syntax(char *cmd, char **env)
{
  int	i;

  if (init_check_syntax(cmd, &i, env))
    return (-1);
  if (!(cmd = my_remove_spaces(cmd)))
    return (msg_error("command nor found.\n"));
  if (check_brackets_syntax(cmd))
    return (FAILURE);
  if (cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '&')
    {
      msg_error("mysh: syntax error near unexpected token `");
      write(2, &cmd[i], 1);
      return (msg_error("'\n"));
    }
  while (i != FAILURE && cmd[i])
    {
      i = my_syntax(cmd, i, "<>", 2);
      i = my_syntax(cmd, i, "><", 2);
      i = my_syntax(cmd, i, "|&", 2);
      if ((i = my_syntax(cmd, i, "&|", 2)) != FAILURE && cmd[i])
        i = i + 1;
    }
  free(cmd);
  return (i);
}
