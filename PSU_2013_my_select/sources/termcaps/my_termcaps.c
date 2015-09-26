/*
** my_termcaps.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 15 15:02:58 2014 menich_a
** Last update Sun Jan 19 18:15:10 2014 menich_a
*/

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <term.h>
#include "my_select.h"
#include "my.h"

void		my_clear_screen(void)
{
  char		*cap;
  int		height;
  t_winsize	window_size;

  height = 0;
  if (ioctl(1, TIOCGWINSZ, &window_size) != -1)
    {
      while (height < window_size.ws_row)
	{
	  move_cursor(0, height);
	  cap = tgetstr("ce", NULL);
	  tputs(cap, 1, &display);
	  height = height + 1;
	}
    }
  else
    {
      cap = tgetstr("cl", NULL);
      tputs(cap, 1, &display);
    }
  move_cursor(0, 0);
}

void		my_putstr_underline(char *str)
{
  char		*cap;

  cap = tgetstr("us", NULL);
  tputs(cap, 1, &display);
  my_putstr(str);
  cap = tgetstr("ue", NULL);
  tputs(cap, 1, &display);
}

void		enable_reverse_video(void)
{
  char		*cap;

  cap = tgetstr("so", NULL);
  tputs(cap, 1, &display);
}

void		disable_reverse_video(void)
{
  char		*cap;

  cap = tgetstr("se", NULL);
  tputs(cap, 1, &display);
}
