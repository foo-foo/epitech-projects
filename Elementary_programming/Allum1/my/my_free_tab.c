/*
** my_free_tab.c for  in /home/menich_a/rendu/Allum1/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Feb 14 12:48:27 2014 menich_a
** Last update Fri Feb 14 18:19:19 2014 menich_a
*/

#include <stdlib.h>

void	my_free_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i = i + 1;
    }
  free(tab);
}
