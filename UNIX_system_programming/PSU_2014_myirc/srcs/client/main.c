/*
** main.c for client in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
**
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
**
** Started on  Tue Mar 10 13:25:24 2015 Anatole Menichetti
** Last update Sat Apr 11 11:48:09 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../includes/myirc.h"
#include "../../includes/client.h"

static int	wait_for_connection(void)
{
  int		ret;
  char		buff[BUFF_SIZE + 1];

  while ((ret = circular_read(0, buff)) > 0)
    {
      buff[ret] = '\0';
      if (ret > 7 && !strncmp(buff, "/server", 7) &&
	  (buff[7] == ' ' || buff[7] == '\t' || buff[7] == '\n'))
	{
	  if ((ret = handle_connection(buff)) != 1)
	    return (ret);
	}
      else
	msg_error(ENOTCONNECTED, 0);
    }
  if (ret < 0)
    return (-msg_error(EREAD, 1));
  return (0);
}

int		main(int ac, char **av)
{
  int		fd;
  int		ret;

  if (ac > 3 || ac == 2)
    return (msg_error(EUSAGE, 0));
  if (ac == 3)
    fd = connect_to_server(av[1], atoi(av[2]));
  else
    fd = wait_for_connection();
  if (fd <= 0)
    return (EXIT_FAILURE);
  ret = launch_client(fd);
  if (close(fd) == -1)
    return (msg_error(ECLOSE, 1));
  return (ret);
}
