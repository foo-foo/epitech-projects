/*
** move.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc/srcs
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar  5 11:55:10 2015 Anatole Menichetti
** Last update Sun Mar  8 22:31:11 2015 Anatole Menichetti
*/

#include "../includes/lemipc.h"

int	get_next_move(short pos, short dest, short m_size)
{
  char	h;
  char	v;

  h = dest % m_size - pos % m_size;
  v = dest / m_size - pos / m_size;
  if (h > 0)
    pos += 1;
  if (h < 0)
    pos -= 1;
  if (v > 0)
    pos += m_size;
  if (v < 0)
    pos -= m_size;
  return (pos);
}

int	straight_around(char *map, short dest, short pos, char m_size)
{
  if (dest == pos + 1 || dest == pos - 1)
    {
      if (pos > m_size && !map[dest - m_size])
	return (dest - m_size);
      if (pos < m_size * m_size - m_size && !map[dest + m_size])
 	return (dest + m_size);
      if (pos > m_size && !map[pos - m_size])
	return (pos - m_size);
      if (pos < m_size * m_size - m_size && !map[pos + m_size])
	return (pos + m_size);
    }
  if (dest == pos - m_size || dest == pos + m_size)
    {
      if ((dest - 1) % m_size && !map[dest - 1])
	return (dest - 1);
      if ((dest + 2) % m_size && !map[dest + 1])
	return (dest + 1);
      if ((pos - 1) % m_size && !map[pos - 1])
	return (pos - 1);
      if ((pos + 2) % m_size && !map[pos + 1])
	return (pos + 1);
    }
  return (-1);
}

int	get_around(char *map, short dest, short pos, char m_size)
{
  int	move;

  move = straight_around(map, dest, pos, m_size);
  if (move >= 0)
    return (move);
  if (dest == pos - m_size + 1 || dest == pos + m_size + 1)
    {
      if (!map[pos + 1])
	return (pos + 1);
      if (!map[dest - 1])
	return (dest - 1);
    }
  if (dest == pos - m_size - 1 || dest == pos + m_size - 1)
    {
      if (!map[pos - 1])
	return (pos - 1);
      if (!map[dest + 1])
	return (dest + 1);
    }
  return (pos);
}

int	move(char *map, short pos, char t_nbr, char m_size)
{
  int	dest;

  dest = get_target_pos(map, pos, t_nbr, m_size);
  if (dest != pos)
    dest = get_next_move(pos, dest, m_size);
  if (dest != pos)
    {
      if (map[dest] == t_nbr)
	dest = get_around(map, dest, pos, m_size);
      if (map[dest])
	return (pos);
      map[pos] = 0;
      map[dest] = t_nbr;
      return (dest);
    }
  return (pos);
}
