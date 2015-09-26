/*
** my_get.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar 22 20:59:47 2015 Anatole Menichetti
** Last update Sat Mar 28 18:23:39 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

int	init_get(int fd, FILE *fp, size_t *len, char **buff)
{
  int	s;
  int	f;

  if (rfputstr(fd, *buff) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  *buff = my_free(*buff);
  if ((s = getline(buff, len, fp)) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  putcolor(*buff);
  if ((size_t)s > strlen(*buff) && (*buff)[0] != '1')
    return (SUCCESS);
  if ((s = getline(buff, len, fp)) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (fputstr(fd, "\n") == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  (*buff)[s - 1] = '\0';
  if ((f = open(*buff, O_WRONLY | O_CREAT, 0644)) == -1)
    return (my_perror(ENOTTAKEN, SUCCESS, fd, 0));
  if ((s = getline(buff, len, fp)) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (fputstr(fd, "\n") == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  return (-f);
}

int	complete_get(int fds[2], char **buff, int s)
{
  if (write(fds[1], buff, s) == -1)
    return (my_perror(ESTORAGE, SUCCESS, fds[0], 0));
  if (fputstr(fds[0], "\n") == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fds[0], 0));
  return (-1);
}

int	process_get(FILE *fp, int fds[2], char **buff, size_t *len)
{
  int	s;
  int	ret;
  int	bytes;

  ret = 0;
  bytes = atoi(*buff);
  while ((s = getline(buff, len, fp)) >= 0 && (ret += s) < bytes)
    {
      disp_percentage(100 * ret / bytes);
      if (write(fds[1], buff, s) == -1)
	return (my_perror(ESTORAGE, SUCCESS, fds[0], 0));
      if (fputstr(fds[0], "\n") == -1)
	return (my_perror(EUNAVAILABLE, FAILURE, fds[0], 0));
    }
  if (s == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fds[0], 0));
  putstr("\r100%\n");
  if (ret == bytes + 1)
    {
      ret -= 1;
      (*buff)[--s] = '\0';
    }
  if (ret != bytes)
    return (my_perror(EABORTED, SUCCESS, fds[0], 0));
  return (complete_get(fds, buff, s));
}

int	my_get(int fd, FILE *fp, char *buff, size_t len)
{
  int	fds[2];
  int	s;

  fds[0] = fd;
  if ((fds[1] = init_get(fd, fp, &len, &buff)) >= 0)
    return (fds[1]);
  fds[1] = -fds[1];
  putstr("0%");
  if (atoi(buff) > 0)
    {
      s = process_get(fp, fds, &buff, &len);
      if (s >= 0)
	return (s);
    }
  else
    putstr("\r100%\n");
  if (close(fds[1]) == -1)
    return (my_perror(EPTYPE, FAILURE, fd, 0));
  buff = my_free(buff);
  if ((s = getline(&buff, &len, fp)) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  putcolor(buff);
  free(buff);
  return (SUCCESS);
}
