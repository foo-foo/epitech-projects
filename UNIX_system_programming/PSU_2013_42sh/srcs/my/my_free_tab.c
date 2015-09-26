/*
** my_free_tab.c for libmy.a in /home/menich_a/rendu/PSU_2013_minishell1/lib/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan  3 11:45:50 2014 menich_a
** Last update Tue May 20 11:35:41 2014 menich_a
*/

#include <stdlib.h>

char	*my_free(char *str)
{
  if (str)
    free(str);
  return (NULL);
}

char	**my_free_tab(char **tab)
{
  int	i;

  i = 0;
  if (tab)
    {
      while (tab[i] != NULL)
	{
	  free(tab[i]);
	  i = i + 1;
	}
      free(tab);
    }
  return (NULL);
}
