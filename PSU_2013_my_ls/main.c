/*
** main.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Nov 25 12:20:43 2013 menich_a
** Last update Sun Dec  1 22:37:03 2013 menich_a
*/

#include <dirent.h>
#include <stdlib.h>
#include "my_ls.h"

char		*create_options_tab(char *av, char *options, char *res, int j)
{
  int		cpt;
  static int	k;

  while (av[j] != '\0' && av[0] == '-')
    {
      cpt = 0;
      if (av[j] == '-')
	{
	  res[k] = '\0';
	  return (res);
	}
      while (av[j] != options[cpt] && options[cpt] != '\0')
	cpt = cpt + 1;
      if (options[cpt] == '\0')
	{
	  my_printf("my_ls: invalid option -- '%c'\n", av[j]);
	  exit(-1);
	}
      res[k] = options[cpt];
      k = k + 1;
      j = j + 1;
    }
  res[k] = '\0';
  return (res);
}

char		*find_options(char **av, char *options, int i, int j)
{
  int		k;
  char		*res;

  k = 0;
  res = malloc(sizeof(*res) * 4);
  while (av[i] != NULL)
    {
      res = create_options_tab(av[i], options, res, 1);
      i = i + 1;
    }
  return (res);
}

void		launch_ls(t_list *f_list, t_list *ptr, char *options, int cpt)
{
  while (cpt < my_list_size(f_list))
    {
      if (my_list_size(f_list) > 2 && find_in_tab(options, 'd') != 0)
	my_printf("%s:\n", ptr->name);
      {
	my_ls(ptr->name, options);
      }
      if (cpt + 1 < my_list_size(f_list) &&
	  (my_list_size(f_list) > 2 && find_in_tab(options, '1') == 0
	   && find_in_tab(options, 'd') != 0 || options[0] == '\0'))
	{
	  my_putstr("\n");
	}
      if (cpt + 1 == my_list_size(f_list) && find_in_tab(options, 'd') == 0 &&
	  find_in_tab(options, 'l') != 0)
	{
	  my_putstr("\n");
	}
      if (cpt + 1 != my_list_size(f_list) && find_in_tab(options, 'l') == 0 &&
	  find_in_tab(options, 'd') != 0 && find_in_tab(options, '1') != 0)
	my_putstr("\n");
      ptr = ptr->next;
      cpt = cpt + 1;
    }
}

int		main(int ac, char **av)
{
  char		*options;
  t_list	*f_list;
  t_list	*ptr;

  f_list = NULL;
  ptr = malloc(sizeof(*ptr));
  options = malloc(sizeof(*options) * 4);
  options = "ldr1";
  options = find_options(av, options, 0, 1);
  f_list = create_list(f_list, av, 0, 1);
  ptr = f_list;
  if (my_list_size(f_list) == 1)
    {
      my_ls(".", options);
      if (find_in_tab(options, 'd') == 0)
	my_putchar('\n');
    }
  else
    launch_ls(f_list, ptr, options, 1);
  //  free(options);
  return (0);
}
