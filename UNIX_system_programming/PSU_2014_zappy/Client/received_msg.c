/*
** received_msg.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jun 15 09:17:52 2015 Anatole Menichetti
** Last update Wed Jun 24 02:12:08 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Parse msg from other type CALL or NEED_PEOPLE.
*/
static void	decrypt_msg_from_type(t_player *p, int msg[6],
				      char *data, int type)
{
  int		i;

  i = 0;
  if (!type)
    {
      msg[TYPE] = CALL;
      msg[EXTERN_PID] = atoi(data);
      return ;
    }
  msg[TYPE] = NEED_PEOPLE;
  while (data[i] != ' ')
    i += 1;
  data[i] = '\0';
  msg[TEAM] = 0;
  if (!strcmp(data, p->team_name))
    msg[TEAM] = 1;
  data[i++] = ' ';
  data += i;
  i = 0;
  while (data[i] != ' ')
    i += 1;
  data[i] = '\0';
  msg[EXTERN_PID] = atoi(data);
  data[i] = ' ';
  msg[LVL] = atoi(data + i + 1);
}

/*
**		Parse msg.
*/
static void	decrypt_msg(t_player *p, char *data, int msg[6])
{
  int		type;
  int		i;

  i = 0;
  type = 0;
  msg[DIR] = data[8] - 48;
  data += 10;
  while (data[i])
    {
      if (data[i] == ' ')
	type += 1;
      i += 1;
    }
  if (type == 1)
    {
      while (data[i] != ' ')
	i -= 1;
      data[i] = '\0';
      msg[TYPE] = CAN_I_JOIN;
      msg[PID] = atoi(data);
      data[i] = ' ';
      msg[EXTERN_PID] = atoi(data + i + 1);
    }
  else
    decrypt_msg_from_type(p, msg, data, type);
}

/*
**		Prepare to broadcast.
*/
void		prepare_answer(t_player *p, int type, int extern_pid, int pid)
{
  int		n;

  n = p->nbr_broadcasts;
  if (!n || type != p->broadcasts[n - 1][TYPE] ||
      extern_pid != p->broadcasts[n -1][EXTERN_PID] ||
      pid != p->broadcasts[n -1][PID])
    {
      if (type == CAN_I_JOIN)
	p->waiting_answer = extern_pid;
      p->broadcasts[n][TYPE] = type;
      p->broadcasts[n][EXTERN_PID] = extern_pid;
      p->broadcasts[n][PID] = pid;
      p->need_to_broadcast = 1;
      if (n < 9)
	p->nbr_broadcasts += 1;
    }
}

/*
**		Reaction to a msg that was addressed to me.
*/
static void	did_i_received_private_msg(t_player *p, int msg[6])
{
  if (msg[TYPE] == CAN_I_JOIN && msg[PID] == p->pid)
    {
      if ((!p->waiting_answer ||
	   (p->waiting_answer == msg[EXTERN_PID] &&
	    msg[EXTERN_PID] < p->pid)) && p->people_needed)
	{
	  p->waiting_answer = 0;
	  p->people_needed -= 1;
	  p->nbr_broadcast_emitted = 0;
	  prepare_answer(p, U_CAN_JOIN, msg[EXTERN_PID], p->pid);
	}
      else
	prepare_answer(p, U_CAN_JOIN, msg[EXTERN_PID], 0);
    }
  if (msg[TYPE] == U_CAN_JOIN && p->waiting_answer && msg[PID] == p->pid)
    {
      p->waiting_answer = 0;
      p->nbr_broadcast_emitted = 0;
      p->target_pid = msg[EXTERN_PID];
      p->target_dir = -1;
    }
}

/*
**		Analyse and react to a msg received.
*/
int		received_msg(t_player *p, char *data)
{
  int		msg[6];

  decrypt_msg(p, data, msg);
  if (data[strlen(data) - 1] == '!')
    msg[TYPE] = U_CAN_JOIN;
  if (msg[TYPE] == CAN_I_JOIN && msg[PID] == -1 &&
      msg[EXTERN_PID] == p->target_pid)
    p->target_pid = 0;
  if (msg[TYPE] == NEED_PEOPLE && msg[TEAM] &&
      msg[LVL] == (int)p->lvl && p->stuff[FOOD] >= MIN_FOOD && !p->target_pid
      && (p->people_needed == (int)p->requirements[p->lvl - 1][0] - 1 ||
       p->nbr_broadcast_emitted > NB_MAX_WITHOUT_RECRUIT))
    {
      if (p->people_needed < (int)p->requirements[p->lvl - 1][0] - 1)
	p->need_to_kick = 1;
      prepare_answer(p, CAN_I_JOIN, msg[EXTERN_PID], p->pid);
    }
  did_i_received_private_msg(p, msg);
  if (p->target_pid && msg[TYPE] == CALL && p->target_pid == msg[EXTERN_PID])
    {
      if (p->look_for_target)
	p->look_for_target = 2;
      p->target_dir = msg[DIR];
    }
  return (1);
}
