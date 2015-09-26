/*
** dest_tab.c for  in /home/auduri_a/rendu/PSU_2014_myirc
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Thu Apr  9 13:08:42 2015 audurier julien
** Last update Sat Apr 11 16:45:11 2015 audurier julien
*/

#include <stdlib.h>
#include <string.h>

static int	get_dest_nbr(char *str)
{
  int		i;
  int		nb;

  i = 0;
  nb = 0;
  while (str && str[i])
    {
      if (str[i] == ',')
	++nb;
      ++i;
    }
  return (nb + 1);
}

static int	get_destlen(char *str, int pos)
{
  int		i;

  i = 0;
  while (str && str[pos] && str[pos] != ',')
    {
      ++pos;
      ++i;
    }
  return (i);
}

char		**dest_tab(char *str)
{
  char		**dest;
  int		size;
  int		i;
  int		pos;

  pos = 0;
  i = 0;
  size = get_dest_nbr(str);
  if ((dest = malloc (sizeof(char*) * (size + 1))) == NULL)
    return (NULL);
  while (i < size)
    {
      if ((dest[i] = strndup(str + pos, get_destlen(str,  pos))) == NULL)
	return (NULL);
      pos += get_destlen(str, pos) + 1;
      ++i;
    }
  dest[i] = NULL;
  return (dest);
}
