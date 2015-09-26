/*
** my_pwd.c for my_pwd in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:38:29 2015 Anatole Menichetti
** Last update Sat Mar 28 18:26:26 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"

char	*my_lpwd(int fd, FILE *fp, char *param, char **pwds)
{
  char	*ret;
  int	size;

  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  if (param[0] != '\n')
    return (my_rerror(ESYNTAX, fd, fp));
  if (!pwds || !pwds[CURRENT] || !pwds[ROOT])
    return (my_rerror(ENOTTAKEN, fd, fp));
  size = strlen(pwds[CURRENT]) + 26;
  ret = malloc(sizeof(*ret) * size);
  if (!ret)
    return (alloc_err(fd, fp, 0));
  strcpy(ret, "\033[36m257 ");
  strcat(ret, pwds[CURRENT]);
  strcat(ret, " created.\033[0m\n\a");
  return (ret);
}
