/*
** main.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 14:14:02 2015 Anatole Menichetti
** Last update Sun Apr 12 11:11:46 2015 Anatole Menichetti
*/

#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include "../../includes/server.h"
#include "../../includes/myirc.h"

static char	g_sigint = 0;

static void	handle_sigint(int signal)
{
  if (signal == SIGINT)
    {
      g_sigint = 1;
      msg_error(ESIGINT, 0);
    }
}

static int	create_server(int port, t_fd **fds)
{
  int		fd;
  t_sin		sin;
  t_proto	*p;

  if (!(p = getprotobyname(PROTONAME)))
    return (msg_error(EPROTONAME, 1));
  if ((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (msg_error(ESOCKET, 1));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    return (msg_error(EBINDING, 1));
  if (listen(fd, SOMAXCONN) == -1)
    return (msg_error(ELISTEN, 1));
  if (push_fd(fds, fd, FD_SERVER, handle_server))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	my_select(t_fd *fds, fd_set *set)
{
  t_fd		*ptr;
  int		fd_max;
  t_tv		tv;

  ptr = fds;
  fd_max = 0;
  tv.tv_sec = 5;
  tv.tv_usec = 0;
  FD_ZERO(set);
  while (ptr)
    {
      FD_SET(ptr->fd, set);
      if (ptr->fd > fd_max)
	fd_max = ptr->fd;
      ptr = ptr->next;
    }
  fd_max = select(fd_max + 1, set, NULL, NULL, &tv);
  if (fd_max < 0)
    return (-msg_error(ESELECT, 1));
  if (!fd_max || !tv.tv_sec)
    return (0);
  return (fd_max);
}

static int	my_exit(t_fd *fds, int ret)
{
  t_fd		*ptr;
  t_fd		*tmp;

  ptr = fds;
  while (ptr)
    {
      tmp = ptr;
      ptr = ptr->next;
      pop_fd(&fds, tmp);
      free(tmp);
    }
  return (ret);
}

int		main(int ac, char **av)
{
  fd_set	set;
  t_fd		*fds;
  int		ret;

  fds = NULL;
  if (ac != 2)
    return (msg_error(EUSAGE, 0));
  if (signal(SIGINT, &handle_sigint) == SIG_ERR)
    return (msg_error(ESIGNAL, 1));
  if (create_server(atoi(av[1]), &fds) == EXIT_FAILURE)
    return (my_exit(fds, EXIT_FAILURE));
  while (!g_sigint)
    {
      ret = my_select(fds, &set);
      if (ret < 0)
	return (my_exit(fds, EXIT_FAILURE));
      if (ret > 0)
	if (handle_selection(fds, &set) == EXIT_FAILURE)
	  return (my_exit(fds, EXIT_FAILURE));
    }
  return (my_exit(fds, EXIT_SUCCESS));
}
