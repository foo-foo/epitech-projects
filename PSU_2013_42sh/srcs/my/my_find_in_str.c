/*
** my_find_in_str.c for libmy in /home/menich_a/rendu/Allum1/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 11 18:30:38 2014 menich_a
** Last update Sat Feb 15 11:23:22 2014 menich_a
*/

#include <stdlib.h>

/*
**	Return pos of to_find is str contains it. Else return (-1).
*/
int	my_find_in_str(char *str, char to_find)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (-1);
  while (str[i] != '\0')
    {
      if (str[i] == to_find)
        return (i);
      i = i + 1;
    }
  return (-1);
}
