/*
** get_best_way_to_survive.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 17:29:50 2015 Anatole Menichetti
** Last update Tue Jun 23 23:58:27 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		It calls get_best_way_to_survive with tmps.
**		Used to recursivly check right, left, up, down squares.
*/
static void	try_best_way_to_survive(t_view *view,
					int visited_squares[10][2],
					int prev_visited_squares[10][2],
					int datas[4])
{
  int		ret;
  int		tmp1[10][2];
  int		tmp2[3];
  int		i;

  i = 0;
  while (i < 10 && prev_visited_squares[i][X] >= 0 &&
	 (prev_visited_squares[i][X] != datas[X] ||
	  prev_visited_squares[i][Y] != datas[Y]))
    i += 1;
  if (i == 10 || prev_visited_squares[i][X] < 0)
    {
      tmp2[0] = datas[0];
      tmp2[1] = datas[1];
      tmp2[2] = datas[2];
      copy_visited_squares(tmp1, prev_visited_squares);
      if ((ret = get_best_way_to_survive(view, tmp1, tmp2)) >= 0 &&
	  ret > datas[PRIORITY])
	{
	  datas[PRIORITY] = ret;
	  copy_visited_squares(visited_squares, tmp1);
	}
    }
}

/*
**		Check if the current square is accessible (stop the recursive).
*/
static int	cannot_access_current_square(t_view *view,
					     int prev_visited_squares[10][2],
					     int datas[3])
{
  int		i;

  i = 0;
  while (i < 10 && prev_visited_squares[i][0] >= 0)
    i += 1;
  if (datas[Y] < 0 || datas[X] < 0 || !view->priorities[datas[Y]] ||
      datas[X] > datas[Y] * 2 + 1 ||
      view->priorities[datas[Y]][datas[X]] < 0 ||
      datas[ACTIONS] >= 10 || i == 10)
    return (-1);
  datas[ACTIONS] += strlen(view->vision[datas[Y]][datas[X]]);
  return (i);
}

/*
**		Returns the potential of current square.
**		If it is potential => copy visited_squares in prev ones.
*/
static int	current_square_potential(int next_priority,
					 int current_priority,
					 int prev_visited_squares[10][2],
					 int visited_squares[10][2])
{
  if (next_priority < 0)
    return (current_priority);
  copy_visited_squares(prev_visited_squares, visited_squares);
  return (next_priority + current_priority);
}

/*
**		Recursive search for squares with best priorities.
**		These squares are saved in visited_squares and transmited
**		to caller with prev_visited_square.
*/
int		get_best_way_to_survive(t_view *view,
					int prev_visited_square[10][2],
					int dat[3])
{
  int		visited_square[10][2];
  int		tmp[4];
  int		i;

  if ((i = cannot_access_current_square(view, prev_visited_square, dat)) < 0)
    return (-1);
  prev_visited_square[i][X] = dat[X];
  prev_visited_square[i][Y] = dat[Y];
  copy_visited_squares(visited_square, prev_visited_square);
  tmp[X] = dat[X] + 1;
  tmp[Y] = dat[Y] + 1;
  tmp[ACTIONS] = dat[ACTIONS] + 1;
  tmp[PRIORITY] = -1;
  try_best_way_to_survive(view, visited_square, prev_visited_square, tmp);
  tmp[Y] -= 1;
  tmp[ACTIONS] += 1;
  try_best_way_to_survive(view, visited_square, prev_visited_square, tmp);
  tmp[X] -= 2;
  try_best_way_to_survive(view, visited_square, prev_visited_square, tmp);
  tmp[X] += 1;
  tmp[Y] -= 2;
  tmp[ACTIONS] += 1;
  try_best_way_to_survive(view, visited_square, prev_visited_square, tmp);
  return (current_square_potential(tmp[3], view->priorities[dat[Y]][dat[X]],
				   prev_visited_square, visited_square));
}
