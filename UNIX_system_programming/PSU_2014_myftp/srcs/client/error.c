/*
** error.c for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 26 11:34:06 2015 Anatole Menichetti
** Last update Sat Mar 28 18:22:18 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include "../../includes/my.h"
#include "../../includes/myftp.h"
#include "../../includes/client.h"

int	my_perror(char *msg, int ret, int fd, int action)
{
  if (action == 0)
    {
      fputstr(2, msg);
      if (fd > 0)
        fputstr(fd, msg);
    }
  else
    perror(msg);
  if (ret == FAILURE || action)
    if (fd)
      if (close(fd) == -1)
        perror(ECLOSE);
  return (ret);
}

char	*alloc_err(int fd, FILE *fp, int action)
{
  fputstr(2, EALLOC);
  if (fp)
    {
      if (fclose(fp) == -1)
	fputstr(2, ECLOSE);
      else
	fd = 0;
    }
  if (action)
    my_perror(ESCANDIR, FAILURE, fd, 1);
  else
    my_perror(EALLOC, FAILURE, fd, 1);
  return (NULL);
}

char	*my_rerror(char *msg, int fd, FILE *fp)
{
  char	*ret;

  if (!msg)
    return (NULL);
  ret = strdup(msg);
  if (!ret)
    return (alloc_err(fd, fp, 0));
  return (ret);
}
