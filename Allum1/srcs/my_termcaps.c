/*
** my_termcaps.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 15 15:02:58 2014 menich_a
** Last update Sat Feb 15 11:58:16 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <term.h>
#include "allum1.h"
#include "my.h"

int	display(int nb)
{
  return (write(1, &nb, 1));
}

void	launch_termcap(char *name)
{
  char	*cap;

  cap = tgetstr(name, NULL);
  tputs(cap, 1, &display);
}

/*
**	Display str in red and underline it.
*/
void	my_putstr_underline(char *str)
{
  launch_termcap("us");
  my_putstr("\033[31m");
  launch_termcap("md");
  my_putstr(str);
  my_putstr("\033[0m");
  launch_termcap("ue");
}

void	move_cursor(int x, int y)
{
  int	width;
  int	height;
  char	*cap;
  char	*str;

  width = tgetnum("co");
  height = tgetnum("li");
  if (x >= 0 && x <= width && y >= 0 && y <= height)
    {
      cap = tgetstr("cm", NULL);
      str = tgoto(cap, x, y);
      tputs(str, 1, &display);
    }
}
