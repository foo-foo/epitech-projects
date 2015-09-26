/*
** server.c for server in /home/menich_a/rendu/PSU_2013_minitalk/server/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  4 11:47:46 2014 menich_a
** Last update Sun Mar 23 12:09:37 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "server.h"

void			init_client(t_client *client)
{
  static int		i;

  if (i == 0)
    {
      client->msg = NULL;
      client->queue = NULL;
      client->c = 0;
      i = 42;
    }
}

void			adapt_client(t_client *client, int actual_pid)
{
  client->msg = add_char(client->msg, client->c);
  if (client->msg == NULL)
    exit(msg_error("server: error: malloc failed (msg).\n"));
  if (client->c == 0)
    {
      my_putstr("client ");
      my_put_nbr(client->queue[0]);
      my_putstr(" :\n");
      my_putstr(client->msg);
      my_putchar('\n');
      if (!my_strcmp(client->msg, "#kill server"))
	my_exit(client->msg, client->queue);
      free(client->msg);
      client->msg = NULL;
      client->queue = remove_client(client->queue, actual_pid);
      if (client->queue)
	client->c = 1;
    }
  else
    client->c = 0;
}

void			server(int signal, siginfo_t *c_inf, __attribute__((unused))void *param)
{
  static t_client	client;
  int			actual_pid;

  init_client(&client);
  if (client.queue == NULL || c_inf->si_pid != client.queue[0])
    if ((client.queue = add_client(client.queue, c_inf->si_pid, 0)) == NULL)
      exit(msg_error("server: error: malloc failed (queue).\n"));
  if (c_inf->si_pid != client.queue[0])
    {
      my_putstr("client ");
      my_put_nbr(c_inf->si_pid);
      my_putstr(" joined end of queue.\n");
      return;
    }
  actual_pid = c_inf->si_pid;
  if (signal == SIGUSR1)
    client.c = client.c + 1;
  if (signal == SIGUSR2)
    adapt_client(&client, actual_pid);
  kill(actual_pid, SIGUSR1);
  if (client.queue && client.queue[0] != actual_pid)
    if (kill(client.queue[0], SIGUSR1) == -1)
      exit(msg_error("server: error: cannot reach client.\n"));
}

int			main(void)
{
  pid_t			pid;
  t_sig			sig;

  sig.sa_flags = SA_SIGINFO;
  sig.sa_sigaction = server;
  pid = getpid();
  if (pid == FAILURE)
    return (msg_error("server: error: cannot get server PID\n"));
  my_putstr(INIT_MSG);
  my_put_nbr(pid);
  my_putstr(".\n");
  sigaction(SIGUSR1, &sig, NULL);
  sigaction(SIGUSR2, &sig, NULL);
  while (42)
    pause();
  return (SUCCESS);
}
