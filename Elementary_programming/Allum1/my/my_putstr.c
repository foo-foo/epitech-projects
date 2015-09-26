/*
** my_putstr.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:45:28 2013 menich_a
** Last update Tue Feb 11 19:20:32 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

void	my_putstr(char *str)
{
  if (str != NULL)
    write(1, str, my_strlen(str));
}
