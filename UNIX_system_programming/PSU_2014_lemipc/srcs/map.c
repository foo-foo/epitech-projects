/*
** map.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  3 15:05:41 2015 Anatole Menichetti
** Last update Sun Mar  8 22:16:13 2015 Anatole Menichetti
*/

#include "../includes/lemipc.h"

void	create_map(char *map, char m_size)
{
  int	i;

  i = 0;
  while (i < m_size * m_size)
    map[i++] = 0;
}

void	show_map(char *map, char m_size)
{
  int	i;

  i = 0;
  while (i++ <= m_size + 1)
    printf("-");
  printf("\n");
  i = 0;
  while (i < m_size * m_size)
    {
      if (i % m_size == 0)
        printf("|");
      if (map[i])
        printf("%d", map[i]);
      else
        printf("o");
      if (i++ && i % m_size == 0)
        printf("|\n");
    }
  i = 0;
  while (i++ <= m_size + 1)
    printf("-");
  printf("\n");
}

int	display_map(t_player *p, char is_first_player, char gui)
{
  if (is_first_player)
    {
      if (gui)
	{
          if (send_msg(p->ids[MSG], T_REFRESH, 0) ||
              receive_msg(p->ids[MSG], T_DONE, 0) == -1)
            return (FAILURE);
        }
      else
        show_map(p->map, p->m_size);
    }
  return (SUCCESS);
}
