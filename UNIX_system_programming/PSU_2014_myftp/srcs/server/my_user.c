/*
** my_user.c for my_user in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:47:27 2015 Anatole Menichetti
** Last update Sat Mar 28 18:40:00 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

char		*get_user_path(int fd, FILE *fp, char *param, char **pwds)
{
  int		size;
  char		*path;
  char		*usr;

  usr = get_conf(0, USER_DIRECTORY);
  size = strlen(pwds[ROOT]) + strlen(usr) + strlen(param) + 1;
  if (!(path = malloc(sizeof(*path) * (size + 1))))
    return (alloc_err(0, fd, fp, 0));
  strcpy(path, pwds[ROOT]);
  if (path[strlen(path) - 1] == '/' && usr[0] == '/')
    path[strlen(path) - 1] = '\0';
  strcat(path, usr);
  if (access(path, F_OK))
    if (mkdir(path, 0777) == -1)
      return (my_rerror(ENOTTAKEN, -42, fd, fp));
  strcat(path, "/");
  strcat(path, param);
  if (access(path, F_OK))
    if (mkdir(path, 0777) == -1)
      return (my_rerror(ENOTTAKEN, -42, fd, fp));
  return (path);
}

char		*get_user_name(int fd, FILE *fp, char *param)
{
  int		i;

  i = 0;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  if (!param[i] || param[i] == '\n')
    param = "Anonymous\n";
  while (param[i] && param[i] != '/' && param[i] != '.')
    i += 1;
  if (!param[i])
    while (--i >= 0 &&
	   (param[i] == '\n' || param[i] == ' ' || param[i] == '\t'));
  if (i < 0 || param[i] == '/' || param[i] == '.')
    return (my_rerror(EFNOTTAKEN, -42, fd, fp));
  param = strndup(param, i + 1);
  if (!param)
    return (alloc_err(0, fd, fp, 0));
  return (param);
}

char		*cd_user(int fd, FILE *fp, char *path, char **pwds)
{
  free(pwds[HOME]);
  if (!(pwds[HOME] = strdup(path)))
    return (alloc_err(0, fd, fp, 0));
  free(pwds[CURRENT]);
  if (!(pwds[CURRENT] = strdup(path)))
    return (alloc_err(0, fd, fp, 0));
  pwds[OLD] = my_free(pwds[OLD]);
  if (chdir(path) == -1)
    {
      free(path);
      return (my_rerror(ENOTTAKEN, -42, fd, fp));
    }
  free(path);
  return (my_rerror(LOGGEDIN, 0, fd, fp));
}

char		*my_user(int fd, FILE *fp, char *param, char **pwds)
{
  char		*path;
  static int	log = 0;

  if (!pwds || !pwds[ROOT])
    return (my_rerror(ENOTTAKEN, -42, fd, fp));
  if (!(param = get_user_name(fd, fp, param)) ||
      (strlen(param) >= 2 && param[strlen(param) - 2] == '\r'))
    return (param);
  if (!(path = get_user_path(fd, fp, param, pwds)) ||
      (strlen(path) >= 2 && path[strlen(path) - 2] == '\r'))
    return (path);
  if (!strcmp(param, "Anonymous") && !log++)
    free(param);
  else
    if (!(path = connect_user(fd, fp, path, param)) ||
	path[strlen(path) - 2] == '\r')
      return (path);
  return (cd_user(fd, fp, path, pwds));
}
