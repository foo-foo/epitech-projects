/*
** init.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc/srcs
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Mar  6 10:46:36 2015 Anatole Menichetti
** Last update Sun Mar  8 23:00:49 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../includes/lemipc.h"

int	init_player_pos(char *map, char t_nbr, char m_size)
{
  int	i;
  int	check;

  i = 0;
  check = -1;
  while (i < m_size * m_size)
    {
      if (!map[i])
	check = 1;
      if (map[i] == t_nbr && get_free_pos(map, i, m_size) >= 0)
	return (get_free_pos(map, i, m_size));
      ++i;
    }
  if (check < 0)
    {
      fprintf(stderr, NO_PLACE_MSG);
      return (-1);
    }
  if ((check = starting_block_pos(map, m_size)) < 0)
    {
      check = random() % (m_size * m_size);
      while (map[check])
	check = random() % (m_size * m_size);
    }
  return (check);
}

int	init_player(t_player *p)
{
  int	msg;

  msg = p->t_nbr;
  p->map = shmat(p->ids[SHM], 0, SHM_R | SHM_W);
  if ((void *)p->map == (void *)-1)
    return (my_perror());
  if ((p->pos = init_player_pos(p->map, p->t_nbr, p->m_size)) == -1)
    return (FAILURE);
  p->map[p->pos] = p->t_nbr;
  usleep(100000);
  if (get_nbr_team(p->map, p->m_size) == 1)
    while (msg == p->t_nbr)
      msg = receive_msg(p->ids[MSG], T_JOIN, 0);
  if (msg == -1)
    return (FAILURE);
  if (send_msg(p->ids[MSG], T_JOIN, msg))
    return (my_perror());
  return (SUCCESS);
}

int	init_sh_resources(key_t key, t_player *p)
{
  void	*addr;
  int	c_flags;


  if (!(p->m_size = msg_get(p->ids, key, p->m_size)))
    return (FAILURE);
  if ((p->ids[SHM] = shmget(key, p->m_size * p->m_size, SHM_R | SHM_W)) == -1 ||
      (p->ids[SEM] = semget(key, 1, SHM_R | SHM_W)) == -1)
    {
      c_flags = IPC_CREAT | SHM_R | SHM_W;
      if ((p->ids[SHM] = shmget(key, p->m_size * p->m_size, c_flags)) == -1 ||
          (p->ids[SEM] = semget(key, 1, c_flags)) == -1 ||
          semctl(p->ids[SEM], 0, SETVAL, 1) == -1)
        return (my_perror());
      addr = shmat(p->ids[SHM], 0, SHM_R | SHM_W);
      if (addr == (void *)-1)
        return (my_perror());
      create_map(addr, p->m_size);
    }
  return (SUCCESS);
}

char	init_game(t_player *p)
{
  key_t	key;

  key = ftok("/", 0);
  if (key == -1)
    return (my_perror());
  if (!init_sh_resources(key, p) || !init_player(p))
    return (FAILURE);
  return (SUCCESS);
}

int	init_params(int ac, char **av)
{
  char	t_nbr[2];

  srandom(time(0) * getpid());
  if (ac != 3)
    fprintf(stderr, USAGE_MSG);
  if (ac < 2)
    {
      t_nbr[0] = random() % 6 + 1 + 48;
      t_nbr[1] = '\0';
      av[1] = t_nbr;
    }
  if (ac < 3)
    av[2] = "20";
  return (check_params(av[1], av[2]));
}
