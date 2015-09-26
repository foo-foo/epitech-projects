/*
** tc_init.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Jan 14 12:25:41 2014 menich_a
** Last update Thu May 29 13:44:23 2014 menich_a
*/

#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include "my_termios.h"
#include "my.h"

/*
**			Initiate termcaps data base. If TERM environnement var is not set
**			=> initiate data base with "xterm" terminal name [enable by default]
*/
int			check_env(char **env)
{
  char			*t_name;
  char			*term;
  int			ret;

  t_name = NULL;
  if (env && env[0])
    {
      term = my_find_in_env(env, "TERM");
      if (term && (t_name = my_strdup(term)) == NULL)
	return (msg_error("mysh: error: malloc failed.\n"));
    }
  if (!env || !env[0] || !t_name)
    if ((t_name = my_strdup("xterm")) == NULL)
      return (msg_error("mysh: error: malloc failed.\n"));
  ret = tgetent(0, t_name);
  my_free(t_name);
  if (ret == 0)
    return (msg_error("mysh: error: invalid terminal name\n"));
  if (ret == -1)
    return (msg_error("mysh: error: cannot find termcap data base\n"));
  return (0);
}

/*
**			Init term ptr with raw mode, non-echo mode and read chars one by one.
**			Open /dev/tty to don't write on STDOUT until selection is validated.
*/
int			init_termios(char **env)
{
  t_termios		t;
  static t_termios	save;

  if (env == NULL)
    t = save;
  else
    {
      if (check_env(env))
	return (-1);
      if (tcgetattr(0, &t) == -1)
	return (1);
      save = t;
      t.c_lflag &= ~(ICANON | ECHO);
      t.c_cc[VMIN] = 1;
    }
  if (tcsetattr(0, 0, &t) == -1)
    return (-1);
  return (0);
}
