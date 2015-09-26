/*
** my_putstr.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:45:28 2013 menich_a
** Last update Fri May 23 20:04:43 2014 menich_a
*/

#include <unistd.h>
#include "my.h"

void	my_putstr(char *str)
{
  int	fd;

  if (str)
    {
      fd = get_fd(1, 1, 1);
      write(fd, str, my_strlen(str));
    }
}
