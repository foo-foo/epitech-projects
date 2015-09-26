/*
** my_putchar.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:24:38 2013 menich_a
** Last update Sun Jan 19 17:41:17 2014 menich_a
*/

#include <unistd.h>
#include "my_select.h"

void	my_putchar(char c)
{
  if (g_fd != -1)
    write(g_fd, &c, 1);
}
