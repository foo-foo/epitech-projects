/*
** my_find_in_tab.c for libmy in /home/menich_a/rendu/Allum1/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 11 18:31:10 2014 menich_a
** Last update Sat Feb 15 11:24:42 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

/*
**	Return pos of the char* which contains `to_find'.
**	If to_find cannot be found return -1.
*/
int	my_find_in_tab(char **tab, char to_find)
{
  int	i;

  i = 0;
  if (tab == NULL)
    return (-1);
  while (tab[i] != NULL)
    {
      if (my_find_in_str(tab[i], to_find) >= 0)
        return (i);
      i = i + 1;
    }
  return (-1);
}
