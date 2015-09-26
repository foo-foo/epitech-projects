/*
** my_put.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar 22 21:00:45 2015 Anatole Menichetti
** Last update Sat Mar 28 18:27:34 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

int		process_put(int fd, FILE *fp, FILE *f, struct stat stat)
{
  char		*buff;
  size_t	len;
  int		s;
  int		i;

  s = 0;
  len = 0;
  buff = 0;
  while ((i = getline(&buff, &len, f)) >= 0)
    {
      s += i;
      disp_percentage(100 * s / stat.st_size);
      if (write(fd, buff, i) == -1)
        return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
      if (buff[i - 1] != '\n')
        if (fputstr(fd, "\n") == -1)
          return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
      if ((i = getline(&buff, &len, fp)) == -1)
        return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
      if (i >= 2 && buff[i - 2] == '\r' &&
	  putstr(remove_ret(buff)) && !my_free(buff))
	return (SUCCESS);
    }
  my_free(buff);
  return (-1);
}

int		complete_put(int fd, FILE *fp, FILE *f, struct stat stat)
{
  int		i;
  size_t	len;
  char		*buff;

  len = 0;
  buff = my_get_str(stat.st_size);
  if (fputstr(fd, buff) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (fputstr(fd, "\n") == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  buff = my_free(buff);
  putstr("0%");
  i = process_put(fd, fp, f, stat);
  putstr("\r100%%\n");
  if (i >= 0)
    return (i);
  if (fclose(f) == -1)
    return (my_perror(EPTYPE, SUCCESS, fd, 0));
  while ((i = getline(&buff, &len, fp)) >= 0 && buff[i - 2] != '\r')
    putstr(buff);
  if (i == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  putcolor(buff);
  my_free(buff);
  return (SUCCESS);
}

int		init_put(int fd, FILE *fp, char **buf, char **tmp)
{
  int		i;
  size_t	len;
  char		*buff;

  i = 0;
  len = 0;
  if (!((*tmp) = strdup(*buf)))
    return (my_perror(EALLOC, FAILURE, fd, 0));
  buff = (*buf) + 4;
  while (buff[0] == ' ' || buff[0] == '\t')
    buff += 1;
  while (buff[i] && buff[i] != '\n' && buff[i] != ' ' && buff[i] != '\t')
    i += 1;
  if (buff[i] != '\n')
    {
      *tmp = my_free(*tmp);
      fputstr(fd, "\n");
      if (getline(tmp, &len, fp) == -1)
        return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
      free(*tmp);
      return (my_perror(ESYNTAX, SUCCESS, 0, 0));
    }
  buff[i] = '\0';
  (*buf) = buff;
  return (-1);
}

int		my_put(int fd, FILE *fp, char *buff, size_t len)
{
  struct stat	stat;
  FILE		*f;
  char		*tmp;
  char		*cpy;
  int		ret;

  cpy = buff;
  if ((ret = init_put(fd, fp, &buff, &tmp)) >= 0)
    return (ret);
  if (access(buff, F_OK) || lstat(buff, &stat) == -1 ||
      stat.st_size == 4096 || !(f = fopen(buff, "r")))
    {
      tmp = my_free(tmp);
      if (fputstr(fd, "\n") == -1 || getline(&tmp, &len, fp) == -1)
        return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
      free(tmp);
      if (stat.st_size == 4096)
        return (my_perror(EARGNOTIMP, SUCCESS, 0, 0));
      return (my_perror(ENOTTAKEN, SUCCESS, 0, 0));
    }
  free(cpy);
  putstr(FSTATOK);
  if (rfputstr(fd, tmp) == -1 || (tmp = my_free(tmp)))
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  return (complete_put(fd, fp, f, stat));
}
