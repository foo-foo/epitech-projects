/*
** my_putstr.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:45:28 2013 menich_a
** Last update Sun Jan 19 18:44:35 2014 menich_a
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_select.h"
#include "my.h"

void	my_putstr(char *str)
{
  if (g_fd != -1 && str != NULL)
    write(g_fd, str, my_strlen(str));
}
