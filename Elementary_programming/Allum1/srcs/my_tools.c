/*
** my_tools.c for allum1 in /home/menich_a/rendu/Allum1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 11 18:34:42 2014 menich_a
** Last update Sun Feb 16 21:36:12 2014 menich_a
*/

#include <stdlib.h>
#include "allum1.h"
#include "my.h"

void	my_putchar_red(char c)
{
  my_putstr("\033[31m\033[45m");
  my_putchar(c);
  my_putstr("\033[0m");
}

/*
**	Returns number of pipes in str.
*/
int	my_pipelen(char *str)
{
  int	i;
  int	pipes;

  i = 0;
  pipes = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '|')
        pipes = pipes + 1;
      i = i + 1;
    }
  return (pipes);
}

/*
**	Display a tray of `rows' rows.
*/
void	display_tray(int rows, int height, int width)
{
  int	pipes;
  int	i;

  pipes = 1;
  while (pipes < rows * 2)
    {
      i = 0;
      move_cursor(width, height);
      if (pipes == 1)
        {
          my_putstr("\033[31m|\033[0m");
          launch_termcap(SAVE_CURSOR);
        }
      else
        while (i++ < pipes)
          my_putchar('|');
      width = width - 1;
      height = height + 1;
      pipes = pipes + 2;
    }
  launch_termcap(RESTORE_CURSOR);
}

/*
**	Returns pos of pipe nexter of pos in str.
*/
int	get_next_pipe(char *str, int pos)
{
  while (str[pos] != '|' && str[pos] != '\0')
    {
      pos = pos + 1;
      launch_termcap(MOVE_RIGHT);
    }
  if (str[pos] == '\0')
    {
      while (pos >= 0 && str[pos] != '|')
        {
          pos = pos - 1;
          launch_termcap(MOVE_LEFT);
        }
    }
  return (pos);
}

/*
**	Build a tray of rows rows.
*/
char	**build_tray(char **tray, int rows)
{
  int	i;
  int	j;
  int	pipes;

  i = 0;
  pipes = 1;
  tray = malloc(sizeof(*tray) * (rows + 1));
  if (tray == NULL)
    return (NULL);
  while (i < rows)
    {
      j = 0;
      tray[i] = malloc(sizeof(**tray) * (pipes + 1));
      if (tray[i] == NULL)
	return (NULL);
      while (j < pipes)
        tray[i][j++] = '|';
      tray[i][j] = '\0';
      pipes = pipes + 2;
      i = i + 1;
    }
  tray[i] = NULL;
  return (tray);
}
