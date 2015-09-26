/*
** tab.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:50 2015 Anatole Menichetti
** Last update Tue Jun 16 05:09:19 2015 Anatole Menichetti
*/

#include <stdlib.h>

void	free_int_tab(int **tab)
{
  int	i;

  i = 0;
  if (tab)
    {
      while (tab[i])
	{
	  free(tab[i]);
	  i += 1;
	}
      free(tab);
    }
}

void	free_tab(char ***tab)
{
  int	y;
  int	x;

  if (tab)
    {
      y = 0;
      while (tab[y])
	{
	  x = 0;
	  while (tab[y][x])
	    {
	      free(tab[y][x]);
	      x += 1;
	    }
	  free(tab[y]);
	  y += 1;
	}
      free(tab);
    }
}

int	tablen(char ***tab)
{
  int	i;

  i = 0;
  if (tab)
    while (tab[i])
      i += 1;
  return (i);
}
