/*
** client.c for client in /home/menich_a/rendu/PSU_2013_minitalk/client/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  4 12:05:26 2014 menich_a
** Last update Sun Mar 23 14:34:51 2014 menich_a
*/

#include <signal.h>
#include "client.h"

int		my_pause(int action)
{
  static int	pause;

  if (action == CHECK)
    return (pause);
  else
    pause = action;
  return (pause);
}


void		break_pause(int signal)
{
  if (signal == SIGUSR1)
    my_pause(BREAK_PAUSE);
  if (signal == SIGUSR2)
    {
      my_putstr("server allready working, joined queue.\n");
      my_pause(SUSPEND);
    }
}

int		send_signal_msg(int server_pid, int size)
{
  int		i;
  int		cpt;

  i = 0;
  while (i < size)
    {
      my_pause(PAUSE);
      if (kill(server_pid, SIGUSR1) == FAILURE)
	return (msg_error("client: error: SIGUSR1 cannot reach server.\n"));
      cpt = 0;
      while (my_pause(CHECK))
	if (cpt++ >= PAUSE_MAX && my_pause(CHECK) != SUSPEND)
	  my_pause(BREAK_PAUSE);
      i = i + 1;
    }
  my_pause(PAUSE);
  if (kill(server_pid, SIGUSR2) == FAILURE)
    return (msg_error("client: error: SIGUSR2 cannot reach server\n"));
  cpt = 0;
  while (my_pause(CHECK))
    if (cpt++ >= PAUSE_MAX && my_pause(CHECK) != SUSPEND)
      my_pause(BREAK_PAUSE);
  return (SUCCESS);
}

int		send_msg(int server_pid, char *msg, int size)
{
  int		i;
  int		percentage;
  int		old_perc;

  i = 0;
  old_perc = 0;
  my_putstr("Starting emission: 0% completed.\n");
  while (msg[i])
    {
      if (send_signal_msg(server_pid, msg[i]))
	return (FAILURE);
      percentage = (i * 100) / size;
      if (percentage != old_perc)
	{
	  old_perc = percentage;
	  my_putstr("\rLoading: ");
	  my_put_nbr(percentage);
	  my_putstr("% completed...");
	}
      i = i + 1;
    }
  if (send_signal_msg(server_pid, 0))
    return (FAILURE);
  my_putstr("\n100% completed: end of emission.\n");
  return (SUCCESS);
}

int		main(int ac, char **av)
{
  int		server_pid;
  int		i;

  i = 0;
  if (ac < 3)
    return (msg_error("client: error: usage: ./client [server PID] [msg].\n"));
  while (av[2][i] != '\0')
    {
      if ((av[2][i] < 32 || av[2][i] > 126) && av[2][i] != '\n')
	return (msg_error("client: error: message corupted.\n"));
      i = i + 1;
    }
  server_pid = my_getnbr(av[1]);
  if (server_pid <= 0)
    return (msg_error("client: error: invalid server PID.\n"));
  signal(SIGUSR1, &break_pause);
  signal(SIGUSR2, &break_pause);
  if (send_msg(server_pid, av[2], my_strlen(av[2])) == FAILURE)
    return (1);
  return (SUCCESS);
}
