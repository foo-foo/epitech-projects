/*
** msg_error_exit.c for libmy in /home/menich_a/rendu/CPE-2013-BSQ/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Dec  7 02:18:07 2013 menich_a
** Last update Sat Dec  7 02:32:01 2013 menich_a
*/

#include <stdlib.h>

void	msg_error_exit(char *msg)
{
  my_putstr(msg);
  exit(-1);
}
