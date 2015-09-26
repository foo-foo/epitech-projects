/*
** quit.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr  8 17:14:59 2015 Anatole Menichetti
** Last update Sat Apr 11 13:42:06 2015 Anatole Menichetti
*/

#include <string.h>
#include "../../includes/myirc.h"
#include "../../includes/server.h"

char	*my_quit(t_fd *fds, t_fd *self, char **cmd)
{
  (void)cmd;
  if (pop_fd(&fds, self))
    return (NULL);
  return (strdup("\r\n"));
}
