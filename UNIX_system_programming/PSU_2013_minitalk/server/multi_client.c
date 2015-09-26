/*
** multi_client.c for server in /home/menich_a/rendu/PSU_2013_minitalk/server/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 22 21:50:31 2014 menich_a
** Last update Sat Mar 22 23:25:20 2014 menich_a
*/

#include <stdlib.h>
#include <signal.h>
#include "server.h"

char	*add_char(char *str, char new_char)
{
  char	*new_str;
  int	new_size;
  int	i;

  i = 0;
  new_size = 0;
  if (str)
    new_size = my_strlen(str);
  if (new_char)
    new_size = new_size + 1;
  new_str = malloc(sizeof(*new_str) * (new_size + 1));
  if (new_str == NULL)
    return (NULL);
  while (str && str[i])
    {
      new_str[i] = str[i];
      i = i + 1;
    }
  new_str[i] = new_char;
  if (new_char)
    new_str[i + 1] = '\0';
  if (str)
    free(str);
  return (new_str);
}

int	*add_client(int *clients, int new_client, int i)
{
  int	*new_clients;

  if (clients == NULL)
    {
      if ((new_clients = malloc(sizeof(*new_clients) * 2)) == NULL)
        return (NULL);
      new_clients[0] = new_client;
      new_clients[1] = -1;
      return (new_clients);
    }
  while (clients[i] != -1 && clients[i] != new_client)
    i = i + 1;
  if (clients[i] == new_client)
    return (clients);
  if ((new_clients = malloc(sizeof(*new_clients * (i + 3)))) == NULL)
    return (NULL);
  i = 0;
  while (clients[i] != -1)
    new_clients[i] = clients[i++];
  new_clients[i] = new_client;
  new_clients[i + 1] = -1;
  free(clients);
  if (kill(new_client, SIGUSR2))
    return (NULL);
  return (new_clients);
}

int	*remove_client(int *clients, int old_client)
{
  int	*new_clients;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (clients[1] == -1)
    {
      free(clients);
      return (NULL);
    }
  while (clients[i] != -1)
    i = i + 1;
  if ((new_clients = malloc(sizeof(*new_clients) * i)) == NULL)
    return (NULL);
  i = 0;
  while (clients[i] != -1)
    {
      if (clients[i] != old_client)
        new_clients[j++] = clients[i];
      i = i + 1;
    }
  new_clients[j] = -1;
  free(clients);
  return (new_clients);
}
