/*
** my_get.c for myftp in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@epitech.net>
** 
** Started on  Fri Mar 20 22:13:32 2015 Anatole Menichetti
** Last update Fri Mar 27 17:47:51 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

char		*get_transfert(int fd, FILE *fp, FILE *f, struct stat stat)
{
  char		*buff;
  size_t	len;
  int		i;
  int		s;

  s = 0;
  len = 0;
  buff = NULL;
  if (getline(&buff, &len, fp) == -1)
    return (my_perror_gen(ERCV, NULL, 0, fd));
  if (fprintf(fp, "%lu\n", stat.st_size) == -1)
    return (my_perror_gen(EWRITE, NULL, 0, fd));
  if (getline(&buff, &len, fp) == -1)
    return (my_perror_gen(ERCV, NULL, 0, fd));
  if (stat.st_size > 0)
    while ((i = getline(&buff, &len, f)) >= 0 && (s += i))
      if (write(fd, buff, i) == -1 ||
	  (buff[i - 1] != '\n' && fputstr(fd, "\n") == -1) ||
	  getline(&buff, &len, fp) == -1)
	return (my_perror_gen(EWRITE, NULL, 0, fd));
  if ((i == -1 && s != stat.st_size) || fclose(f) == -1 || my_free(buff))
    return (my_rerror(EPTYPE, -42, fd, fp));
  return (my_rerror(FSUCCESS, -42, fd, fp));
}

int		get_eop(char *param)
{
  int		i;
  int		j;

  i = 0;
  while (param[i] != '\n' && param[i] != ' ' && param[i] != '\t')
    i += 1;
  j = i;
  while (param[j] == ' ' || param[j] == '\t')
    j += 1;
  if (param[j] != '\n')
    return (0);
  return (i);
}

char		*my_get(int fd, FILE *fp, char *param, char **pwds)
{
  FILE		*f;
  int		i;
  struct stat	stat;

  (void)pwds;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  i = get_eop(param);
  if (!i)
    return (my_rerror(ESYNTAX, -42, fd, fp));
  param[i] = '\0';
  if (access(param, F_OK) || lstat(param, &stat) == -1 ||
      stat.st_size == 4096 || !(f = fopen(param, "rb")))
    {
      if (!access(param, F_OK) && stat.st_size == 4096)
	return (my_rerror(EARGNOTIMP, -42, fd, fp));
      return (my_rerror(ENOTTAKEN, -42, fd, fp));
    }
  if (write(fd, FSTATOK, strlen(FSTATOK)) == -1)
    return (my_perror_gen(EWRITE, NULL, 0, fd));
  param[i] = '\n';
  param[i + 1] = '\0';
  if (fputstr(fd, param) == -1)
    return (my_perror_gen(EWRITE, NULL, 0, fd));
  return (get_transfert(fd, fp, f, stat));
}
