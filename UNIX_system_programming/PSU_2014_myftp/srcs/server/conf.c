/*
** conf.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar 22 17:00:28 2015 Anatole Menichetti
** Last update Sat Mar 28 17:08:14 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../includes/server.h"
#include "../../includes/my.h"

char		*get_one_conf(char *conf, char *p, char *var)
{
  int		i;
  int		j;

  i = 0;
  if (conf)
    return (conf);
  while (p[i] == ' ' || p[i] == '\t')
    i += 1;
  if (strlen(p + i) > strlen(var) && !strncmp(p + i, var, strlen(var)))
    {
      j = i + strlen(var) - 1;
      if (p[j + 1] == '\n' || p[j + 1] == ' ' || p[j + 1] == '\t')
	return (NULL);
      p[j] = '/';
      while (p[++j] && p[j] != '\n')
	if ((p[j] < 45 || p[j] == '/' ||
	     (p[j] == '.' && p[j + 1] == '.')) && p[j] != ' ')
	  return (NULL);
      return (strndup(p + i + strlen(var) - 1, strlen(p) - (i + strlen(var))));
    }
  return (NULL);
}

char		*process_conf(char *path, char **pass, char **user)
{
  size_t	len;
  FILE		*fp;

  if (!access(path, F_OK) && (fp = fopen(path, "r")))
    {
      path = my_free(path);
      len = 0;
      while (getline(&path, &len, fp) >= 0)
	{
	  *pass = get_one_conf(*pass, path, "PWD_CONTAINER=");
	  *user = get_one_conf(*user, path, "USER_DIRECTORY=");
	}
      if (fclose(fp) == -1)
	return (NULL);
    }
  else
    free(path);
  if ((!(*pass) && !((*pass) = strdup(PWD_CONTAINER))) ||
      (!(*user) && !((*user) = strdup(USER_DIRECTORY))))
      return (NULL);
  return (path);
}

char		*get_conf(char *pwd, char *conf)
{
  static char	*pass = NULL;
  static char	*user = NULL;
  char		*path;

  if (conf && !strcmp(conf, PWD_CONTAINER))
    return (pass);
  if (conf && !strcmp(conf, USER_DIRECTORY))
    return (user);
  path = malloc(sizeof(*path) * (strlen(pwd) + 7));
  if (!path)
    return (NULL);
  strcpy(path, pwd);
  strcat(path, "/.conf");
  return (process_conf(path, &pass, &user));
}
