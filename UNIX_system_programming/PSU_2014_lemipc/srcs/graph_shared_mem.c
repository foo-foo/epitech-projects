/*
** graph_shared_mem.c for  in /home/bencha_a/PSU_2014_lemipc
** 
** Made by Aniss Bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Sat Mar  7 15:28:18 2015 Aniss Bencharif
** Last update Sun Mar  8 23:02:54 2015 Anatole Menichetti
*/

#include "../includes/graph.h"

void		acces_shared_mem(SDL_Surface *screen)
{
  static key_t	key;
  static int	id;
  static int	size = 0;
  static int	msg_id;
  t_msg		msg;

  key = ftok("/", 0);
  if ((msg_id = msgget(key, SHM_R | SHM_W)) == -1)
    {
      printf("lemipc graphic: no size sent to get the map.\n");
      return;
    }
  if (msgrcv(msg_id, &msg, sizeof(msg), T_MAP, 0) == -1)
    exit(-1);
  size = msg.data;
  msg.mtype = T_MAP;
  if (msgsnd(msg_id, &msg, sizeof(msg), 0))
    exit(-1);
  msg.mtype = T_GUI;
  if (msgsnd(msg_id, &msg, sizeof(msg), 0))
    exit(-1);
  if ((id = shmget(key, size * size, SHM_R)) == -1)
    printf("lemipc graphic: cannot acces the shared memory.\n");
  refresh_screen(size, screen, msg_id, id);
}

int		refresh_screen(int size, SDL_Surface *screen, int msg_id, int id)
{
  int		check;
  void		*addr;
  t_msg		msg;

  check = 0;
  addr = shmat(id, NULL, SHM_R);
  while (get_nbr_player(addr, size) != -1)
    {
      if (!check)
        check = 1;
      SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
      init_picture(screen, addr, size);
      usleep(200000);
      if (check)
        {
          msg.mtype = T_DONE;
          msgsnd(msg_id, &msg, sizeof(msg), 0);
        }
      if (msgrcv(msg_id, &msg, sizeof(msg), T_REFRESH, 0) == -1)
	exit(0);
      addr = shmat(id, NULL, SHM_R);
    }
  return (0);
}
