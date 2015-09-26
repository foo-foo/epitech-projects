/*
** my.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/tools
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 12 13:00:48 2015 Anatole Menichetti
** Last update Thu Mar 26 11:28:49 2015 Anatole Menichetti
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	putstr(char *str)
{
  if (str)
    if (write(1, str, strlen(str)) == -1)
      if (write(2, str, strlen(str)) == -1)
	perror("myftp: failure by writting on stdout");
  return (1);
}

int	fputstr(int fd, char *str)
{
  int	ret;

  ret = 0;
  if (str)
    ret = write(fd, str, strlen(str));
  if (fd == 2)
    ret = 1;
  return (ret);
}

void	*my_free(void *ptr)
{
  if (ptr)
    free(ptr);
  return (NULL);
}

int	my_cmdcmp(char *buff, char *cmd)
{
  int	s;

  s = strlen(cmd);
  if (!strncmp(buff, cmd, s) &&
      (buff[s] == ' ' || buff[s] == '\t' || buff[s] == '\n'))
    return (0);
  return (-1);
}

char	*my_get_str(int nb)
{
  int	i;
  int	div;
  char	*nbr;

  i = 0;
  div = 1;
  if (nb < 0)
    return (NULL);
  while (nb / div > 9)
    {
      i = i + 1;
      div = div * 10;
    }
  if ((nbr = malloc(sizeof(*nbr) * (i + 2))) == NULL)
    return (NULL);
  i = 0;
  while (div != 0)
    {
      nbr[i] = nb / div + 48;
      i = i + 1;
      nb = nb % div;
      div = div / 10;
    }
  nbr[i] = '\0';
  return (nbr);
}
