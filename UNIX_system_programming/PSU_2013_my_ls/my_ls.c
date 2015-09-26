/*
** my_ls.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Dec  1 21:49:01 2013 menich_a
** Last update Sun Dec  1 22:34:28 2013 menich_a
*/

#include <dirent.h>
#include <stdlib.h>
#include "my_ls.h"

void		check_dir_functions(char *d, DIR *dir, int check)
{
  if (check == 0)
    {
      if (dir == NULL)
	{
	  my_printf("my_ls: cannot access %s: ", d);
	  perror("");
	  exit(-1);
	}
    }
  else
    {
      if (closedir(dir) == -1)
	{
	  my_printf("my_ls: cannot close %s: ", d);
	  perror("");
	  exit(-1);
	}
    }
}

int             my_ls(char *d, char *options)
{
  DIR           *dir;
  t_dirent      *file;
  t_list        *list;
  char          *tmp;

  list = NULL;
  dir = opendir(d);
  check_dir_functions(d, dir, 0);
  while (file = readdir(dir))
    {
      if (file->d_name[0] != '.')
        {
          if (find_in_tab(options, 'l') == 0 || find_in_tab(options, 'd') == 0)
            launch_options(file, options, &list, d);
          else
            my_put_in_list(&list, file->d_name, file->d_type, d);
        }
    }
  check_dir_functions(d, dir, 1);
  if (find_in_tab(options, 'l') == 0)
    clean_list_syntax(list);
  my_sort_list(list, options);
  my_show_long_list(list, options, d);
  return (0);
}
