/*
** errors.c for errors in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:22:13 2015 Anatole Menichetti
** Last update Fri Mar 27 12:54:10 2015 Anatole Menichetti
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../../includes/errors.h"
#include "../../includes/my.h"

int	my_perror(char *msg, int ret, int fd, int fd_client)
{
  if (fd_client)
    fputstr(fd_client, msg);
  perror(msg);
  if (fd)
    if (close(fd) == -1)
      perror(ESCLOSE);
  if (fd_client)
    if (close(fd_client) == -1)
      perror(ECCLOSE);
  return (ret);
}

void	*my_perror_gen(char *msg, void *ret, int fd, int fd_client)
{
  if (fd_client)
    fputstr(fd_client, msg);
  perror(msg);
  if (fd)
    if (close(fd) == -1)
      perror(ESCLOSE);
  if (fd_client)
    if (close(fd_client) == -1)
      perror(ECCLOSE);
  return (ret);
}

char	*alloc_err(int fd, int fd_client, FILE *fp, int action)
{
  fputstr(fd_client, ERALLOC);
  if (fp)
    {
      if (fclose(fp) == -1)
	return (my_perror_gen(ECCLOSE, NULL, fd, fd_client));
      fd_client = 0;
    }
  if (action)
    my_perror(ESCANDIR, 0, fd, fd_client);
  else
    my_perror(EALLOC, 0, fd, fd_client);
  return (NULL);
}

char	*my_rerror(char *msg, int fd, int fd_client, FILE *fp)
{
  char	*ret;

  if (!msg)
    return (NULL);
  ret = strdup(msg);
  if (!ret)
    return (alloc_err(fd, fd_client, fp, 0));
  return (ret);
}
