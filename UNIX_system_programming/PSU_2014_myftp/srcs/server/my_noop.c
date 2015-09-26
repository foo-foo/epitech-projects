/*
** my_mkd.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 28 11:43:28 2015 Anatole Menichetti
** Last update Sat Mar 28 12:09:57 2015 Anatole Menichetti
*/

#include "../../includes/server.h"
#include "../../includes/errors.h"

char	*my_noop(int fd, FILE *fp, char *param, char **pwds)
{
  (void)pwds;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  if (param[0] != '\n')
    return (my_rerror(ESYNTAX, 0, fd, fp));
  return (my_rerror(CMDOK, 0, fd, fp));
}
