/*
** my_cd.c for my_cd in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:44:48 2015 Anatole Menichetti
** Last update Sat Mar 28 18:26:03 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"

char	*get_path(int fd, FILE *fp, char *param)
{
  int	i;

  i = 0;
  while (param[i] == ' ' || param[i] == '\t')
    param += 1;
  while (param[i] && param[i] != '\n' &&
	 param[i] != ' ' && param[i] != '\t')
    i += 1;
  if (param[i] != '\n' || !i || param[i - 1] == ' ' || param[i - 1] == '\t')
    return (my_rerror(ESYNTAX, fd, fp));
  param[i] = '\0';
  return (param);
}

char	*clear_path(int fd, FILE *fp, char *param, char **pwds)
{
  int	i;
  char	*d;

  if (!(d = strdup(pwds[CURRENT])))
    return (alloc_err(fd, fp, 0));
  while (!strncmp(param, "..", 2))
    {
      i = strlen(d) - 2;
      while (i >= 0 && d[i] != '/')
	i -= 1;
      d[i] = '\0';
      param += 2;
      if (param[0] == '/' && !strncmp(param + 1, "..", 2))
	param += 1;
    }
  if (!strcmp(d + strlen(d) - 9, "Anonymous"))
    strcat(d, "/");
  if (param[0] == '/' && param[1] && param[1] != '\n' &&
      param[1] != ' ' && param[1] != '\t')
    {
      if (!(d = realloc(d, (strlen(d) + strlen(param) + 1))))
	return (alloc_err(fd, fp, 0));
      strcat(d, param);
    }
  return (d);
}

char	*process_cd(int fd, FILE *fp, char *d, char **pwds)
{
  char	*ret;

  if (chdir(d) == -1)
    {
      ret = strdup(ENOTTAKEN);
      free(d);
      if (!ret)
        return (alloc_err(fd, fp, 0));
      return (ret);
    }
  free(pwds[OLD]);
  pwds[OLD] = pwds[CURRENT];
  pwds[CURRENT] = d;
  if (!(ret = strdup(CMDOK)))
    return (alloc_err(fd, fp, 0));
  return (ret);
}

char	*cd_init(int fd, FILE *fp, char *param, char **pwds)
{
  char	*ret;

  if (!pwds || !strcmp(param, "-"))
    {
      if (!pwds || !pwds[OLD])
	return (my_rerror(EBADSEQ, fd, fp));
      ret = pwds[OLD];
      pwds[OLD] = NULL;
      return (ret);
    }
  if (!strncmp(param, "..", 2))
    return (clear_path(fd, fp, param, pwds));
  ret = strdup(param);
  if (!ret)
    return (alloc_err(fd, fp, 0));
  return (ret);
}

char	*my_lcd(int fd, FILE *fp, char *param, char **pwds)
{
  char	*d;

  if (!(param = get_path(fd, fp, param)) ||
      !strcmp(param, ESYNTAX) || !strcmp(param, ENOTTAKEN))
    return (param);
  d = cd_init(fd, fp, param, pwds);
  if (!d || !strcmp(d, EBADSEQ))
    return (d);
  if (d[0] != '/')
    {
      param = d;
      d = malloc(sizeof(*d) * (strlen(param) + strlen(pwds[CURRENT]) + 2));
      if (!d)
        return (alloc_err(fd, fp, 0));
      strcpy(d, pwds[CURRENT]);
      if (strcmp(d + strlen(d) - 10, "Anonymous/"))
	strcat(d, "/");
      strcat(d, param);
      free(param);
    }
  return (process_cd(fd, fp, d, pwds));
}
