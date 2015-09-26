/*
** search_in_list.c for  in /home/bencha_a/lem-in/v1.6/interface_graphique
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri May  2 19:01:55 2014 bencharif
** Last update Sun May  4 19:21:39 2014 menich_a
*/

#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "graph.h"

int		connections(t_coord *elem, char *tmp, char *tmp2, int i)
{
  if (strcmp(elem->room_name, tmp) == 0) /* strcmp */
    {
      i = 0;
      if (elem->connection == NULL)
	{
	  elem->connection = malloc(sizeof(char*) * 2);
	  if (!elem->connection)
	    return (-1);
	  elem->connection[0] = NULL;
	}
      else
	{
	  elem->connection = my_realloc(elem->connection);
	  if (!elem->connection)
	    return (-1);
	}
      while (elem->connection[i])
	i = i + 1;
      elem->connection[i] = strdup(tmp2);
      if (!elem->connection[i])
	return (-1);
      elem->connection[i + 1] = NULL;
    }
  return (0);
}


int		my_search_in_list(t_coord *begun, char *str, int i, int a)
{
  t_coord	*elem;
  char		*tmp;
  char		*tmp2;

  elem = begun;
  if ((tmp = malloc(my_strlen(str) * sizeof(char))) == NULL)
    return (-1);
  while (str[i] && str[i] != '\n' && str[i] != '-')
    tmp[a++] = str[i++];
  tmp[a] = '\0';
  while (str[i] == '-')
    i = i + 1;
  if ((tmp2 = strdup(str + i)) == NULL)
    return (-1);
  while (elem)
    {
      if (connections(elem, tmp, tmp2, i) || connections(elem, tmp2, tmp, i))
	return (-1);
      elem = elem->next;
    }
  free(tmp);
  free(tmp2);
  return (0);
}
