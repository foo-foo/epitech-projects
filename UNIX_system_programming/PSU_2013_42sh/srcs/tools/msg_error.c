/*
** msg_error.c for libmy in /home/menich_a/rendu/CPE-2013-BSQ/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Dec  7 02:18:07 2013 menich_a
** Last update Sat May 31 14:00:25 2014 menich_a
*/

#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int	msg_error(char *msg)
{
  if (msg != NULL)
    write(2, msg, my_strlen(msg));
  return (-1);
}

char	*msg_error_ret(char *msg)
{
  msg_error(msg);
  return (NULL);
}

char	**msg_error_return(char *msg, char **to_return)
{
  msg_error(msg);
  return (to_return);
}

char	**my_warn_ret(char *msg)
{
  if (msg)
    warn("%s", msg);
  else
    warn("error:");
  return (NULL);
}

int	my_warn(char *msg, int errnum)
{
  if (errnum == -42 && msg)
    warn("%s", msg);
  if (msg)
    warn("%s %d", msg, errnum);
  else
    warn("%d", errnum);
  return (-1);
}
