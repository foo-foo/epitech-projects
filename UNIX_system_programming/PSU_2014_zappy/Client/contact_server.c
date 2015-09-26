/*
** contact_server.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:15 2015 Anatole Menichetti
** Last update Tue Jun 23 23:55:19 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

/*
**		Get the server size from the string received.
*/
static int	get_server_size(char *world_size, size_t server_size[2])
{
  int		i;
  int		tmp;

  i = 0;
  while (world_size[i] >= '0' && world_size[i] <= '9')
    i += 1;
  if (world_size[i] != ' ')
    return (0);
  tmp = i;
  while (world_size[i] == ' ')
    i += 1;
  if (world_size[i] < '0' || world_size[i] > '9')
    return (0);
  while (world_size[i] >= '0' && world_size[i] <= '9')
    i += 1;
  if (world_size[i] != '\n')
    return (0);
  world_size[tmp] = '\0';
  server_size[WIDTH] = atoi(world_size);
  server_size[HEIGHT] = atoi(world_size + tmp + 1);
  return (1);
}

/*
**		Get the basic informations from the server.
*/
int		contact_server(int const fd, char *team_name,
			       size_t server_size[2], int *connect_nbr)
{
  char		*data;

  if (!(data = get_next_line(fd)))
    return (msg_error(EREAD, 0, 1));
  if (strcmp(data, "BIENVENUE\n"))
    return (msg_error(ECONNECT, 0, 1));
  if (fputstr(fd, team_name) == -1 || fputstr(fd, "\n") == -1)
    return (msg_error(EWRITE, 0, 1));
  free(data);
  if (!(data = get_next_line(fd)))
    return (msg_error(EREAD, 0, 1));
  *connect_nbr = atoi(data);
  free(data);
  if (!(data = get_next_line(fd)))
    return (msg_error(EREAD, 0, 1));
  if (!get_server_size(data, server_size))
    return (msg_error(ECONNECT, 0, 1));
  free(data);
  return (0);
}
