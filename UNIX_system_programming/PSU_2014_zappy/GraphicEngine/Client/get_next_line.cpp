/*
** get_next_line.c for get_next_line in /home/rosain_f/Exo/getnextline
**
** Made by rosain_f
** Login   <rosain_f@epitech.net>
**
** Started on  Tue Feb 18 13:24:14 2014 rosain_f
// Last update Fri Jul  3 04:50:44 2015 Younes Iddahamou
*/

#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

static char	*new_line(char *line, char *read_char)
{
  if (line == NULL)
    {
      if ((line = (char*)malloc(sizeof(char))) == NULL)
	{
	  printf("Can't perform Malloc.\n");
	  return (NULL);
	}
      line[0] = '\0';
    }
  if ((line = (char*)realloc(line, (strlen(line) + 2) * sizeof(char))) == NULL)
    return (NULL);
  line = strcat(line, read_char);
  return (line);
}

static int	init_gnl(char **line, char **read_char)
{
  if ((*read_char = (char*)malloc(2 * sizeof(char))) == NULL)
    {
      printf("Can't perform Malloc.\n");
      return (-1);
    }
  (*read_char)[0] = '\0';
  (*read_char)[1] = '\0';
  *line = NULL;
  return (0);
}

char		*get_next_line(const int fd)
{
  char		*line;
  char		*read_char;
  int		ret;

  if (init_gnl(&line, &read_char) == -1)
    return (NULL);
  while (read_char[0] != '\n')
    {
      ret = read(fd, read_char, 1);
      if (ret == -1)
	printf("Can't perform read.\n");
      if (ret == 0)
	{
	  free(read_char);
	  return (line);
	}
      else
	if ((line = new_line(line, read_char)) == NULL)
	  return (NULL);
    }
  free(read_char);
  line[strlen(line) - 1] = '\n';
  line[strlen(line)] = '\0';
  return (line);
}
