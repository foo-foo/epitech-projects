/*
** msg_error_return.c for libmy.a in /home/menich_a/rendu/PSU_2013_my_select/sources/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 15 15:50:37 2014 menich_a
** Last update Sat Jan 18 11:00:07 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

int	msg_error(char *msg, int status)
{
  if (msg != NULL)
    {
      my_putstr(msg);
    }
  return (status);
}
