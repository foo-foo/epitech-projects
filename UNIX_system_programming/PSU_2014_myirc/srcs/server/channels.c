/*
** my_list.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 13:19:43 2015 Anatole Menichetti
** Last update Sun Apr 12 12:26:30 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/myirc.h"
#include "../../includes/server.h"

static int	channel_is_valid(char *channel, char *channels, char *to_match)
{
  int		i;
  int		j;

  i = 0;
  if (to_match)
    {
      while (channel[i] && strncmp(channel + i, to_match, strlen(to_match)))
	i += 1;
      if (!channel[i])
	return (0);
      i = 0;
    }
  if (!channels)
    return (1);
  while (channels[i])
    {
      j = i;
      while (channels[i] != '\n')
	i += 1;
      if (i - j > (int)strlen(channel) &&
	  !strncmp(channel, channels + i - strlen(channel) - 1, strlen(channel)))
	return (0);
      i += 1;
    }
  return (1);
}

static char	*get_one_channel(t_fd *ptr, t_fd *self, char *channels, char *param)
{
  int		i;

  i = 0;
  while (ptr->channels && ptr->channels[i])
    {
      if (channel_is_valid(ptr->channels[i], channels, param))
	{
	  if (!(channels = realloc(channels, sizeof(char) *
				   (strlen(channels) + strlen(self->nick)
				    + strlen(ptr->channels[i]) + 8))))
	    return (NULL);
	  sprintf(channels + strlen(channels), "322 %s %s\r\n",
		  self->nick, ptr->channels[i]);
	}
      i += 1;
    }
  return (channels);
}

char		*my_list(t_fd *fds, t_fd *self, char **params)
{
  char		*channels;
  t_fd		*ptr;

  if (!self || tablen(params) > 1)
    return (err_serv("461 ", self->nick, "LIST",
		     " :Not enough parameters\r\n"));
  ptr = fds;
  if (!(channels = malloc(sizeof(char) * (strlen(self->nick) + 15))))
    return (NULL);
  sprintf(channels, "321 %s Channel\r\n", self->nick);
  while (ptr)
    {
      if (!(channels = get_one_channel(ptr, self, channels, params[0])))
	return (NULL);
      ptr = ptr->next;
    }
  if (!(channels = realloc(channels, sizeof(char)
			   * (strlen(channels) + strlen(self->nick) + 21))))
    return (NULL);
  sprintf(channels + strlen(channels), "323 %s :End of LIST\r\n", self->nick);
  return (channels);
}

char		*my_join(t_fd *fds, t_fd *self, char **params)
{
  int		i;

  (void)fds;
  if (tablen(params) != 1)
    return (err_serv("461 ", self->nick, "JOIN",
		     " :Not enough parameters\r\n"));
  if (check_channel_name(params[0]) == -1)
    return (err_serv("403 ", self->nick, params[0], " :No such channel\r\n"));
  i = 0;
  if (self->channels)
    while (self->channels[i] && strcmp(self->channels[i], params[0]))
      i += 1;
  if (self->channels && self->channels[i])
    return (strdup("\r\n"));
  if (!(self->channels = realloc(self->channels,
				 sizeof(*self->channels) * (i + 2))) ||
      !(self->channels[i] = strdup(params[0])))
    return (NULL);
  self->channels[i + 1] = NULL;
  return (strdup("\r\n"));
}

char		*my_part(t_fd *fds, t_fd *self, char **params)
{
  int		i;
  char		*tmp;

  (void)fds;
  if (tablen(params) != 1)
    return (err_serv("461 ", self->nick, "PART",
		     " :Not enough parameters\r\n"));
  i = 0;
  if (self->channels)
    while (self->channels[i] && strcmp(self->channels[i], params[0]))
      i += 1;
  if (!self->channels || !self->channels[i])
    return (err_serv("442 ", self->nick, params[0],
		     " :You're not on that channel\r\n"));
  tmp = self->channels[i];
  while (self->channels[i])
    {
      self->channels[i] = self->channels[i + 1];
      i += 1;
    }
  free(tmp);
  if (!(self->channels = realloc(self->channels, sizeof(*self->channels) * i)))
    return (NULL);
  return (strdup("\r\n"));
}
