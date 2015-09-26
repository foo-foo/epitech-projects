/*
** main.c for allum1 in /home/menich_a/rendu/Allum1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 11 18:06:55 2014 menich_a
** Last update Sun Feb 16 21:42:24 2014 menich_a
*/

#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <ncurses/curses.h>
#include "allum1.h"
#include "my.h"

/*
**			Called bu display_menu. Display and underline good tittle.
*/
int			display_titles(char *name1, char *name2, int width, int height)
{
  if (height < 0)
    {
      height = -height;
      my_putstr_underline(name1);
      launch_termcap(BOLD);
      move_cursor(width - my_strlen(name2) / 2, height + 1);
      my_putstr(name2);
    }
  else
    {
      launch_termcap(BOLD);
      my_putstr(name1);
      move_cursor(width - my_strlen(name2) / 2, height + 1);
      my_putstr_underline(name2);
    }
  return (height);
}

/*
**			Display a menu with name1 and name2 choice.
*/
int			display_menu(char *name1, char *name2, int height, int width)
{
  char			buff[BUFF_SIZE + 1];
  int			pos;

  pos = 0;
  while (buff[0] != '\n')
    {
      launch_termcap(CLEAR);
      move_cursor(width - my_strlen(name1) / 2, height);
      if (pos % 2 == 0)
        height = -height;
      height = display_titles(name1, name2, width, height);
      if (read(0, buff, BUFF_SIZE) == -1)
        return (FAILURE);
      if (buff[0] == 27 && buff[1] == 91 && (buff[2] == 65 || buff[2] == 66))
        pos = pos + 1;
    }
  buff[0] = '\0';
  return (pos % 2);
}

/*
**      Initiate termcaps data base. If TERM environnement var is not set
**      => initiate data base with "xterm" terminal name [enable by default]
**	Remove cursor and launch raw mode.
**	If launched with reinit = 1 => set save => reinit termios.
*/
int			init_termios(char **env, int reinit)
{
  static t_termios	save;
  t_termios		t;
  char			*t_name;
  int			ret;

  if (reinit == 1)
    {
      launch_termcap(ENABLE_CURSOR);
      launch_termcap(CLEAR);
      return (tcsetattr(0, 0, &save));
    }
  t_name = my_find_in_env(env, "TERM");
  if (t_name == NULL)
    t_name = "xterm";
  ret = tgetent(NULL, t_name);
  if (ret == 0 || ret == -1 || tcgetattr(0, &t) == -1)
    return (FAILURE);
  save = t;
  t.c_lflag &= ~(ICANON | ECHO);
  t.c_cc[VMIN] = 1;
  launch_termcap("vi");
  if (tcsetattr(0, 0, &t) == -1)
    return (FAILURE);
  return (SUCCESS);
}

/*
**			Display a game tray adapted to number of rows.
**			User can adjust tray with arrows (UP/DOWN).
*/
int			set_rows(int height, int width)
{
  char			buff[BUFF_SIZE + 1];
  int			rows;

  rows = 2;
  while (buff[0] != '\n')
    {
      launch_termcap(CLEAR);
      move_cursor(width - 16, 1);
      if (width * 2 > 32)
        my_putstr_underline("Adjust tray size and press enter");
      display_tray(rows, height - rows / 2, width);
      if (read(0, buff, BUFF_SIZE) == FAILURE)
        return (FAILURE);
      if (rows < width - 1 && rows < height + height / 2 &&
	  buff[0] == 27 && buff[1] == 91 && buff[2] == UP)
        rows = rows + 1;
      if (rows > 2 && buff[0] == 27 && buff[1] == 91 && buff[2] == DOWN)
        rows = rows - 1;
    }
  launch_termcap(CLEAR);
  display_tray(rows, height - rows / 2, width);
  return (rows);
}

/*
**			Launch 4 menus to set :
**			- New Game / Exit
**			- Number of players (MULTIPLAYER bu default)
**			- If ONE_PLAYER => menu difficulty (EASY/HARD)
**			Then launch new game with these values.
*/
int			main(__attribute__((unused))int ac,
			     __attribute__((unused))char **av, char **env)
{
  t_pos			pos;
  int			diff;
  int			mode;

  if (init_termios(env, 0) == FAILURE)
    return (FAILURE);
  pos.height = tgetnum(WINDOW_HEIGHT) / 2;
  pos.width = tgetnum(WINDOW_WIDTH) / 2;
  while (display_menu("New Game", "Exit", pos.height - 1, pos.width) == SUCCESS)
    {
      diff = MULTIPLAYER;
      if (display_menu("One player", "Two players", pos.height - 1, pos.width)
	  == ONE_PLAYER)
        if ((diff = display_menu("Easy", "Hard", pos.height - 1, pos.width))
	    != EASY)
          diff = HARD;
      if ((mode = display_menu("Normal Mode", "Read Mode",
			       pos.height - 1, pos.width)) == FAILURE)
	return (FAILURE);
      if (launch_new_game(pos, diff, mode) == FAILURE)
	return (FAILURE);
    }
  return (init_termios(env, 1));
}
