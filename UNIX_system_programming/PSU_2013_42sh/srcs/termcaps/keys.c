/*
** keys.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs/termcaps
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May  8 14:27:49 2014 menich_a
** Last update Sun May 25 22:50:09 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"
#include "my_termios.h"
#include "get_next_line.h"

int	delete_key(t_line *line, int width, int prompt_width)
{
  int	tmp;
  char	*str;

  if (line->i > 0)
    {
      line->i = line->i - 1;
      if (line->i % width + prompt_width == width - 1)
	while (width-- >= 0)
	  launch_termcap(MOVE_RIGHT);
      else
	launch_termcap(MOVE_LEFT);
      tmp = line->i - 1;
      launch_termcap(SAVE_CURSOR);
      launch_termcap(DEL_FROM_CURS);
      while (line->line[++tmp])
	my_putchar(line->line[tmp] = line->line[tmp + 1]);
      if ((str = my_strdup(line->line)) == NULL)
	return (-1);
      free(line->line);
      line->line = str;
      launch_termcap(RESTORE_CURSOR);
      line->size = line->size - 1;
    }
  return (0);
}

int	right_key(int i, int width, int prompt_width)
{
  int	tmp;

  i = i + 1;
  if (i % width + prompt_width == width)
    {
      tmp = width;
      while (tmp)
        {
          launch_termcap(MOVE_LEFT);
          tmp = tmp - 1;
        }
      launch_termcap(MOVE_DOWN);
    }
  else
    launch_termcap(MOVE_RIGHT);
  return (i);
}

int	left_key(int i, int width, int prompt_width)
{
  int	tmp;

  i = i - 1;
  if (i % width + prompt_width == width - 1)
    {
      tmp = width;
      while (tmp)
        {
          launch_termcap(MOVE_RIGHT);
          tmp = tmp - 1;
        }
      launch_termcap(MOVE_UP);
    }
  else
    launch_termcap(MOVE_LEFT);
  return (i);
}
