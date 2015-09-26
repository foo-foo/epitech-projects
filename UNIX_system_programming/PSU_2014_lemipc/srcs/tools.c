/*
** tools.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  3 15:09:26 2015 Anatole Menichetti
** Last update Sun Mar  8 23:02:14 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include "../includes/lemipc.h"

int	my_perror(void)
{
  perror("lemipc");
  return (FAILURE);
}

int	check_params(char *t_nbr, char *m_size)
{
  int	i;
  int	s;

  i = 0;
  while (m_size[i] && m_size[i] >= '0' && m_size[1] <= '9')
    i += 1;
  if (m_size[i] || (s = atoi(m_size)) < 10 || s > 120)
    fprintf(stderr, M_SIZE_MSG);
  if (t_nbr[0] < '1' || t_nbr[0] > '6' || t_nbr[1])
    fprintf(stderr, T_NBR_MSG);
  else
    {
      t_nbr[0] -= 48;
      if (!m_size[i] && s >= 10 && s <= 120)
        return (s);
    }
  return (FAILURE);
}

int	get_nbr_team(char *map, char m_size)
{
  char	teams[6];
  short	check;
  short	cpt;
  short	i;

  i = 0;
  cpt = 0;
  while (i < m_size * m_size)
    {
      if (map[i])
        {
	  check = 0;
	  while (check < cpt && teams[check] != map[i])
	    check += 1;
	  if (check == cpt)
	    teams[cpt++] = map[i];
	}
      i += 1;
    }
  return (cpt);
}

int	surround(char enemies[8], int index)
{
  int	i;

  if (index >= 2)
    while (--index >= 0)
      {
        i = 0;
        while (i < index)
          {
            if (enemies[i] == enemies[index])
              return (SUCCESS);
            i += 1;
          }
      }
  return (FAILURE);
}

int	is_surrounded(char *map, short pos, char t_nbr, char m_size)
{
  char	enemies[8];
  int	i;

  i = 0;
  if (pos && map[pos - 1] && map[pos - 1] != t_nbr)
    enemies[i++] = map[pos - 1];
  if (pos + 1 < m_size * m_size && map[pos + 1] && map[pos + 1] != t_nbr)
    enemies[i++] = map[pos + 1];
  if (pos >= m_size && map[pos - m_size] && map[pos - m_size] != t_nbr)
    enemies[i++] = map[pos - m_size];
  if (pos > m_size && pos % m_size &&
      map[pos - m_size - 1] && map[pos - m_size - 1] != t_nbr)
    enemies[i++] = map[pos - m_size - 1];
  if (pos > m_size && (pos + 1) % m_size &&
      map[pos - m_size + 1] && map[pos - m_size + 1] != t_nbr)
    enemies[i++] = map[pos - m_size + 1];
  if (pos < m_size * m_size - m_size && pos % m_size &&
      map[pos + m_size - 1] && map[pos + m_size - 1] != t_nbr)
    enemies[i++] = map[pos + m_size - 1];
  if (pos < m_size * m_size - m_size && (pos + 1) % m_size &&
      map[pos + m_size + 1] && map[pos + m_size + 1] != t_nbr)
    enemies[i++] = map[pos + m_size + 1];
  return (surround(enemies, i));
}
