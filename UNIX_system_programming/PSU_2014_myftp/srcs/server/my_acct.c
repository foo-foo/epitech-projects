/*
** my_mkd.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 28 11:43:28 2015 Anatole Menichetti
** Last update Sat Mar 28 16:33:02 2015 Anatole Menichetti
*/

#include <string.h>
#include <stdlib.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"

char	*my_acct(int fd, FILE *fp, char *param, char **pwds)
{
  int	i;
  char	*user_name;
  char	*ret;

  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  if (param[0] != '\n')
    return (my_rerror(ESYNTAX, 0, fd, fp));
  if (!pwds || !pwds[HOME])
    return (my_rerror(ENOTTAKEN, 0, fd, fp));
  i = strlen(pwds[HOME]) - 2;
  while (pwds[HOME][i] != '/')
    i -= 1;
  if (!(user_name = strdup(pwds[HOME] + i + 1)))
    return (alloc_err(0, fd, 0, 0));
  if (user_name[strlen(user_name) - 1] == '/')
    user_name[strlen(user_name) - 1] = '\0';
  if (!(ret = malloc(sizeof(*ret) * (strlen(user_name) + 16))))
    return (alloc_err(0, fd, 0, 0));
  strcpy(ret, "257 ");
  strcat(ret, user_name);
  strcat(ret, " created.\r\n");
  free(user_name);
  return (ret);
}
