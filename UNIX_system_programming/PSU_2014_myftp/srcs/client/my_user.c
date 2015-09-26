/*
** my_user.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar 22 21:03:40 2015 Anatole Menichetti
** Last update Sat Mar 28 18:28:24 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

int	my_user(int fd, FILE *fp, FILE *f_stdin, size_t len)
{
  char	*buff;
  int	s;

  buff = NULL;
  if ((s = getline(&buff, &len, fp)) < 0)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  putcolor(buff);
  if ((size_t)s > strlen(buff) && buff[0] != '3' && !my_free(buff))
    return (SUCCESS);
  putstr("Please enter your password:\n");
  if (getline(&buff, &len, f_stdin) < 0 || fputstr(fd, buff) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (getline(&buff, &len, fp) < 0)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (buff[strlen(buff) - 2] == '\r' &&
      putcolor(buff) && !my_free(buff))
    return (SUCCESS);
  putstr("Please confirm your password:\n");
  if (getline(&buff, &len, f_stdin) < 0 || fputstr(fd, buff) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (getline(&buff, &len, fp) < 0)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  putcolor(buff);
  free(buff);
  return (SUCCESS);
}
