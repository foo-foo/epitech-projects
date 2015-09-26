/*
** pos.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc/srcs
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar  8 22:26:26 2015 Anatole Menichetti
** Last update Sun Mar  8 23:01:48 2015 Anatole Menichetti
*/

#include "../includes/lemipc.h"

int	get_target_dist(short pos, short targ, char m_size)
{
  int	h;
  int	v;
  int	d;

  h = targ % m_size - pos % m_size;
  v = targ / m_size - pos / m_size;
  if (h)
    --h;
  if (v)
    --v;
  if (h < 0)
    h = -h;
  if (v < 0)
    v = -v;
  d = h + v;
  while (h-- && v--)
    --d;
  return (d);
}

int	get_target_pos(char *map, short pos, char t_nbr, char m_size)
{
  short	i;
  short	min[2];

  i = 0;
  min[0] = m_size * m_size;
  min[1] = m_size * m_size;;
  while (i < m_size * m_size)
    {
      if (map[i] && map[i] != t_nbr && get_target_dist(pos, i, m_size) < min[1])
        {
          min[0] = i;
          min[1] = get_target_dist(pos, i, m_size);
          if (!min[1])
            return (pos);
        }
      i++;
    }
  return (min[0]);
}

int	get_free_pos(char *map, int i, char m_size)
{
  if (i % m_size != 0 && !map[i - 1])
    return (i - 1);
  if ((i + 1) % m_size != 0 && !map[i + 1])
    return (i + 1);
  if (i >= m_size && !map[i - m_size])
    return (i - m_size);
  if (i < m_size * m_size - m_size && !map[i + m_size])
    return (i + m_size);
  if (i > m_size && i % m_size != 0 && !map[i - m_size - 1])
    return (i - m_size - 1);
  if (i > m_size && (i + 1) % m_size != 0 && !map[i - m_size + 1])
    return (i - m_size + 1);
  if (i < m_size * m_size - m_size &&
      i % m_size != 0 && !map[i + m_size - 1])
    return (i + m_size - 1);
  if (i < m_size * m_size - m_size &&
      (i + 1) % m_size != 0 && !map[i + m_size + 1])
    return (i + m_size + 1);
  return (-1);
}

int	starting_block_pos(char *map, char m_size)
{
  int	starting_pos;
  int	nbr_team;

  nbr_team = get_nbr_team(map, m_size);
  if (!nbr_team)
    starting_pos = 0;
  else if (nbr_team == 1)
    starting_pos = m_size * m_size - 1;
  else if (nbr_team == 2)
    starting_pos = m_size - 1;
  else if (nbr_team == 3)
    starting_pos = m_size * m_size - m_size;
  else if (nbr_team == 4)
    starting_pos = m_size * m_size / 2;
  else if (nbr_team == 5)
    starting_pos = m_size * m_size / 2 + m_size - 1;
  else
    return (-1);
  if (!map[starting_pos])
    return (starting_pos);
  return (get_free_pos(map, starting_pos, m_size));
}
