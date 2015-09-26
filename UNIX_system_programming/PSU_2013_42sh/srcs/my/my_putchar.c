/*
** my_putchar.c for libmy in /home/menich_a/rendu/PSU_2013_minishell2/sources/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Feb 17 14:47:38 2014 menich_a
** Last update Sun May 25 11:31:36 2014 menich_a
*/

#include <unistd.h>
#include "my.h"

void	my_putchar(char c)
{
  int	fd;

  fd = get_fd(1, 1, 1);
  write(fd, &c, 1);
}
