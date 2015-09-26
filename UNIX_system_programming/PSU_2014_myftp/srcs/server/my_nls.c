/*
** my_ls.c for my_ls in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:34:16 2015 Anatole Menichetti
** Last update Sat Mar 28 17:42:23 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

char		*append_one_nfile(int fd, char *ret, t_dir *file, int *s)
{
  int		size;

  if (strcmp(file->d_name, PWD_CONTAINER + 1))
    {
      size = *s;
      if (!(ret = realloc(ret, (strlen(file->d_name) +
				size + 2) * sizeof(*ret))))
        return (alloc_err(0, fd, 0, 0));
      ret[size] = '\0';
      strcat(ret, file->d_name);
      size = strlen(ret);
      ret[size++] = '\n';
      ret[size] = '\0';
      *s = size;
    }
  else
    if (!ret)
      return (my_rerror("", 0, fd, 0));
  free(file);
  return (ret);
}

char		*my_nls(int fd, FILE *fp, char *param, char **pwds)
{
  t_dir		**files;
  char		*ret;
  int		size;
  int		n;

  (void)pwds;
  if (!(ret = get_scan_path(&files, fd, param, &n)) ||
      !strcmp(ret, ENOTTAKEN) || !strcmp(ret, ESYNTAX))
    return (ret);
  ret = strdup(FSTATOK);
  if (!ret)
    return (alloc_err(0, fd, fp, 0));
  size = strlen(FSTATOK) - 1;
  ret[size - 1] = '\n';
  ret[size] = '\0';
  while (n--)
    if (!(ret = append_one_nfile(fd, ret, files[n], &size)) ||
	!strcmp(ret, ENOTTAKEN))
      return (ret);
  free(files);
  if (!(ret = realloc(ret, (size + strlen(FSUCCESS) + 1) * sizeof(*ret))))
    return (alloc_err(0, fd, fp, 0));
  strcat(ret, FSUCCESS);
  return (ret);
}
