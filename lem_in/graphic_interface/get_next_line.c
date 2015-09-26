/*
** get_next_line.c for get_next_line in /home/menich_a/rendu/CPE_2014_corewar/corewar/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 29 18:25:35 2014 menich_a
** Last update Sun May  4 18:38:28 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char		*my_strcatdup(char *s1, char *s2)
{
  char		*str;
  int		i;
  int		j;

  i = 0;
  j = 0;
  str = malloc(sizeof(*str) * (my_strlen(s1) + my_strlen(s2) + 1));
  if (str == NULL)
    return (NULL);
  if (str)
    {
      while (s1[i])
        str[j++] = s1[i++];
      i = 0;
      while (s2[i])
        str[j++] = s2[i++];
      str[j] = '\0';
      free(s1);
      free(s2);
    }
  return (str);
}

char		*read_one_line(char buff[BUFF_SIZE + 1], int i)
{
  int		cpt;
  int		pos;
  char		*str;

  cpt = 0;
  pos = end_of_line(buff + i) + i;
  if (pos < 0)
    pos = my_strlen(buff);
  if ((str = malloc(sizeof(*str) * (pos - i) + 2)) == NULL)
    return (NULL);
  while (i <= pos)
    str[cpt++] = buff[i++];
  str[cpt] = '\0';
  return (str);
}

char		*my_read(int fd)
{
  static int	i = -1;
  static char	buff[BUFF_SIZE + 1];
  int		ret;

  if (i == -1 || buff[i] == '\0')
    {
      i = 0;
      while (buff[i + 1])
        buff[i++] = '\0';
      ret = read(fd, buff, BUFF_SIZE);
      if (ret < 0)
        {
          msg_error("read error.\n");
          return (NULL);
        }
      if (ret == 0)
        return (NULL);
      buff[ret] = '\0';
    }
  ret = i;
  i = end_of_line(buff + i) + i + 1;
  return (read_one_line(buff, ret));
}

char		*get_next_line(int fd)
{
  char		*str;
  char		*tmp;

  str = my_read(fd);
  if (str == NULL)
    return (NULL);
  while (end_of_line(str) < 0 && my_strlen(str) < BUFF_SIZE * 10)
    {
      tmp = my_read(fd);
      if (tmp == NULL)
        return (NULL);
      str = my_strcatdup(str, tmp);
      if (str == NULL)
        return (NULL);
    }
  str[end_of_line(str)] = '\0';
  return (str);
}
