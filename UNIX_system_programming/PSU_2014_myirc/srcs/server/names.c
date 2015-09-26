/*
** user.c for  in /home/auduri_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Wed Apr  8 14:30:18 2015 audurier julien
** Last update Sat Apr 11 16:25:09 2015 audurier julien
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../includes/myirc.h"
#include "../../includes/server.h"

static char	*get_user_name(t_fd *ptr, t_fd *self, char *ret, char *param)
{
  int		i;
  char		*tmp;

  i = 0;
  if (ptr->channels && param)
    while (ptr->channels[i] && strcmp(param, ptr->channels[i]))
      i += 1;
  if (ptr->type != FD_SERVER &&
      ((ptr->channels && ptr->channels[i]) ||
       ((!ptr->channels || !ptr->channels[i]) && !param)))
    {
      tmp = "none";
      if (ptr->channels && ptr->channels[i])
	tmp = ptr->channels[i];
      if ((ret = realloc(ret, sizeof(*ret) *
			 (strlen(ret) + strlen(tmp) + strlen(self->nick)
			  + strlen(ptr->nick) + 13))) == NULL)
	return (NULL);
      sprintf(ret + strlen(ret), "353 %s = %s :@%s\r\n",
	      self->nick, tmp, ptr->nick);
    }
  return (ret);
}

char		*my_names(t_fd *fds, t_fd *self, char **params)
{
  t_fd		*ptr;
  char		*ret;
  char		*tmp;

  ptr = fds;
  if (!(ret = malloc(sizeof(*ret) * 1)))
    return (NULL);
  ret[0] = '\0';
  while (ptr != NULL)
    {
      if (!(ret = get_user_name(ptr, self, ret, params[0])))
	return (NULL);
      ptr = ptr->next;
    }
  tmp = "none";
  if (params[0])
    tmp = params[0];
  if ((ret = realloc(ret, sizeof(*ret) *
		     (strlen(ret) + strlen(tmp) + strlen(self->nick) + 27))) == NULL)
    return (NULL);
  sprintf(ret + strlen(ret), "366 %s %s :End of NAMES list\r\n",
	  self->nick, tmp);
  return (ret);
}
