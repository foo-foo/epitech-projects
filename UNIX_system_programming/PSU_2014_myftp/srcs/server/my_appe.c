/*
** my_put.c for my_put in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Fri Mar 20 21:39:26 2015 Anatole Menichetti
** Last update Sat Mar 28 14:12:20 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

char		*my_appe(int fd, FILE *fp, char *param, char **pwds)
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
  if ((fds[1] = open(param, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
    return (my_rerror(ENOTTAKEN, -42, fd, fp));
  i = getline(&buff, &len, fp);
  if (i == -1)
    return (my_perror_gen(ERCV, NULL, 0, fd));
  return (put_transfert(fds, fp, buff, len));
}
