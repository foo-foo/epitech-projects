/*
** nickname.c for  in /home/auduri_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Wed Apr  8 10:37:11 2015 audurier julien
** Last update Thu Apr 16 12:11:27 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/server.h"

static int	check_nickname(char *str)
{
  int		i;

  i = 1;
  if (char_is_alpha(str[0]) != 0)
    return (-1);
  while (str && str[i])
    {
      if (char_is_spe(str[i]) == -1 && char_is_num(str[i]) == -1
	  && char_is_alpha(str[i]) == -1)
	return (-1);
      ++i;
    }
  if (i >= 9)
    return (-1);
  return (0);
}

static int	nick_is_taken(t_fd *client_list, char *name)
{
  t_fd		*tmp;

  tmp = client_list;
  while (tmp != NULL)
    {
      if (tmp->nick && strcmp(tmp->nick, name) == 0)
	return (-1);
      tmp = tmp->next;
    }
  return (0);
}

static char	*change_nickname(char *ret, t_fd *self, char *param)
{
  strcpy(ret, self->nick);
  strcat(ret, " changed his nickname to ");
  strcat(ret, param);
  strcat(ret, "\r\n");
  free(self->nick);
  if (!(self->nick = strdup(param)))
    return (NULL);
  return (ret);
}

char		*my_nickname(t_fd *client_list, t_fd *self, char **params)
{
  char		*ret;
  static char	check = 0;

  if (params[0] == NULL)
    return (err_serv("432", "", "", ":No nickname given\r\n"));
  if (check_nickname(params[0]) != 0)
    return (err_serv("432 ", self->nick, params[0], " :Erroneus nickname\r\n"));
  if (nick_is_taken(client_list, params[0]))
    return (err_serv("433 ", self->nick, params[0],
		     " :Nickname is already in use\r\n"));
  if ((ret = malloc(sizeof(char) * 45)) == NULL)
    return (NULL);
  if (check)
    return (change_nickname(ret, self, params[0]));
  check = 1;
  free(self->nick);
  strcpy(ret ,strdup("001 "));
  strcat(ret, strdup(params[0]));
  strcat(ret, " :Welcome to myIRC!\r\n");
  if (!(self->nick = strdup(params[0])))
    return (NULL);
  return (ret);
}
