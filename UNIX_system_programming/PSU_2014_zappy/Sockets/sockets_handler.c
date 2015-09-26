/* sockets_handler.c for sockets_handler in /home/rosain_f/projects/myFTP/tp
** 
** Made by Francois Rosain
** Login   <rosain_f@epitech.net>
** 
** Started on  Mon Mar  9 17:08:37 2015 Francois Rosain
** Last update Tue Apr  7 13:23:01 2015 Francois Rosain
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "sockets.h"

int			create_socket(int *fd)
{
  struct protoent	*pe;

  if ((pe = getprotobyname("TCP")) == NULL)
    {
      printf("Error : Can\'t perform getprotobyname.\n");
      return (-1);
    }
  if ((*fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      printf("Error : Can\'t perform socket.\n");
      return (-1);
    }
  return (0);
}

int			destroy_socket(int fd)
{
  if (close(fd) == -1)
    {
      printf("Error : Can\'t perform close.\n");
      return (-1);
    }
  return (0);
}
