/*
** my_create_list.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Nov 28 14:29:45 2013 menich_a
** Last update Sun Dec  1 21:30:12 2013 menich_a
*/

#include "my_ls.h"
#include <stdlib.h>

t_list		*create_list(t_list *list, char **av, int i, int j)
{
  while (av[i] != NULL)
    {
      if (av[i][0] != '-')
	{
	  my_put_in_list(&list, av[i], 4, "");
	}
      else if (av[i][0] == '-' && av[i][1] == '-')
	{
	  while (av[++i] != NULL)
	    {
	      my_put_in_list(&list, av[i], 4, "");
	    }
	}
      i = i + 1;
    }
  return (list);
}
