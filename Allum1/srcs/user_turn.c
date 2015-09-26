/*
** user_turn.c for allum1 in /home/menich_a/rendu/Allum1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 11 18:02:16 2014 menich_a
** Last update Sun Feb 16 21:44:53 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "allum1.h"
#include "my.h"

void	display_player_name(t_pos *pos, int turn)
{
  launch_termcap(SAVE_CURSOR);
  move_cursor(pos->width - 5, pos->height - pos->y - 2);
  if (turn % 2 == 0)
    my_putstr_underline("Player One:");
  else
    my_putstr_underline("Player Two:");
  launch_termcap(RESTORE_CURSOR);
}

/*
**	Return the first number typed by user.
*/
int	read_nbr(char *buff)
{
  char	tmp[3];
  int	i;

  i = 0;
  while (read(0, buff, BUFF_SIZE) != -1 && buff[0] != '\n' && i < 3)
    if (buff[0] >= '0' && buff[0] <= '9')
      {
	tmp[i] = buff[0];
	i = i + 1;
      }
  if (buff[0] != '\n' && i < 3)
    return (FAILURE);
  tmp[i] = '\0';
  return (my_getnbr(tmp));
}

/*
**	Mode used to receved user commands (to know what he wants to rm).
*/
int	read_mode(char **tray, t_pos *pos, char *buff)
{
  int	size;
  int	to_rm;

  size = 0;
  while (tray[size] != NULL)
    size = size + 1;
  move_cursor(0, 0);
  my_putstr("On which line do you want to remove matches ?");
  while ((pos->y = read_nbr(buff) - 1) < 0 || pos->y >= size ||
	 my_pipelen(tray[pos->y]) <= 0)
    {
      move_cursor(0, 0);
      my_putstr("Invalid line                                 ");
    }
  move_cursor(0, 0);
  my_putstr("How many matches do you want to remove ?     ");
  while ((to_rm = read_nbr(buff)) <= 0)
    {
      move_cursor(0, 0);
      my_putstr("You cannot remove so few matches             ");
    }
  pos->x = 0;
  launch_remove(tray, pos, to_rm);
  return (SUCCESS);
}

/*
**	Check if user have the right to use this arrow.
*/
int	check_arrows_validity(char **tray, char arrow, t_pos *pos)
{
  int	i;

  i = pos->y;
  if (arrow == UP && i > 0)
    while (i > 0)
      {
        if (my_pipelen(tray[i - 1]) > 0)
          return (SUCCESS);
        i = i - 1;
      }
  if (arrow == DOWN && tray[i + 1] != NULL)
    while (tray[i + 1] != NULL)
      {
        if (my_pipelen(tray[i + 1]) > 0)
          return (SUCCESS);
        i = i + 1;
      }
  return (FAILURE);
}

/*
**	If user selected read mode => read mode.
**	Else => termcaps mode (launch appropriate key function).
**	These 2 modes modify tray by reading user.
*/
int	user_turn(char **tray, int turn, t_pos pos, int mode)
{
  char	buff[BUFF_SIZE + 1];

  pos.height = pos.height + pos.y;
  launch_termcap(MOVE_LEFT);
  if (mode == 0)
    my_putchar_red(tray[pos.y][pos.x]);
  display_player_name(&pos, turn);
  if (mode == 1)
    return (read_mode(tray, &pos, buff));
  if (read(0, buff, BUFF_SIZE) == -1)
    return (FAILURE);
  while (buff[0] != '\n' || turn != -1)
    {
      if (turn != -1 && buff[0] == 27 && buff[1] == 91)
        arrows_up_down(tray, &pos, buff[2], 0);
      if (buff[0] == 27 && buff[1] == 91)
        arrows_left_right(tray, &pos, buff[2]);
      turn = delete_key(tray, &pos, buff[0], turn);
      if (read(0, buff, BUFF_SIZE) == -1)
        return (FAILURE);
    }
  launch_termcap(MOVE_LEFT);
  my_putchar(tray[pos.y][pos.x]);
  return (SUCCESS);
}
