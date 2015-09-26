/*
** handler.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 19:09:31 2015 Anatole Menichetti
** Last update Thu Apr 16 12:07:51 2015 Anatole Menichetti
*/

#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/server.h"
#include "../../includes/myirc.h"

static const t_cmd	g_cmd_tab[] =
  {
    {"NICK", &my_nickname},
    {"LIST", &my_list},
    {"JOIN", &my_join},
    {"PART", &my_part},
    {"PRIVMSG", &my_msg},
    {"QUIT", &my_quit},
    {"NAMES", &my_names}
  };

static int	handle_cmd(t_fd *fds, t_fd *self, t_cmd cmd, char **params)
{
  char		*code;

  code = cmd.cmd(fds, self, params + 1);
  free_tab(params);
  if (!code)
    return (msg_error(EALLOC, 1));
  if (strcmp(cmd.name, "QUIT"))
    if (fputstr(self->fd, code) == -1)
      return (msg_error(EWRITE, 1));
  free(code);
  return (EXIT_SUCCESS);
}

static int	handle_client(t_fd *fds, t_fd *self)
{
  int		ret;
  char		**cmd;
  char		buff[BUFF_SIZE + 1];
  int		i;

  i = 0;
  ret = circular_read(self->fd, buff);
  if (ret <= 0)
    return (pop_fd(&fds, self));
  if (ret > 1 && buff[ret - 2] == '\r')
    buff[ret - 2] = '\0';
  else
    buff[ret - 1] = '\0';
  if (!(cmd = str_to_cmdtab(buff)))
    return (msg_error(EALLOC, 1));
  while (i < NBR_CMDS && strcmp(g_cmd_tab[i].name, cmd[0]))
    i += 1;
  if (i == NBR_CMDS)
    {
      free_tab(cmd);
      if (fputstr(self->fd, "command not found\r\n") == -1)
	return (msg_error(EWRITE, 1));
      return (EXIT_SUCCESS);
    }
  return (handle_cmd(fds, self, g_cmd_tab[i], cmd));
}

int		handle_server(t_fd *fds, t_fd *self)
{
  int		ret;
  int		client_fd;
  t_sin		client_sin;
  t_slen	client_sin_len;

  client_sin_len = sizeof(client_sin);
  client_fd = accept(self->fd, (struct sockaddr *)&client_sin, &client_sin_len);
  if (client_fd < 0)
    return (msg_error(EACCEPT, 1));
  printf("New client added: %d\n", client_fd);
  ret = push_fd(&fds, client_fd, FD_CLIENT, handle_client);
  if (fputstr(client_fd, "NOTICE Auth :Welcome to myIRC!\r\n")
      == -1)
    return (msg_error(EWRITE, 1));
  return (ret);
}

int		handle_selection(t_fd *fds, fd_set *set)
{
  t_fd		*ptr;
  t_fd		*tmp;

  ptr = fds;
  while (ptr)
    {
      if (FD_ISSET(ptr->fd, set))
        if (ptr->handler_fptr(fds, ptr) == EXIT_FAILURE)
          return (EXIT_FAILURE);
      if (ptr->state == DOWN)
	{
	  tmp = ptr;
	  ptr = ptr->next;
	  free(tmp);
	}
      else
	ptr = ptr->next;
    }
  return (EXIT_SUCCESS);
}
