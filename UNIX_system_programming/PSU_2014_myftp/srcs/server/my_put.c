/*
** my_put.c for my_put in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Fri Mar 20 21:39:26 2015 Anatole Menichetti
** Last update Sun Mar 22 20:56:46 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

char		*process_transfert(int fds[2], FILE *fp, char **buff, size_t len)
{
  int		i;
  int		s;

  if ((s = atoi(*buff)) <= 0)
    return (NULL + 1);
  while ((i = getline(buff, &len, fp)) >= 0 && (s -= i) > 0)
    {
      if (fputstr(fds[0], "\n") == -1)
	return (my_perror_gen(EWRITE, NULL, 0, fds[0]));
      if (write(fds[1], *buff, i) == -1)
	return (my_rerror(ESTORAGE, -42, fds[0], fp));
    }
  if (i == -1)
    return (my_perror_gen(ERCV, NULL, 0, fds[0]));
  if (s == -1 && s++)
    (*buff)[--i] = '\0';
  if (s)
    return (my_rerror(EABORTED, -42, fds[0], fp));
  if (fputstr(fds[0], "\n") == -1)
    return (my_perror_gen(EWRITE, NULL, 0, fds[0]));
  if (write(fds[1], *buff, i) == -1)
    return (my_rerror(ESTORAGE, -42, fds[0], fp));
  return (NULL + 1);
}

char		*put_transfert(int fds[2], FILE *fp, char *buff, size_t len)
{
  char		*ret;

  ret = process_transfert(fds, fp, &buff, len);
  if (ret != NULL + 1)
    return (ret);
  if (close(fds[1]) == -1)
    return (my_rerror(EPTYPE, -42, fds[0], fp));
  free(buff);
  return (my_rerror(FSUCCESS, 0, fds[0], fp));
}

char		*my_put(int fd, FILE *fp, char *param, char **pwds)
{
  char		*buff;
  size_t	len;
  int		fds[2];
  int		i;

  buff = NULL;
  len = 0;
  i = 0;
  fds[0] = fd;
  (void)pwds;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  while (param[i] && param[i] != '\n' && param[i] != ' ' && param[i] != '\t')
    i += 1;
  if (param[i] != '\n')
    return (my_rerror(ESYNTAX, -42, fd, fp));
  param[i] = '\0';
  if ((fds[1] = open(param, O_WRONLY | O_CREAT, 0644)) == -1)
    return (my_rerror(ENOTTAKEN, -42, fd, fp));
  i = getline(&buff, &len, fp);
  if (i == -1)
    return (my_perror_gen(ERCV, NULL, 0, fd));
  return (put_transfert(fds, fp, buff, len));
}
