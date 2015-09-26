/*
** computer_turn.c for allum1 in /home/menich_a/rendu/Allum1/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Feb 14 18:00:40 2014 menich_a
** Last update Sun Feb 16 22:14:55 2014 menich_a
*/

#include <stdlib.h>
#include "allum1.h"

/*
**	move cursor and pos->y on biggest row then:
**	Find max pipes computer can rm on this row.
*/
int	remove_pipes(char **tray, t_pos *pos, int to_rm)
{
  int	max[2];

  max[0] = 0;
  max[1] = 0;
  if (to_rm == 0)
    {
      while (tray[pos->y] != NULL && my_pipelen(tray[pos->y]) != 1)
	pos->y = pos->y + 1;
      max[0] = pos->y;
      to_rm = 1;
    }
  else
    while (tray[pos->y] != NULL)
      {
	if (my_pipelen(tray[pos->y]) > max[1])
	  {
	    max[0] = pos->y;
	    max[1] = my_pipelen(tray[pos->y]);
	  }
	pos->y = pos->y + 1;
      }
  pos->y = max[0];
  launch_remove(tray, pos, to_rm);
  return (SUCCESS);
}

/*
**	If number of rows still containing pipes is "pair":
**	=> remove the biggest row.
**	Else => remove all pipes exept one on biggest row.
*/
int	find_matches_to_rm(char **tray)
{
  int	sizemax;
  int	len;
  int	cpt;
  int	y;

  y = 0;
  cpt  = 0;
  sizemax = 0;
  while (tray[y] != NULL)
    {
      len = my_pipelen(tray[y]);
      if (len > 0)
        cpt = cpt + 1;
      if (len > sizemax)
        sizemax = len;
      y = y + 1;
    }
  if (cpt % 2 != 0 && sizemax > 1)
    sizemax = sizemax - 1;
  return (sizemax);
}

int	best_choice(int big_lines, int small_lines, int sizemax)
{
  if (big_lines == 2 && small_lines == 0)
    {
      if (sizemax > 2)
	return (sizemax - 2);
      else
	return (sizemax);
    }
  if (big_lines == 2 && small_lines % 2 == 0)
    return (0);
  if ((big_lines % 2 != 0 && small_lines % 2 != 0) ||
      (big_lines == 1 && small_lines == 1))
    return (sizemax);
  return (sizemax - 1);
}

/*
**	Count number of lines with more than one pipe and:
**	number of lines with only one pipe.
**	best choice return choice adapted to situation.
*/
int	my_rm(char **tray, int y)
{
  int	sizemax;
  int	len;
  int	small_lines;
  int	big_lines;

  big_lines  = 0;
  small_lines = 0;
  sizemax = 0;
  while (tray[y] != NULL)
    {
      len = my_pipelen(tray[y]);
      if (len > sizemax)
	sizemax = len;
      if (len == 1)
        small_lines = small_lines + 1;
      if (len > 1)
        big_lines = big_lines + 1;
      y = y + 1;
    }
  return (best_choice(big_lines, small_lines, sizemax));
}

/*
**	For a difficulty level of 0, remove `find_matches_to_rm' pipes
**	Else remove `my_rm' pipes.
*/
int	computer_turn(char **tray, int difficulty, t_pos pos)
{
  int	to_rm;

  pos.x = 0;
  launch_termcap(SAVE_CURSOR);
  move_cursor(pos.width - 4, pos.height - 2);
  my_putstr_underline("Computer:");
  launch_termcap(RESTORE_CURSOR);
  if (difficulty == 0)
    to_rm = find_matches_to_rm(tray);
  else
    to_rm = my_rm(tray, 0);
  return (remove_pipes(tray, &pos, to_rm));
}
