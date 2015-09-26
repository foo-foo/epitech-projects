/*
** errors.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:22 2015 Anatole Menichetti
** Last update Tue Jun 23 23:55:33 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

int	msg_error(char *msg, char *end_of_msg, int const action)
{

  fputstr(2, "\033[31mzappy client: ");
  if (action)
    {
      if (msg)
	perror(msg);
      else
	perror("fatal error");
      fputstr(2, "\033[0m");
      return (EXIT_FAILURE);
    }
  fputstr(2, msg);
  fputstr(2, end_of_msg);
  fputstr(2, ".\n\033[0m");
  return (EXIT_FAILURE);
}
