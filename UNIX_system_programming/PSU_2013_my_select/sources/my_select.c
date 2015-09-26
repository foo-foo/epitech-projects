/*
** my_select.c for my_select in /home/menich_a/rendu/PSU_2013_my_select
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan 10 12:58:18 2014 menich_a
** Last update Sun Jan 19 20:13:51 2014 menich_a
*/

#include <sys/ioctl.h>
#include <signal.h>
#include <ncurses/curses.h>
#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include "my_select.h"
#include "my.h"

t_size		g_window;

/*
**		If a signal SIGWINCH (resizing terminal) is recepted:
**		=> adapt the global size to display a list with good dimensions.
*/
void		my_resizing(int signal)
{
  t_winsize	window_size;
  t_termios	t;

  if (signal == SIGWINCH)
    {
      if (ioctl(g_fd, TIOCGWINSZ, &window_size) != -1)
	{
	  g_window.height = window_size.ws_row;
	  g_window.width = window_size.ws_col;
	  display_list(g_window.list, g_window.pos, &g_window);
	}
      else
	reinit_then_exit(t, "ioctl error: cannot find window size", -1);
    }
}

void		my_signal(void)
{
  signal(SIGTERM, &my_kill);
  signal(SIGKILL, &my_kill);
  signal(SIGINT, &my_kill);
  signal(SIGWINCH, &my_resizing);
  signal(SIGTSTP, &my_ignore_signal);
}

/*
**		Check if user taped on an arrow key then adapt position (i) \
**		and display list with a new position for cursor.
*/
int		check_arrows(char *buff, t_list *list, int pos, int posmax)
{
  if (buff[0] == ESC && buff[1] == 91 && buff[2] == 65)
    {
      if (--pos < 0)
	pos = posmax;
    }
  else if (buff[0] == ESC && buff[1] == 91 && buff[2] == 66)
    {
      if (++pos > posmax)
	pos = 0;
    }
  else if (buff[0] == ESC && buff[1] == 91 && buff[2] == 67)
    {
      if ((pos = pos + (g_window.height - 1)) > posmax)
	while (list->pos-- > 0)
	  pos = pos - (g_window.height - 1);
    }
  else if (buff[0] == ESC && buff[1] == 91 && buff[2] == 68)
    {
      if ((pos = pos - (g_window.height - 1)) < 0)
	while (list->pos-- > 0)
	  pos = pos + (g_window.height - 1);
    }
  return (pos);
}

/*
**		Change pos value according on key pressed.
**		Adapt global window informations for each key pressed.
*/
int		keypressed(t_termios t, t_list *list, char *buff, int posmax)
{
  static int	pos;

  if (buff[0] == ESC && buff[1] == 91)
    pos = check_arrows(buff, list, pos, posmax);
  else if (buff[0] == SPACE)
    {
      if (select_elem(list, pos) == 0)
	if (++pos > posmax)
	  pos = 0;
      display_list(list, pos, &g_window);
    }
  else if (buff[0] == DELETE || buff[0] == BACKSPACE)
    {
      if ((pos = delete_elem(t, list, pos, posmax)) == -1)
	return (1);
      display_list(list, pos, &g_window);
      posmax = posmax - 1;
    }
  else if (buff[0] == ESC && buff[1] != 91)
    reinit_then_exit(t, NULL, 0);
  else
    pos = dynamic_research_mode(list, buff, pos);
  g_window.pos = pos;
  display_list(list, pos, &g_window);
  return (posmax);
}

/*
**		Initiate the global var used to display the list.
**		(pos = 0 => first elem is selectionned).
**		my_resizing => display the list with appropriate dimensions.
**		my_signal catch signals send by user.
**		launch the reading loop used for my_select.
*/
int		my_select(t_termios t, t_list *list, int posmax)
{
  char		buff[BUFF_SIZE + 1];
  int		ret;

  g_window.list = list;
  g_window.pos = 0;
  my_resizing(SIGWINCH);
  my_signal();
  ret = read(0, buff, BUFF_SIZE);
  if (ret == -1)
    return (msg_error("read error\n", 1));
  buff[ret] = '\0';
  while (buff[0] != '\n' && buff[0] != '\r')
    {
      posmax = keypressed(t, list, buff, posmax);
      if (posmax == -1)
	return (1);
      g_window.list = list;
      ret = read(0, buff, BUFF_SIZE);
      if (ret == -1)
	return (msg_error("read error\n", 1));
      buff[ret] = '\0';
    }
  return (0);
}
