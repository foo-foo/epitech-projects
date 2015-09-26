/*
** my_init.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Jan 14 12:25:41 2014 menich_a
** Last update Sun Jan 19 20:07:35 2014 menich_a
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <ncurses/curses.h>
#include "my_select.h"
#include "my.h"

void	reinit_then_exit(t_termios t, char *msg, int status)
{
  my_clear_screen();
  if (reinit_termios(&t) == 1)
    {
      my_putstr("my_select: error: cannot reinit terminal settings\n");
      exit(1);
    }
  if (msg != NULL)
    my_putstr(msg);
  exit(status);
}

/*
**      find_in_env: cherche la variable to_find dans env
**      to_find est le nom de la variable, ponctué par un '='.
*/
char	*find_in_env(char **env, char *to_find)
{
  char	*res;
  int	i;
  int	j;
  int	len;

  len = my_strlen(to_find);
  i = 0;
  j = len;
  while (env[i] != NULL)
    {
      if (my_strlen(env[i]) > len && my_strncmp(env[i], to_find, len - 1) == 0)
        {
          res = malloc(sizeof(*res) * (my_strlen(env[i]) - len + 1));
          if (res == NULL)
            return (NULL);
          while (env[i][j] != '\0')
            res[j - len] = env[i][j++];
          res[j - len] = '\0';
          return (res);
        }
      i = i + 1;
    }
  return (NULL);
}

/*
**	Initiate termcaps data base. If TERM environnement var is not set
**	=> initiate data base with "xterm" terminal name [enable by default]
*/
int	check_env(char **env)
{
  char	*t_name;
  int	ret;

  if (env != NULL && env[0] != NULL)
    t_name = find_in_env(env, "TERM=");
  if (t_name == NULL || env == NULL || env[0] == NULL)
    if ((t_name = my_strdup("xterm")) == NULL)
      return (1);
  ret = tgetent(NULL, t_name);
  free(t_name);
  if (ret == 0)
    {
      my_putstr("my_select: error: invalid terminal name\n");
      return (1);
    }
  if (ret == -1)
    {
      my_putstr("my_select: error: cannot find termcap data base\n");
      return (1);
    }
  return (0);
}

/*
**	Init term ptr with raw mode, non-echo mode and read chars one by one.
**	Open /dev/tty to don't write on STDOUT until selection is validated.
*/
int	init_termios(t_termios *t)
{
  if (tcgetattr(0, t) == -1)
    {
      my_putstr("my_select: error: tcgetattr failed\n");
      return (1);
    }
  t->c_lflag &= ~(ICANON | ECHO);
  t->c_cc[VMIN] = 1;
  t->c_cc[VTIME] = 0;
  g_fd = open("/dev/tty", O_RDWR);
  if (g_fd == -1)
    {
      my_putstr("error: cannot open /dev/tty\n");
      return (1);
    }
  remove_cursor();
  if (tcsetattr(0, 0, t) == -1)
    {
      my_putstr("my_select: error: tcsetattr failed\n");
      return (1);
    }
  return (0);
}

int	reinit_termios(t_termios *t)
{
  if (tcgetattr(0, t) == -1)
    {
      my_putstr("my_select: error: tcgetattr failed\n");
      return (1);
    }
  t->c_lflag |= (ICANON | ECHO);
  display_cursor();
  close(g_fd);
  if (tcsetattr(0, 0, t) == -1)
    {
      my_putstr("my_select: error: tcsetattr failed\n");
      return (1);
    }
  return (0);
}
