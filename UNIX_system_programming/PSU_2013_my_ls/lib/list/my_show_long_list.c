/*
** my_show_list.c for j_12 in /home/menich_a/rendu/Piscine-C-Jour_12/ex_03
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Oct 23 07:35:38 2013 menich_a
** Last update Sun Dec  1 22:50:21 2013 menich_a
*/

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "my_ls.h"

int	display_colors_l(t_list *ptr)
{
  if (ptr->type == 4)
    my_printf(" \033[1;34m%s\033[0;m\n", ptr->name);
  else if (ptr->name[my_strlen(ptr->name) - 1] == 'm' &&
	     ptr->name[my_strlen(ptr->name) - 2] == 'p' &&
	   ptr->name[my_strlen(ptr->name) - 3] == 'x' &&
	     ptr->name[my_strlen(ptr->name) - 4] == '.')
    my_printf(" \033[1;35m%s\033[0;m\n", ptr->name);
  else if (ptr->name[my_strlen(ptr->name) - 1] == 'h' &&
	     ptr->name[my_strlen(ptr->name) - 2] == 's' &&
	     ptr->name[my_strlen(ptr->name) - 3] == '.')
    my_printf(" \033[0;32m%s\033[0;m\n", ptr->name);
  else if (ptr->name[my_strlen(ptr->name) - 1] == 'z' &&
	     ptr->name[my_strlen(ptr->name) - 2] == 'g' &&
	     ptr->name[my_strlen(ptr->name) - 3] == '.')
    my_printf(" \033[0;31m%s\033[0;m\n", ptr->name);
  else
    my_printf(" %s\n", ptr->name);
  return (0);
}

int	display_colors(t_list *ptr, char *end, int check_option)
{
  if (check_option == 1)
    return (display_colors_l(ptr));
  else
    {
      if (ptr->type == 4)
	my_printf("\033[1;34m%s\033[0;m%s", ptr->name, end);
      else if (ptr->name[my_strlen(ptr->name) - 1] == 'm' &&
		 ptr->name[my_strlen(ptr->name) - 2] == 'p' &&
	       ptr->name[my_strlen(ptr->name) - 3] == 'x' &&
		 ptr->name[my_strlen(ptr->name) - 4] == '.')
	my_printf("\033[1;35m%s\033[0;m%s", ptr->name, end);
      else if (ptr->name[my_strlen(ptr->name) - 1] == 'h' &&
		 ptr->name[my_strlen(ptr->name) - 2] == 's' &&
		 ptr->name[my_strlen(ptr->name) - 3] == '.')
	my_printf("\033[0;32m%s\033[0;m%s", ptr->name, end);
      else if (ptr->name[my_strlen(ptr->name) - 1] == 'z' &&
		 ptr->name[my_strlen(ptr->name) - 2] == 'g' &&
		 ptr->name[my_strlen(ptr->name) - 3] == '.')
	my_printf("\033[0;31m%s\033[0;m%s", ptr->name, end);
      else
	my_printf("%s%s", ptr->name, end);
    }
  return (0);
}

void		launch_display(t_list *ptr, char *options)
{
  while (ptr != NULL)
    {
      if (find_in_tab(options, 'l') == 0)
	{
	    my_printf("%s ", ptr->rights);
	    my_printf("%s ", ptr->link);
	    my_printf("%s ", ptr->usr);
	    my_printf("%s ", ptr->grp);
	    my_printf("%s ", ptr->size);
	    write(1, ptr->date + 4, 12);
	    display_colors(ptr, "42", 1);
	}
      else if (find_in_tab(options, 'l') != 0 &&
	       (ptr->next != NULL || find_in_tab(options, 'd') == 0) &&
		 options[0] != '1')
	display_colors(ptr, "  ", 0);
      else if (find_in_tab(options, 'l') != 0 &&
		 (ptr->next == NULL || options[0] == '1'))
	display_colors(ptr, "\n", 0);
      ptr = ptr->next;
    }
}

void		my_show_long_list(t_list *list, char *options, char *dir)
{
  t_list	*ptr;
  int		blocks;

  blocks = 0;
  if ((ptr = malloc(sizeof(*ptr))) == NULL)
    exit(-1);
  ptr = list;
  if (find_in_tab(options, 'l') == 0 && find_in_tab(options, 'd') != 0)
    {
      while (ptr != NULL)
	{
	  blocks = blocks + ptr->blocks;
	  ptr = ptr->next;
	}
      my_printf("total %d\n", blocks / 2);
    }
  ptr = list;
  launch_display(ptr, options);
}
