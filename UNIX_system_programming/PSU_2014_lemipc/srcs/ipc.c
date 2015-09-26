/*
** ipc.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc/srcs
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  3 18:56:43 2015 Anatole Menichetti
** Last update Sun Mar  8 22:17:59 2015 Anatole Menichetti
*/

#include <errno.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "../includes/lemipc.h"

int	ipc_rm(int ids[3])
{
  if ((ids[SHM] != -1 && shmctl(ids[SHM], IPC_RMID, 0) == -1) ||
      (ids[SEM] != -1 && semctl(ids[SEM], IPC_RMID, 0) == -1) ||
      (ids[MSG] != -1 && msgctl(ids[MSG], IPC_RMID, 0) == -1))
    return (my_perror());
  return (SUCCESS);
}

int	msg_get(int ids[3], key_t key, int m_size)
{
  ids[MSG] = msgget(key, SHM_R | SHM_W);
  if (ids[MSG] == -1)
    {
      if ((ids[MSG] = msgget(key, IPC_CREAT | SHM_R | SHM_W)) == -1)
	return (my_perror());
    }
  else
    m_size = receive_msg(ids[MSG], T_MAP, 0);
  send_msg(ids[MSG], T_MAP, m_size);
  return (m_size);
}

int	send_msg(int id, int type, int data)
{
  t_msg	msg;

  msg.mtype = type;
  msg.data = data;
  return (msgsnd(id, &msg, sizeof(t_msg), 0));
}

int	receive_msg(int id, int type, int flags)
{
  t_msg	msg;
  int	data;

  if ((data = msgrcv(id, &msg, sizeof(t_msg), type, flags)) != -1)
    data = msg.data;
  else
    if (errno != ENOMSG)
      my_perror();
  return (data);
}

int	my_sem_op(int id, struct sembuf *sops, int op)
{
  sops->sem_num = 0;
  sops->sem_flg = 0;
  sops->sem_op = op;
  if (semop(id, sops, 1))
    return (my_perror());
  return (SUCCESS);
}
