/*
** key_pressed.c for allum1 in /home/menich_a/rendu/Allum1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Feb 14 17:54:24 2014 menich_a
** Last update Sat Feb 15 11:52:38 2014 menich_a
*/

#include "allum1.h"
#include "my.h"

/*
**	If a key is pressed re-display normally pipe on which is cursor.
**	Then move cursor on first pipe of next/prev rows.
**	Finally, display in red pipes on which is cursor.
*/
void	arrows_up_down(char **tray, t_pos *pos, char arrow, int x2)
{
  if (check_arrows_validity(tray, arrow, pos) == SUCCESS)
    {
      launch_termcap(MOVE_LEFT);
      my_putchar(tray[pos->y][pos->x]);
      pos->x = 0;
      if (arrow == UP)
        {
          pos->height = pos->height - 1;
          while (my_find_in_str(tray[--pos->y], '|') < 0)
            pos->height = pos->height - 1;
          while (tray[pos->y][pos->x] != '|' && tray[pos->y][pos->x] != '\0')
            pos->x = pos->x + 1;
        }
      if (arrow == DOWN)
        {
          pos->height = pos->height + 1;
          while (my_find_in_str(tray[++pos->y], '|') < 0)
            pos->height = pos->height + 1;
          while (tray[pos->y][pos->x] != '|' && tray[pos->y][pos->x] != '\0')
            pos->x = pos->x + 1;
        }
      x2 = pos->width - my_strlen(tray[pos->y]) / 2 + pos->x;
      move_cursor(x2, pos->height);
      my_putchar_red(tray[pos->y][pos->x]);
    }
}

/*
**	If a key is pressed re-display normally pipe on which is cursor.
**	Then move cursor left/right and display in red pipes on which is cursor.
*/
void	arrows_left_right(char **tray, t_pos *pos, char arrow)
{
  if ((arrow == LEFT && pos->x > 0) ||
      (arrow == RIGHT && tray[pos->y][pos->x + 1] != '\0'))
    {
      launch_termcap(MOVE_LEFT);
      my_putchar(tray[pos->y][pos->x]);
      if (arrow == LEFT)
        {
          launch_termcap(MOVE_LEFT);
          launch_termcap(MOVE_LEFT);
          pos->x = pos->x - 1;
          while (pos->x > 0 && tray[pos->y][pos->x] != '|')
            {
              pos->x = pos->x - 1;
              launch_termcap(MOVE_LEFT);
            }
        }
      if (arrow == RIGHT)
        pos->x = pos->x + 1;
      if (tray[pos->y][pos->x] != '|')
        pos->x = get_next_pipe(tray[pos->y], pos->x);
      my_putchar_red(tray[pos->y][pos->x]);
    }
}

/*
**	Re-display normally pipe on which is cursor, then:
**	rm the pipe on which is cursor and adapt **tray.
**	turn = -1 => cannot move up/down any more.
*/
int	delete_key(char **tray, t_pos *pos, char key, int turn)
{
  if (key == 127 && tray[pos->y][pos->x] == '|')
    {
      launch_termcap(MOVE_LEFT);
      my_putstr(RED_BROKEN_PIPE);
      tray[pos->y][pos->x] = BROKEN_PIPE;
      pos->x = get_next_pipe(tray[pos->y], pos->x);
      if (pos->x >= 0)
        {
          launch_termcap(MOVE_LEFT);
          my_putchar_red(tray[pos->y][pos->x]);
        }
      turn = -1;
    }
  return (turn);
}
