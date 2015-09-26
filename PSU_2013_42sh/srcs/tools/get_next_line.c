/*
** get_next_line.c for get_next_line in /home/menich_a/rendu/CPE_2014_corewar/corewar/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 29 18:25:35 2014 menich_a
** Last update Sat May 31 13:52:57 2014 menich_a
*/
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "mysh.h"
#include "my.h"

char		*read_one_line(char *line)
{
  int		cpt;
  char		*str;
  int		i;

  cpt = 0;
  while (line[cpt] && line[cpt] != '\n' && line[cpt] != ';')
    jump_inhibitors(line, &cpt);
  if (line[cpt])
    cpt = cpt + 1;
  if ((str = malloc(sizeof(*str) * (cpt + 1))) == NULL)
    return (NULL);
  cpt = 0;
  i = cpt;
  while (line[cpt] && line[cpt] != '\n' && line[cpt] != ';')
    jump_inhibitors_cpy(str, line, &i, &cpt);
  if (line[cpt])
    str[i++] = '\n';
  str[i] = '\0';
  return (str);
}

int		my_fread(char buff[4097], int fd)
{
  int		ret;

  if (signal(SIGINT, &disable_sigint) == SIG_ERR)
    return (0);
  while ((ret = read(fd, buff, 4096)) > 0 && !my_str_isprintable(buff))
    {
      my_putstr("\033[32m$ \033[33m~ \033[31m> \033[0mcommand not found\n");
      buff[ret] = '\0';
    }
  if (signal(SIGINT, &my_sigint) == SIG_ERR || launch_exiting(0))
    return (0);
  return (ret);
}

char		*my_read(int fd, int ret)
{
  static int	i = 0;
  static char	buff[4097];

  if (i == 0 || buff[i] == '\0')
    {
      i = 0;
      if ((ret = read(fd, buff, 4096)) > 0 && !my_str_isprintable(buff))
	ret = my_fread(buff, fd);
      if (ret <= 0)
        {
	  if (ret)
	    my_warn(NULL, fd);
          return (NULL);
        }
      buff[ret] = '\0';
    }
  ret = i;
  while (buff[i] && buff[i] != '\n' && buff[i] != ';')
    jump_inhibitors(buff, &i);
  if (buff[i])
    i = i + 1;
  return (read_one_line(buff + ret));
}

char		*fget_next_line(int fd)
{
  char		*str;
  char		*tmp;

  str = my_read(fd, 0);
  if (str == NULL)
    return (NULL);
  while (str[my_strlen(str) - 1] != '\n')
    {
      tmp = my_read(fd, 0);
      if (tmp == NULL)
	return (str);
      str = my_strcatdup(str, tmp);
      if (str == NULL)
	return (NULL);
    }
  str[my_strlen(str) - 1] = '\0';
  return (str);
}

/*
**		If termcaps database isn't reachable:
**			=> returns fget_next_line (normal get_next_line).
**		Else => returns tc_get_next_line (using termcaps).
*/
char		*get_next_line(int fd, char **env)
{
  static char	*line = NULL;
  char		*str;
  int		i;

  i = 0;
  if ((i = init_termios(env)) == 1)
    return (fget_next_line(fd));
  if (i == -1)
    return (NULL);
  if ((str = line) != NULL)
    line = NULL;
  else
    if ((str = tc_get_next_line(fd, env)) != NULL)
      my_putchar('\n');
  while (str && str[i] && str[i] != ';')
    jump_inhibitors(str, &i);
  if (str && str[i])
    if (display_prompt(0, 0, 1) || (line = my_strdup(str + i + 1)) == NULL ||
        (str = my_xstrndup(str, i)) == NULL)
      return (NULL);
  if (init_termios(NULL))
    return (NULL);
  return (str);
}
