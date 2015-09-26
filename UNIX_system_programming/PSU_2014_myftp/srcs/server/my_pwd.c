/*
** my_pwd.c for my_pwd in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:38:29 2015 Anatole Menichetti
** Last update Fri Mar 27 12:50:17 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"

char	*my_pwd(int fd, FILE *fp, char *param, char **pwds)
{
  char	*ret;
  int	size;

  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  if (param[0] != '\n')
    return (my_rerror(ESYNTAX, 0, fd, fp));
  if (!pwds || !pwds[CURRENT] || !pwds[ROOT])
    return (my_rerror(ENOTTAKEN, 0, fd, fp));
  size = strlen(pwds[CURRENT]) - strlen(pwds[ROOT]);
  size += strlen(USER_DIRECTORY) + 16;
  ret = malloc(sizeof(*ret) * size);
  if (!ret)
    return (alloc_err(0, fd, fp, 0));
  strcpy(ret, "257 ");
  strcat(ret, pwds[CURRENT] + strlen(pwds[ROOT]) + strlen(USER_DIRECTORY));
  strcat(ret, " created.\r\n");
  return (ret);
}
