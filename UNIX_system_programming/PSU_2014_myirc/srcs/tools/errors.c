/*
** errors.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 14:24:23 2015 Anatole Menichetti
** Last update Tue Apr  7 16:09:11 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	msg_error(char *msg, int action)
{
  if (action)
    {
      if (msg)
	perror(msg);
      else
	perror("fatal error");
    }
  else
    if (msg)
      write(2, msg, strlen(msg));
  return (EXIT_FAILURE);
}
