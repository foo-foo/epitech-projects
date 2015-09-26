/*
** get_next_line.c for get_next_line in /home/menich_a/rendu/CPE_2014_corewar/corewar/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 29 18:25:35 2014 menich_a
** Last update Sat May  3 19:54:41 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my.h"

/*
**		Returns pos of next line delimitor.
*/
int		end_of_line(char *str)
{
  int		i;

  i = 0;
  if (str == NULL)
    return (-1);
  while (str[i] && str[i] != '\n')
    i = i + 1;
  return (i);
}

/*
**		Returns next line of buff.
*/
char		*read_one_line(char *line)
{
  int		cpt;
  char		*str;

  cpt = 0;
  while (line[cpt] && line[cpt] != '\n')
    cpt = cpt + 1;
  if (line[cpt])
    cpt = cpt + 1;
  if ((str = malloc(sizeof(*str) * (cpt + 1))) == NULL)
    return (NULL);
  cpt = 0;
  while (line[cpt] && line[cpt] != '\n')
    {
      str[cpt] = line[cpt];
      cpt = cpt + 1;
    }
  if (line[cpt])
    str[cpt++] = '\n';
  str[cpt] = '\0';
  return (str);
}

/*
**		While it can read something:
**		1 => Treats datas line by line.
**		2 => Read again
*/
char		*my_read(int fd)
{
  static int	i = 0;
  static char	buff[BUFF_SIZE + 1];
  int		ret;

  if (i == 0 || buff[i] == '\0')
    {
      i = 0;
      while (buff[i] && i < BUFF_SIZE)
        buff[i++] = '\0';
      i = 0;
      ret = read(fd, buff, BUFF_SIZE);
      if (ret < 0 && msg_error("read error.\n"))
	return (NULL);
      if (ret == 0)
        return (NULL);
      buff[ret] = '\0';
    }
  ret = i;
  while (buff[i] && buff[i] != '\n')
    i = i + 1;
  if (buff[i])
    i = i + 1;
  return (read_one_line(buff + ret));
}

/*
**		If string received from my_read contains delimitor ('\n'):
**		=> return line (without '\n').
**		Else while there isn't a '\n' it appends string with next string.
**		Display line before to return it.
*/
char		*get_next_line(int fd)
{
  char		*str;
  char		*tmp;

  str = my_read(fd);
  if (str == NULL)
    return (NULL);
  while (str[end_of_line(str)] != '\n' && my_strlen(str) < BUFF_SIZE * 10)
    {
      tmp = my_read(fd);
      if (tmp == NULL)
        return (NULL);
      str = my_strcatdup(str, tmp);
      if (str == NULL)
        return (NULL);
    }
  str[end_of_line(str)] = '\0';
  if (my_str_isprintable(str))
    return (str);
  my_putstr(str);
  my_putchar('\n');
  return (str);
}
