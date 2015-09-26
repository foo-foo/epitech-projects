/*
** messages.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 14:07:45 2015 Anatole Menichetti
** Last update Sun Apr 12 12:40:13 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/myirc.h"
#include "../../includes/server.h"

static int	send_grouped_msg(t_fd *fds, t_fd *self, char *channel, char *msg)
{
  t_fd		*ptr;
  int		i;

  ptr = fds;
  while (ptr)
    {
      i = 0;
      if (ptr != self && ptr->channels)
	{
	  while (ptr->channels[i] && strcmp(ptr->channels[i], channel))
	    i += 1;
	  if (ptr->channels[i])
	    if (fputstr(ptr->fd, msg) == -1)
	      return (0);
	}
      ptr = ptr->next;
    }
  return (1);
}

static char	*my_channel_msg(t_fd *fds, t_fd *self, char *dest, char *msg)
{
  int		i;
  int		ret;

  i = 0;
  ret = 42;
  if (!self->channels)
    {
      free(msg);
      return (err_serv("404 ", self->nick, "", " :Cannot send to channel\r\n"));
    }
  while (self->channels[i])
    {
      if (!strcmp(dest, self->channels[i]))
	if (!(ret = send_grouped_msg(fds, self, self->channels[i], msg)))
	  return (NULL);
      i += 1;
    }
  free(msg);
  if (ret == 42)
    return (err_serv("403 ", self->nick, dest, " :No such channel\r\n"));
  return (strdup("\r\n"));
}

static char	*check_params_msg(t_fd *self, char **params)
{
  if (tablen(params) == 1)
    {
      if (params[0] && params[0][0] && params[0][0] != ':')
	return (err_serv("412 ", self->nick,
			 ":No text to send", " PRIVMSG\r\n"));
      else
	return (err_serv("411 ", self->nick,
			 ":No recipient given", " PRIVMSG\r\n"));
    }
  if (tablen(params) != 2)
    return (err_serv("461 ", self->nick, "PRIVMSG",
		     " :Not enough parameters\r\n"));
  return ("");
}

static char	*my_msg_loop(char **dest_list, t_fd *self, t_fd *fds, char *msg)
{
  int		i;
  t_fd		*ptr;
  char		*str;

  i = 0;
  while (dest_list[i])
    {
      ptr = fds;
      while (ptr && (!ptr->nick || strcmp(ptr->nick, dest_list[i])))
	ptr = ptr->next;
      if (!ptr)
	{
	  str = err_serv("401 ", self->nick, dest_list[i],
			   " :No such nick\r\n");
	  free_tab(dest_list);
	  free(msg);
	  return (str);
	}
      if (fputstr(ptr->fd, msg) == -1)
	return (NULL);
      ++i;
    }
  free(msg);
  free_tab(dest_list);
  return (strdup("\r\n"));
}

char		*my_msg(t_fd *fds, t_fd *self, char **params)
{
  char		**dest_list;
  char		*msg;

  msg = check_params_msg(self, params);
  if (msg[0])
    return (msg);
  if (!(msg = malloc(sizeof(*msg) *
		     (strlen(self->nick) + strlen(params[1]) + 5))))
    return (NULL);
  strcpy(msg, self->nick);
  strcat(msg, ": ");
  strcat(msg, params[1]);
  strcat(msg, "\r\n");
   if (params[0][0] == '#' || params[0][0] == '&')
    return (my_channel_msg(fds, self, params[0], msg));
  dest_list = dest_tab(params[0]);
  return (my_msg_loop(dest_list, self, fds, msg));
}
