/*
** lemipc.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  3 20:00:12 2015 Anatole Menichetti
** Last update Sun Mar  8 23:05:29 2015 Anatole Menichetti
*/

#include "../includes/lemipc.h"

int		end_game(int ids[3], int is_last_player, char t_nbr)
{
  if (is_last_player)
    {
      printf("Team %d won!!\n", t_nbr);
      return (ipc_rm(ids));
    }
  return (SUCCESS);
}

int		leave_game(char *map, size_t pos, char m_size)
{
  int		i;

  i = 0;
  map[pos] = 0;
  while (i < m_size * m_size)
    {
      if (map[i])
	return (FAILURE);
      ++i;
    }
  return (SUCCESS);
}

int		play_turn(t_player *p, char is_first_player, char gui, struct sembuf *sops)
{
  if (!display_map(p, is_first_player, gui))
    return (FAILURE);
  if (is_first_player != 2 &&
      is_surrounded(p->map, p->pos, p->t_nbr, p->m_size))
    {
      ((char *)p->map)[p->pos] = 0;
      if (!my_sem_op(p->ids[SEM], sops, 1))
	return (FAILURE);
      if (is_first_player)
	is_first_player = 2;
      else
	return (SUCCESS);
    }
  if (is_first_player != 2)
    p->pos = move(p->map, p->pos, p->t_nbr, p->m_size);
  if (!my_sem_op(p->ids[SEM], sops, 1))
    return (FAILURE);
  return (SUCCESS + 1);
}

int		join_game(t_player *p)
{
  struct sembuf	sops;
  int		ret;
  char		gui;
  char		is_first_player;

  is_first_player = 0;
  if (!p->pos)
    is_first_player = 1;
  if ((gui = receive_msg(p->ids[MSG], T_GUI, IPC_NOWAIT) + 1))
    send_msg(p->ids[MSG], T_GUI, 0);
  while ((ret = my_sem_op(p->ids[SEM], &sops, -1)) &&
	 get_nbr_team(p->map, p->m_size) > 1)
    {
      ret = play_turn(p, is_first_player, gui, &sops);
      if (ret <= 1)
	return (ret);
    }
  if (!ret)
    return (my_perror());
  if (is_first_player != 2)
    ret = leave_game(p->map, p->pos, p->m_size);
  display_map(p, is_first_player, gui);
  if (!my_sem_op(p->ids[SEM], &sops, 1))
    return (my_perror());
  return (end_game(p->ids, ret, p->t_nbr));
}
