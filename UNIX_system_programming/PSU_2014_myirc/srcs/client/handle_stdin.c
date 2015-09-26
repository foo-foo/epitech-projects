/*
** handle_stdin.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 13:07:39 2015 Anatole Menichetti
** Last update Sun Apr 12 12:42:23 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myirc.h"
#include "../../includes/client.h"

static char	*process_clear_buff(char *buff, int i)
{
  char		*tmp;

  if (buff[i] == '/')
    {
      if (!(tmp = strdup(buff + i + 1)))
	return (NULL);
      i = 0;
      while (tmp[i] >= 'a' && tmp[i] <= 'z')
	{
	  tmp[i] -= 32;
	  i += 1;
	}
      free(buff);
      return (tmp);
    }
  if (!(tmp = malloc(sizeof(*tmp) * (strlen(buff) + 10))))
    return (NULL);
  strncpy(tmp, buff, i);
  tmp[i] = '\0';
  strcat(tmp, "PRIVMSG ");
  strcat(tmp, buff + i);
  free(buff);
  return (tmp);
}

static char	*clear_buff(char *buff)
{
  int		i;

  i = 0;
  while (buff[i] == ' ' || buff[i] == '\t')
    i += 1;
  if (!(buff = clear_prefix(buff, i)))
    return (NULL);
  i = 0;
  while (buff[i] == ' ' || buff[i] == '\t')
    i += 1;
  if (!(buff = process_clear_buff(buff, i)))
    return (NULL);
  i = strlen(buff);
  if (!(buff = realloc(buff, sizeof(*buff) * (i + 2))))
    return (NULL);
  buff[i - 1] = '\r';
  buff[i] = '\n';
  buff[i + 1] = '\0';
  return (buff);
}

int		handle_stdin(int *fd, int *sel)
{
  char		buf[BUFF_SIZE];
  char		*buff;
  int		ret;

  *sel = 0;
  if ((ret = circular_read(0, buf)) < 0)
    return (-msg_error(EREAD, 1));
  if (!ret)
    strcpy(buf, "/QUIT\n");
  if (!strcmp(buf, "/quit\n"))
    ret = 0;
  if (!(buff = strdup(buf)))
    return (-msg_error(EALLOC, 1));
  if (!strncmp(buff, "/server", 7) &&
      (buff[7] == ' ' || buff[7] == '\t' || buff[7] == '\n'))
    return (process_server_cmd(buff, fd, ret));
  if (!(buff = clear_buff(buff)))
    return (-msg_error(EALLOC, 1));
  if (fputstr(*fd, buff) == -1)
    return (-msg_error(EWRITE, 1));
  free(buff);
  return (ret);
}
