/*
** main.c for server in /home/menich_a/rendu/PSU_2014_myftp/srcs/server
**
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
**
** Started on  Tue Mar 10 12:24:49 2015 Anatole Menichetti
** Last update Thu Mar 26 10:26:26 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

void		my_sigint(int sig)
{
  static int	fd = -1;

  if (sig < 0)
    fd = -sig;
  if (sig == SIGINT)
    {
      if (fd > 0 && close(fd) == -1)
	{
	  perror(ESCLOSE);
	  exit(-1);
	}
      else
	putstr("\nmyftp: server: received SIGINT: closing server's socker.\n");
    }
}

int		main(int ac, char **av)
{
  int		fd;
  t_proto	*p;
  t_sockin	s_in;

  if (ac != 2)
    return (fputstr(2, EUSAGE));
  if (!(p = getprotobyname(PROTONAME)))
    return (my_perror(ETCP, EXIT_FAILURE, 0, 0));
  if ((fd = socket(AF_INET, SOCK_STREAM, p->p_proto)) == -1)
    return (my_perror(ESOCKET, EXIT_FAILURE, 0, 0));
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(atoi(av[1]));
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    return (my_perror(EBIND, EXIT_FAILURE, fd, 0));
  my_sigint(-fd);
  if (signal(SIGINT, &my_sigint) == SIG_ERR)
    return (my_perror(ESIGNAL, EXIT_FAILURE, fd, 0));
  if (listen(fd, 3) == -1)
    return (my_perror(ELISTEN, EXIT_FAILURE, fd, 0));
  ac = handle_clients(fd, (av = get_pwd(av[0], "server")));
  free_pwds(av);
  if (!ac)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
