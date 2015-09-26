/*
** my_put.c for my_put in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Fri Mar 20 21:39:26 2015 Anatole Menichetti
** Last update Sat Mar 28 17:48:03 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

void		nconcat(char *name, char *tmp, int i, char c)
{
  int		del;

  strncpy(name, tmp, i);
  name[i] = '\0';
  strcat(name, " (");
  del = strlen(name);
  name[del] = c;
  name[del + 1] = '\0';
  strcat(name, ")");
  strcat(name, tmp + i);
}

char		*get_unique_name(char *name, int fd)
{
  char		*tmp;
  int		i;
  char		c;

  c = '1';
  i = strlen(name) - 1;
  while (i > 0 && name[i] != '.')
    i -= 1;
  if (!i)
    i = strlen(name);
  tmp = name;
  while (!access(name, F_OK) && c <= '9')
    {
      if (strcmp(name, tmp))
	free(name);
      if (!(name = malloc(sizeof(*name) * (strlen(tmp) + 5))))
	return (alloc_err(0, fd, 0, 0));
      nconcat(name, tmp, i, c++);
    }
  return (name);
}

char		*my_stou(int fd, FILE *fp, char *param, char **pwds)
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
  param = get_unique_name(param, fd);
  if ((fds[1] = open(param, O_WRONLY | O_CREAT, 0644)) == -1)
    return (my_rerror(ENOTTAKEN, -42, fd, fp));
  i = getline(&buff, &len, fp);
  if (i == -1)
    return (my_perror_gen(ERCV, NULL, 0, fd));
  return (put_transfert(fds, fp, buff, len));
}
