/*
** handle_connection.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 13:06:31 2015 Anatole Menichetti
** Last update Sat Apr 11 12:22:40 2015 audurier julien
*/

#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../../includes/myirc.h"
#include "../../includes/client.h"

int		connect_to_server(const char *addr, int port)
{
  int		fd;
  t_proto	*p;
  t_sin		sin;
  t_slen	len;

  len = sizeof(t_sin);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(addr);
  if (!(p = getprotobyname(PROTONAME)))
    return (-msg_error(EPROTONAME, 1));
  if ((fd = socket(AF_INET, SOCK_STREAM, p->p_proto)) == -1)
    return (-msg_error(ESOCKET, 1));
  if (connect(fd, (const struct sockaddr *)&sin, len) == -1)
    return (-msg_error(ECONNECT, 1));
  return (fd);
}

static int	get_port(char *cmd)
{
  int		port;

  port = 6667;
  if (cmd[0])
    port = atoi(cmd + 1);
  return (port);
}

int		handle_connection(char *buff)
{
  char		**cmd;
  char		*addr;
  int		port;
  int		i;

  i = 0;
  if (!(cmd = str_to_cmdtab(buff)))
    return (-msg_error(EALLOC, 1));
  if (tablen(cmd) > 2 || !cmd[1])
    {
      free_tab(cmd);
      return (msg_error(err_serv("461 ", "", "CONNECT",
				 " :Not enough parameters\r\n"), 0));
    }
  while (cmd[1][i] && cmd[1][i] != ':')
    i += 1;
  port = get_port(cmd[1] + i);
  cmd[1][i] = '\0';
  if (!(addr = strdup(cmd[1])))
    {
      free_tab(cmd);
      return (-msg_error(EALLOC, 1));
    }
  free_tab(cmd);
  return (connect_to_server(addr, port));
}

int		process_server_cmd(char *buff, int *fd, int ret)
{
  int		new_fd;

  if ((new_fd = handle_connection(buff)) <= 0)
    return (new_fd);
  if (new_fd == 1)
    return (ret);
  if (fputstr(*fd, "QUIT\n") == -1)
    return (-msg_error(EWRITE, 1));
  *fd = new_fd;
  return (ret);
}
