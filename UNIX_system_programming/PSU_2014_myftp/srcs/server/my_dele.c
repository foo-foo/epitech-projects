/*
** my_mkd.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 28 11:43:28 2015 Anatole Menichetti
** Last update Sat Mar 28 13:43:27 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include "../../includes/server.h"
#include "../../includes/errors.h"

char	*my_dele(int fd, FILE *fp, char *param, char **pwds)
{
  int	i;

  i = 0;
  (void)pwds;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  while (param[i] && param[i] != '\n' && param[i] != ' ' && param[i] != '\t')
    {
      if (strlen(param + i) >= 2 && !strncmp(param + i, "..", 2))
	return (my_rerror(ENOTTAKEN, 0, fd, fp));
      i += 1;
    }
  if (param[i] != '\n')
    return (my_rerror(ESYNTAX, 0, fd, fp));
  param[i] = '\0';
  if (remove(param) == -1)
    return (my_rerror(ENOTTAKEN, 0, fd, fp));
  return (my_rerror(CMDOK, 0, fd, fp));
}

char	*my_rmd(int fd, FILE *fp, char *param, char **pwds)
{
  int	i;

  i = 0;
  (void)pwds;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  while (param[i] && param[i] != '\n' && param[i] != ' ' && param[i] != '\t')
    {
      if (strlen(param + i) >= 2 && !strncmp(param + i, "..", 2))
	return (my_rerror(ENOTTAKEN, 0, fd, fp));
      i += 1;
    }
  if (param[i] != '\n')
    return (my_rerror(ESYNTAX, 0, fd, fp));
  param[i] = '\0';
  if (rmdir(param) == -1)
    return (my_rerror(ENOTTAKEN, 0, fd, fp));
  return (my_rerror(CMDOK, 0, fd, fp));
}
