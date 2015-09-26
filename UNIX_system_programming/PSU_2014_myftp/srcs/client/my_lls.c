/*
** my_ls.c for my_ls in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:34:16 2015 Anatole Menichetti
** Last update Thu Mar 26 15:23:39 2015 Anatole Menichetti
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
#include "../../includes/client.h"
#include "../../includes/my.h"

void		concat_file(char *f, char *b, char *n, int t)
{
  f[strlen(f) - 1] = '\0';
  strcat(f, "\t");
  strcat(f, b);
  strcat(f, "\t");
  if (t > 3)
    strcat(f, "\033[34m");
  strcat(f, n);
  if (t > 3)
    strcat(f, "\033[0m");
}

char		*long_listing(int fd, char *n, struct stat *stat)
{
  char		*f;
  char		*l;
  char		*b;
  char		*d;
  int		t;

  t = 3;
  if (lstat(n, stat) == -1)
    return (my_rerror(ENOTTAKEN, fd, 0));
  if (!(l = my_get_str(stat->st_nlink)) ||
      !(b = my_get_str(stat->st_size)))
    return (alloc_err(fd, 0, 0));
  d = ctime(&stat->st_mtime);
  if (stat->st_size == 4096)
    t += 12;
  f = malloc(sizeof(*f) * (strlen(l) + strlen(b) + strlen(d) + strlen(n) + t));
  if (!f)
    return (alloc_err(fd, 0, 0));
  strcpy(f, l);
  strcat(f, "\t");
  strcat(f, d);
  concat_file(f, b, n, t);
  free(l);
  free(b);
  return (f);
}

char		*append_one_file(int fd, char *ret, t_dir *file, int *s)
{
  char		*fstats;
  int		size;
  struct stat	stat;

  size = *s;
  if (!(fstats = long_listing(fd, file->d_name, &stat)) ||
      !strcmp(fstats, ENOTTAKEN))
    return (fstats);
  if (!(ret = realloc(ret, (strlen(fstats) + size + 2) * sizeof(*ret))))
    return (alloc_err(fd, 0, 0));
  ret[size] = '\0';
  strcat(ret, fstats);
  size = strlen(ret);
  ret[size++] = '\n';
  ret[size] = '\0';
  *s = size;
  free(fstats);
  free(file);
  return (ret);
}

char		*get_scan_path(t_dir ***files, int fd, char *param, int *n)
{
  int		i;
  char		*d;

  i = 0;
  while (param[0] == ' ' || param[0] == '\t')
    param += 1;
  while (param[i] && param[i] != '\n' && param[i] != ' ' &&
	 param[i] != '\t' && strncmp(param + i, "..", 2))
    i += 1;
  if (!strncmp(param + i, "..", 2))
    return (my_rerror(ENOTTAKEN, fd, 0));
  if (param[i] != '\n')
    return (my_rerror(ESYNTAX, fd, 0));
  param[i] = '\0';
  d = malloc(sizeof(*d) * (strlen(param) + 3));
  if (!d || (strcpy(d, "./") && strcat(d, param) && access(d, F_OK)))
    {
      if (!d || (!my_free(d) && !(d = strdup(ENOTTAKEN))))
	return (alloc_err(fd, 0, 1));
      return (d);
    }
  *n = scandir(d, files, NULL, alphasort);
  if (!my_free(d) && *n < 0)
    return (alloc_err(fd, 0, 1));
  return (param);
}

char		*my_lls(int fd, FILE *fp, char *param, char **pwds)
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
  size = strlen(FSTATOK);
  if (!ret)
    return (alloc_err(fd, fp, 0));
  while (n--)
    if (!(ret = append_one_file(fd, ret, files[n], &size)) ||
	!strcmp(ret, ENOTTAKEN))
      return (ret);
  free(files);
  if (!(ret = realloc(ret, (size + strlen(FSUCCESS) + 1) * sizeof(*ret))))
    return (alloc_err(fd, fp, 0));
  strcat(ret, FSUCCESS);
  return (ret);
}
