/*
** main.c for client in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
**
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
**
** Started on  Tue Mar 10 13:25:24 2015 Anatole Menichetti
** Last update Sat Mar 28 18:23:05 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

void		my_sigint(int sig)
{
  if (sig == SIGINT)
    display_prompt(0, 0);
}

int		connect_to_server(const char *addr, int port)
{
  int		fd;
  t_proto	*p;
  t_sockin	s_in;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(addr);
  if (!(p = getprotobyname(PROTONAME)))
    return (my_perror(ETCP, FAILURE, 0, 1));
  if ((fd = socket(AF_INET, SOCK_STREAM, p->p_proto)) == -1)
    return (my_perror(ESOCKET, FAILURE, 0, 1));
  if (connect(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    return (my_perror(ECONNECT, FAILURE, fd, 1));
  return (fd);
}

int		main(int ac, char **av)
{
  int		fd;
  char		**pwds;
  int		ret;

  if (ac != 3)
    return (fputstr(2, EUSAGE));
  if (!(fd = connect_to_server(av[1], atoi(av[2]))))
    return (EXIT_FAILURE);
  if (signal(SIGINT, &my_sigint) == SIG_ERR)
    return (my_perror(ESIGNAL, FAILURE, fd, 1));
  pwds = get_pwd(av[0], "client");
  ret = launch_client(fd, 0, 0, pwds);
  free_pwds(pwds);
  if (!ret)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
