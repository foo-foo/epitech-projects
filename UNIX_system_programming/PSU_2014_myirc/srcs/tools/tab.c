/*
** tab.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/tools
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 11:17:39 2015 Anatole Menichetti
** Last update Thu Apr  9 16:51:17 2015 Anatole Menichetti
*/

#include <stdlib.h>

void	free_tab(char **tab)
{
  int	i;

  if (tab)
    {
      i = 0;
      while (tab[i])
	{
	  free(tab[i]);
	  i += 1;
	}
      free(tab);
    }
}

int	tablen(char **tab)
{
  int	i;

  i = 0;
  if (tab)
    while (tab[i])
      i += 1;
  return (i);
}
