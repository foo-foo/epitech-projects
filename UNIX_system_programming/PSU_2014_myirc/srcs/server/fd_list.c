/*
** fd.c for myirc in /home/menich_a/rendu/PSU_2014_myirc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 18:16:31 2015 Anatole Menichetti
** Last update Sun Apr 12 11:09:29 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../includes/myirc.h"
#include "../../includes/server.h"

static char	*get_default_nick(t_fd *fds)
{
  t_fd		*ptr;
  char		*nick;
  char		unit;
  char		decade;

  decade = '/';
  if (!(nick = malloc(sizeof(*nick) * 9)))
    return (NULL);
  strcpy(nick, "Guest-");
  nick[8] = '\0';
  while (++decade <= '9')
    {
      unit = '/';
      nick[6] = decade;
      while (++unit <= '9')
	{
	  nick[7] = unit;
	  ptr = fds;
	  while (ptr && strcmp(ptr->nick, nick))
	    ptr = ptr->next;
	  if (!ptr)
	    return (nick);
	}
    }
  return (NULL);
}

static void	clean_fd(t_fd *target)
{
  free_tab(target->channels);
  target->channels = NULL;
  free(target->nick);
  target->nick = NULL;
  target->state = DOWN;
}

int		pop_fd(t_fd **fds, t_fd *target)
{
  int		fd;
  t_fd		*ptr;
  char		type;

  fd = target->fd;
  type = target->type;
  if (target == *fds)
    *fds = target->next;
  else
    {
      ptr = *fds;
      while (ptr->next && ptr->next != target)
        ptr = ptr->next;
      if (!ptr->next)
        return (EXIT_SUCCESS);
      ptr->next = ptr->next->next;
    }
  clean_fd(target);
  if (close(fd) == -1)
    return (msg_error(ECLOSE, 1));
  if (type == FD_CLIENT)
    printf("server: closing connection with client number %d.\n", fd);
  return (EXIT_SUCCESS);
}

int		push_fd(t_fd **fds, int fd, int type, handler_fptr handler)
{
  t_fd		*elem;
  t_fd		*ptr;

  if (!(elem = malloc(sizeof(*elem))))
    return (msg_error(EALLOC, 1));
  elem->fd = fd;
  elem->type = type;
  elem->state = ACTIVE;
  elem->handler_fptr = handler;
  if ((type == FD_CLIENT && !(elem->nick = get_default_nick(*fds))) ||
      (type == FD_SERVER && !(elem->nick = strdup("server"))))
    return (msg_error(EALLOC, 1));
  elem->channels = NULL;
  elem->next = NULL;
  if (!(*fds))
    {
      *fds = elem;
      return (EXIT_SUCCESS);
    }
  ptr = *fds;
  while (ptr->next)
    ptr = ptr->next;
  ptr->next = elem;
  return (EXIT_SUCCESS);
}
