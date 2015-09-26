/*
** str.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:44 2015 Anatole Menichetti
** Last update Tue Jun 16 20:59:11 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void	putstr(char *str)
{
  if (str)
    if (write(1, str, strlen(str)) == -1 &&
	write(2, str, strlen(str)) == -1)
	perror("zappy client: write error");
}

int	fputstr(int const fd, char *str)
{
  if (str)
    return (write(fd, str, strlen(str)));
  return (0);
}

int	str_is_num(char *str)
{
  int	i;

  i = 0;
  while (str && str[i] >= '0' && str[i] <= '9')
    i += 1;
  if (!str || str[i])
    return (0);
  return (1);
}

int	str_is_float(char *str)
{
  int	i;

  i = 0;
  while (str && ((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
    {
      if (str[i] == '.' && (!i || str[i - 1] == '.'))
	return (0);
      i += 1;
    }
  if (!str || str[i])
    return (0);
  return (1);
}

char	*nbr_to_str(int nb)
{
  int	div;
  int	len;
  char	*nbr;

  div = 1;
  len = 1;
  while (nb / div > 9)
    {
      div *= 10;
      len += 1;
    }
  if (!(nbr = malloc(sizeof(*nbr) * (len + 1))))
    return (NULL);
  len = 0;
  while (div)
    {
      nbr[len] = (nb / div) + 48;
      nb %= div;
      div /= 10;
      len += 1;
    }
  nbr[len] = '\0';
  return (nbr);
}
