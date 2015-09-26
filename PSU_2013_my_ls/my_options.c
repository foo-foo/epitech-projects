/*
** my_ls_options.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Nov 26 19:20:26 2013 menich_a
** Last update Sun Dec  1 22:36:28 2013 menich_a
*/

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "my_ls.h"

void            launch_options(t_dirent *file, char *options, t_list **list, char *dir)
{
  int           i;
  char          *name;
  static char   *check;

  name = file->d_name;
  i = 0;
  if (find_in_tab(options, 'd') == 0)
    name = dir;
  if (find_in_tab(options, 'l') == 0)
    {
      if (find_in_tab(options, 'd') == 0 &&
	  (check == NULL || my_strcmp(dir, check) != 0))
	{
	  check = my_strdup(dir);
	  long_listing_option(name, list, 4, "");
	}
      else if (find_in_tab(options, 'd') != 0)
	long_listing_option(name, list, file->d_type, dir);
    }
  if (find_in_tab(options, 'd') == 0  && find_in_tab(options, 'l') != 0)
    if (check == NULL || my_strcmp(dir, check) != 0)
      {
        check = my_strdup(dir);
        my_put_in_list(list, name, 4, dir);
      }
}

void		put_rights_in_list(t_stat *stat, t_list *file)
{
  file->rights = malloc(sizeof(char) * 11);
  if (file->rights == NULL)
    exit(-1);
  (stat->st_mode & S_IFDIR) != 0 ?
    (file->rights[0] = 'd') : (file->rights[0] = '-');
  (stat->st_mode & S_IRUSR) != 0 ?
    (file->rights[1] = 'r') : (file->rights[1] = '-');
  (stat->st_mode & S_IWUSR) != 0 ?
    (file->rights[2] = 'w') : (file->rights[2] = '-');
  (stat->st_mode & S_IXUSR) != 0 ?
    (file->rights[3] = 'x') : (file->rights[3] = '-');
  (stat->st_mode & S_IRGRP) != 0 ?
    (file->rights[4] = 'r') : (file->rights[4] = '-');
  (stat->st_mode & S_IWGRP) != 0 ?
    (file->rights[5] = 'w') : (file->rights[5] = '-');
  (stat->st_mode & S_IXGRP) != 0 ?
    (file->rights[6] = 'x') : (file->rights[6] = '-');
  (stat->st_mode & S_IROTH) != 0 ?
    (file->rights[7] = 'r') : (file->rights[7] = '-');
  (stat->st_mode & S_IWOTH) != 0 ?
    (file->rights[8] = 'w') : (file->rights[8] = '-');
  (stat->st_mode & S_IXOTH) != 0 ?
    (file->rights[9] = 'x') : (file->rights[9] = '-');
  file->rights[10] = '\0';
}

void		put_inf_in_list(char *name, char *old_name, t_list **list, int type)
{
  t_stat	*stat;
  t_list	*file;
  t_passwd	*pwd;
  t_grp		*grp;

  file = *list;
  file = malloc(sizeof(*file));
  stat = malloc(sizeof(*stat));
  if (file == NULL || stat == NULL)
    exit(-1);
  lstat(name, stat);
  pwd = getpwuid(stat->st_uid);
  grp = getgrgid(stat->st_gid);
  put_rights_in_list(stat, file);
  file->blocks = stat->st_blocks;
  file->date = my_strdup(ctime(&stat->st_mtime));
  file->size = my_strdup(my_get_str(stat->st_size));
  file->grp = my_strdup(grp->gr_name);
  file->usr = my_strdup(pwd->pw_name);
  file->link = my_strdup(my_get_str(stat->st_nlink));
  file->name = my_strdup(old_name);
  file->way = my_strdup(name);
  file->type = type;
  file->next = *list;
  *list = file;
}

void		long_listing_option(char *old_name, t_list **list, int type, char *dir)
{
  char		*name;
  t_list	*file;

  name = malloc(sizeof(*name) * (my_strlen(old_name) + my_strlen(dir)));
  if (name == NULL)
    {
      exit(-1);
    }
  if (my_strcmp(dir, ".") == 0)
    {
      name = my_strdup(old_name);
    }
  else
    {
      name = my_strdup(dir);
      if (name[my_strlen(name) - 1] != '/' && my_strlen(name) > 0)
	name[my_strlen(name)] = '/';
      my_strcat(name, old_name);
      name[my_strlen(name)] = '\0';
    }
  put_inf_in_list(name, old_name, list, type);
}
