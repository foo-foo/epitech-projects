/*
** connect_user.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar 22 20:10:05 2015 Anatole Menichetti
** Last update Sat Mar 28 17:54:40 2015 Anatole Menichetti
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

char		*get_usr_password(int fd, char *pwd, char *usr_pwd)
{
  int		len;
  char		*tmp;

  len = 4;
  while (usr_pwd[len] == ' ' || usr_pwd[len] == '\t')
    len += 1;
  if (!(tmp = strdup(usr_pwd + len)))
    return (my_perror_gen(EALLOC, NULL, 0, fd));
  free(usr_pwd);
  usr_pwd = tmp;
  if (pwd && strcmp(pwd, usr_pwd))
    {
      free(usr_pwd);
      free(pwd);
      return (NULL + 1);
    }
  if (pwd)
    free(pwd);
  return (usr_pwd);
}

char		*ask_usr_pwd(int fd, FILE *fp, char *pwd, char *msg)
{
  char		*usr_pwd;
  size_t	len;

  len = 0;
  usr_pwd = NULL;
  if (pwd == NULL + 1)
    return (NULL + 1);
  if (fputstr(fd, msg) == -1 ||
      getline(&usr_pwd, &len, fp) < 0)
    return (my_perror_gen(EACCESS, NULL, 0, fd));
  if (strncmp(usr_pwd, "PASS", 4) || (usr_pwd[4] != ' ' && usr_pwd[4] != '\t'))
    {
      free(usr_pwd);
      free(pwd);
      return (NULL + 1);
    }
  return (get_usr_password(fd, pwd, usr_pwd));
}

char		*create_user_directory(int fd, FILE *fp, char *path)
{
  FILE		*f;
  char		*pwd;

  pwd = NULL;
  if (!(pwd = ask_usr_pwd(fd, fp, NULL, NEEDACCOUNT)) ||
      !(pwd = ask_usr_pwd(fd, fp, pwd, "Enter your password.\n")))
    return (my_free(path));
  if (pwd == NULL + 1)
    {
      free(path);
      return (my_rerror(EBADSEQ, 0, fd, fp));
    }
  if (!(f = fopen(path, "a")) && !my_free(pwd) && !my_free(path))
    return (my_rerror(ENOTTAKEN, 0, fd, fp));
  if (fprintf(f, "%s\n", pwd) < 0)
    return (my_rerror(ESTORAGE, 0, fd, fp));
  if (fclose(f) == -1 && !my_free(pwd) && !my_free(path))
    return (my_rerror(EPTYPE, 0, fd, fp));
  free(pwd);
  return (path);
}

char		*check_user_pwd(int fd, FILE *fp, char *path, char *usr_name)
{
  FILE		*f;
  size_t	len;
  char		*pwd;

  pwd = NULL;
  if (strcmp(usr_name, "Anonymous"))
    {
      if (!(f = fopen(path, "r")) || getline(&pwd, &len, f) < 0)
	{
	  if (!my_free(path) && f)
	    fclose(f);
	  return (my_rerror(ENOTTAKEN, 0, fd, fp));
	}
      if (fclose(f) == -1 && !my_free(path))
	return (my_rerror(ENOTTAKEN, 0, fd, fp));
    }
  if (!strcmp(usr_name, "Anonymous") && !(pwd = strdup("")))
    return (alloc_err(0, fd, fp, 0));
  if (!(pwd = ask_usr_pwd(fd, fp, pwd, NEEDPWD)))
    return (my_free(path));
  if (pwd == NULL + 1 && strcmp(usr_name, "Anonymous") && !my_free(path))
    return (my_rerror(EBADSEQ, 0, fd, fp));
  if (pwd != NULL + 1)
    free(pwd);
  return (path);
}

char		*connect_user(int fd, FILE *fp, char *path, char *param)
{
  char		*pwd_container;

  pwd_container = get_conf(0, PWD_CONTAINER);
  path = realloc(path, sizeof(*path) *
                 (strlen(path) + strlen(pwd_container) + 1));
  if (!path)
    {
      free(param);
      return (alloc_err(0, fd, fp, 0));
    }
  strcat(path, pwd_container);
  if (access(path, F_OK) && strcmp(param, "Anonymous"))
    path = create_user_directory(fd, fp, path);
  else
    path = check_user_pwd(fd, fp, path, param);
  free(param);
  if (path && path[strlen(path) - 2] != '\r')
    path[strlen(path) + 1 - strlen(pwd_container)] = '\0';
  return (path);
}
