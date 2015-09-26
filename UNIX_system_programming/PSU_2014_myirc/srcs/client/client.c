/*
** client.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 13:03:17 2015 Anatole Menichetti
** Last update Sat Apr 11 11:46:11 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/myirc.h"
#include "../../includes/client.h"

static int	handle_server(int fd, int *sel)
{
  char		buff[BUFF_SIZE + 1];
  int		ret;

  ret = circular_read(fd, buff);
  if (ret < 0)
    return (-msg_error(EREAD, 1));
  if (*sel)
    putstr("\n");
  if (!ret)
    {
      msg_error(ELOST, 0);
      return (EXIT_SUCCESS);
    }
  if (ret > 2)
    {
      buff[ret] = '\0';
      putstr("\033[36m");
      putstr(buff);
      putstr("\033[0m");
    }
  *sel = 1;
  putstr("\033[35m~> \033[0m");
  return (ret);
}

static int	my_select(int fd, fd_set *set)
{
  t_tv		tv;
  int		ret;

  FD_ZERO(set);
  FD_SET(0, set);
  FD_SET(fd, set);
  tv.tv_sec = 5;
  tv.tv_usec = 0;
  ret = select(fd + 1, set, NULL, NULL, &tv);
  if (ret < 0)
    return (msg_error(ESELECT, 1));
  if (!ret || !tv.tv_sec)
    return (0);
  return (ret);
}

int		launch_client(int fd)
{
  int		sel;
  int		ret1;
  int		ret2;
  fd_set	set;

  ret2 = 42;
  sel = 0;
  while (ret2)
    {
      ret2 = 42;
      ret1 = my_select(fd, &set);
      if (ret1 < 0)
        return (EXIT_FAILURE);
      if (ret1 > 0)
        if ((FD_ISSET(0, &set) &&
	     (ret2 = handle_stdin(&fd, &sel)) < 0) ||
            (ret2 && FD_ISSET(fd, &set) &&
	     (ret2 = handle_server(fd, &sel)) < 0))
          return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
