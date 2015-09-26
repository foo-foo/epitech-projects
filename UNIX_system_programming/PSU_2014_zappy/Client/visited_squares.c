/*
** clear_vision.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 17:29:50 2015 Anatole Menichetti
** Last update Wed Jun 17 22:56:45 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

void		copy_visited_squares(int dest[10][2], int src[10][2])
{
  int		y;

  y = 0;
  while (y < 10)
    {
      dest[y][X] = src[y][X];
      dest[y][Y] = src[y][Y];
      y += 1;
    }
}

void		init_visited_squares(int visited_squares[10][2])
{
  int		y;

  y = 0;
  while (y < 10)
    {
      visited_squares[y][X] = -1;
      visited_squares[y][Y] = -1;
      y += 1;
    }
}

/*
**		Returns every action associated to the current square.
**		e.g: take stone, put stone, turn, move...
*/
static void	get_one_square_actions(int visited_squares[10][2],
				       short actions[10], int pos[5])
{
  if (pos[J])
    {
      if (pos[I] < 8)
	{
	  if ((pos[D] == UP && pos[X] > visited_squares[pos[J] - 1][X] &&
	       pos[Y] == visited_squares[pos[J] - 1][Y]) ||
	      (pos[D] == LEFT && pos[Y] > visited_squares[pos[J] - 1][Y]))
	    {
	      actions[pos[I]++] = TURN_RIGHT;
	      pos[D] = (pos[D] < LEFT ? pos[D] + 2 : RIGHT - pos[D]);
	    }
	  if ((pos[D] == UP && pos[X] < visited_squares[pos[J] - 1][X] &&
	      pos[Y] == visited_squares[pos[J] - 1][Y]) ||
	      (pos[D] == RIGHT && pos[Y] > visited_squares[pos[J] - 1][Y]))
	    {
	      actions[pos[I]++] = TURN_LEFT;
	      pos[D] = (pos[D] < LEFT ? RIGHT - pos[D] : pos[D] - 2);
	    }
	}
      actions[pos[I]++] = MOVE;
      pos[J] += 1;
    }
}

/*
**		Translate every visited square datas into associated actions.
*/
void		get_visited_squares_actions(t_player *p, char ***vision,
					    int visited_squares[10][2],
					    short actions[10])
{
  int		index;
  int		pos[5];

  pos[I] = 0;
  pos[J] = 0;
  pos[D] = UP;
  while (pos[I] < 9 && actions[pos[I]] >= 0)
    pos[I] += 1;
  while (pos[I] < 9 && pos[J] < 10 && visited_squares[pos[J]][X] >= 0)
    {
      pos[X] = visited_squares[pos[J]][X];
      pos[Y] = visited_squares[pos[J]][Y];
      get_one_square_actions(visited_squares, actions, pos);
      index = 0;
      while (pos[I] < 9 && vision[pos[Y]][pos[X]][index])
	{
	  if (vision[pos[Y]][pos[X]][index] != 56 &&
	      (vision[pos[Y]][pos[X]][index] != 49 || p->stuff[FOOD] < MAX_FOOD))
	    actions[pos[I]++] = vision[pos[Y]][pos[X]][index];
	  index += 1;
	}
      if (!pos[J])
	pos[J] += 1;
    }
  actions[pos[I]] = LOOK;
}
