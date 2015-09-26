/*
** my_cursor_termcaps.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources/termcaps
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan 17 17:48:29 2014 menich_a
** Last update Fri Jan 17 17:52:39 2014 menich_a
*/

#include <stdlib.h>
#include <ncurses/curses.h>
#include <term.h>
#include "my_select.h"

void	remove_cursor(void)
{
  char	*cap;

  cap = tgetstr("vi", NULL);
  tputs(cap, 1, &display);
}

void	display_cursor(void)
{
  char	*cap;

  cap = tgetstr("ve", NULL);
  tputs(cap, 1, &display);
}

void	save_cursor_pos(void)
{
  char	*cap;

  cap = tgetstr("sc", NULL);
  tputs(cap, 1, &display);
}

void	restore_cursor_pos(void)
{
  char	*cap;

  cap = tgetstr("rc", NULL);
  tputs(cap, 1, &display);
}

void	move_cursor(int x, int y)
{
  char	*cap;
  char	*str;

  cap = tgetstr("cm", NULL);
  str = tgoto(cap, x, y);
  tputs(str, 1, &display);
}
