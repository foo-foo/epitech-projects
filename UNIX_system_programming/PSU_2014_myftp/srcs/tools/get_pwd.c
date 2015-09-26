/*
** get_pwd.c for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 26 10:08:40 2015 Anatole Menichetti
** Last update Thu Mar 26 10:20:26 2015 Anatole Menichetti
*/

#include <string.h>
#include <stdlib.h>
#include "../../includes/myftp.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

void	free_pwds(char **pwds)
{
  free(pwds[HOME]);
  free(pwds[ROOT]);
  free(pwds[CURRENT]);
  free(pwds[OLD]);
  free(pwds);
}

char	*adjust_pwd(char *current, char *ex, char *name)
{
  char	*pwd;

  if (!(pwd = strdup(current)))
    return (NULL);
  if (strcmp(ex, name))
    {
      pwd = realloc(pwd, sizeof(*pwd) * (strlen(pwd) + strlen(ex) - 4));
      if (!pwd)
        return (NULL);
      strcat(pwd, "/");
      strncat(pwd, ex, strlen(ex) - (strlen(name) + 1));
    }
  return (pwd);
}

char	**get_pwd(char *ex, char *name)
{
  char	**pwds;
  char	*path;

  path = getenv("PWD");
  if (!path)
    {
      fputstr(2, ENOTFOUND);
      return (NULL);
    }
  if (ex[0] == '.')
    ex += 1;
  if (ex[0] == '/')
    ex += 1;
  if (!(pwds = malloc(sizeof(*pwds) * 4)) || !(pwds[CURRENT] = strdup(path)) ||
      !(pwds[ROOT] = adjust_pwd(path, ex, name)))
    {
      perror(EALLOC);
      return (NULL);
    }
  pwds[HOME] = NULL;
  pwds[OLD] = NULL;
  return (pwds);
}
