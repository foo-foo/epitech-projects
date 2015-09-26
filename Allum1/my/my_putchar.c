/*
** my_putchar.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:24:38 2013 menich_a
** Last update Thu Jan 30 15:27:49 2014 menich_a
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}
