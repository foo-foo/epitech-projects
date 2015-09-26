/*
** allum1.c for allum1 in /home/menich_a/rendu/Allum1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Feb  6 15:52:53 2014 menich_a
** Last update Sun Feb 16 22:04:51 2014 menich_a
*/

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses/curses.h>
#include <term.h>
#include <signal.h>
#include <stdlib.h>
#include "allum1.h"
#include "my.h"

static t_pos	g_winsize;

void		check_resizing(int sig)
{
  static int	rows;
  t_winsize	ws;

  if (rows == 0)
    rows = sig;
  if (ioctl(0, TIOCGWINSZ, &ws) == -1)
    exit(-1);
  g_winsize.width = ws.ws_col / 2;
  g_winsize.height = ws.ws_row / 2 - rows / 2;
  launch_termcap(CLEAR);
  if (g_winsize.height < 10 || g_winsize.width <= 10 ||
	 g_winsize.height / 2 - rows / 2 <= 0 || g_winsize.width / 2 - rows <= 0)
    my_putstr("Term too small");
  else
    display_tray(rows, g_winsize.height, g_winsize.width);
}

/*
**		Remove `to_rm' pipes on tray biggest line.
*/
void		launch_remove(char **tray, t_pos *pos, int to_rm)
{
  int		x2;

  while (tray[pos->y][pos->x] != '|')
    pos->x = pos->x + 1;
  x2 = pos->width + pos->x - my_strlen(tray[pos->y]) / 2;
  move_cursor(x2, pos->height + pos->y);
  while (tray[pos->y][pos->x] != '\0' && to_rm > 0)
    {
      usleep(100000);
      if (tray[pos->y][pos->x] == '|')
	{
	  tray[pos->y][pos->x] = BROKEN_PIPE;
	  my_putstr(BLUE_BROKEN_PIPE);
	  to_rm = to_rm - 1;
	}
      else
	launch_termcap(MOVE_RIGHT);
      pos->x = pos->x + 1;
    }
}

/*
**		Init a new turn: move cursor on the first pipe of the tray.
*/
int		launch_new_turn(char **tray, t_pos pos, int difficulty, int mode)
{
  static int	turn;
  int		x2;


  if (turn == 0)
    turn = pos.x;
  signal(SIGWINCH, &check_resizing);
  pos.height = g_winsize.height;
  pos.width = g_winsize.width;
  pos.x = my_find_in_str(tray[pos.y], '|');
  x2 = pos.width - my_strlen(tray[pos.y]) / 2 + 1;
  move_cursor(x2 + pos.x, pos.height + pos.y);
  if (turn % 2 == 0 || difficulty == MULTIPLAYER)
    if (user_turn(tray, turn, pos, mode) == FAILURE)
      return (FAILURE);
  if (turn % 2 != 0 && difficulty != 2)
    if (computer_turn(tray, difficulty, pos) == FAILURE)
      return (FAILURE);
  turn = turn + 1;
  return (SUCCESS);
}

void		game_over(char **tray, t_pos pos, int turn, int rows)
{
  my_free_tab(tray);
  launch_termcap(CLEAR);
  move_cursor(pos.width - 8, pos.height - rows);
  if (turn % 2 == 0)
    my_putstr_underline("Player one won!!\n");
  else
    my_putstr_underline("Player one lost!!\n");
  usleep(1500000);
}

/*
**		Init a new game: create a tray of size which user wants (set_rows).
**		Then, build the tray (char **), contains a line in each char*.
**		Launch new turn while there are some pipes in tray.
*/
int		launch_new_game(t_pos pos, int difficulty, int mode)
{
  char		**tray;
  int		turn;
  int		rows;

  rows = set_rows(pos.height, pos.width);
  if (rows == FAILURE)
    return (FAILURE);
  check_resizing(rows);
  if (rows % 2 == 0)
    turn = 1;
  else
    turn = 0;
  tray = build_tray(tray, rows);
  if (tray == NULL)
    return (FAILURE);
  pos.x = turn;
  while ((pos.y = my_find_in_tab(tray, '|')) >= 0)
    {
      if (launch_new_turn(tray, pos, difficulty, mode) == FAILURE)
	return (FAILURE);
      turn = turn + 1;
    }
  game_over(tray, pos, turn, rows);
  return (SUCCESS);
}
