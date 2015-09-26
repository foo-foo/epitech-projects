/*
** circular_read.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Apr 10 10:38:10 2015 Anatole Menichetti
** Last update Sat Apr 11 16:43:52 2015 audurier julien
*/

#include <string.h>
#include <unistd.h>
#include "../../includes/myirc.h"

static void	circular_turn(char buff[BUFF_SIZE + 1], char tmp[BUFF_SIZE + 1])
{
  int		i;
  int		size;

  size = BUFF_SIZE - strlen(buff);
  i = size - 1;
  strncat(buff, tmp, BUFF_SIZE - (size + 1));
  while (tmp[++i] && tmp[i] != '\n')
    buff[i - size] = tmp[i];
  buff[BUFF_SIZE - 1] = '\n';
}

int		circular_read(int fd, char buff[BUFF_SIZE + 1])
{
  char		tmp[BUFF_SIZE + 1];
  int		ret;

  ret = 1;
  buff[0] = '\0';
  tmp[0] = '\0';
  while (tmp[ret - 1] != '\n' && (ret = read(fd, tmp, BUFF_SIZE)) > 0)
    {
      if (!fd && ret < BUFF_SIZE && tmp[ret - 1] != '\n')
	tmp[ret++] = '\n';
      tmp[ret] = '\0';
      if (strlen(tmp) + strlen(buff) > BUFF_SIZE)
	circular_turn(buff, tmp);
      else
        strcat(buff, tmp);
    }
  buff[BUFF_SIZE] = '\0';
  return (ret);
}
