/*
** magic_tools.c for 42sh in /home/menich_a/rendu/PSU_2013_42sh
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun May 25 23:37:12 2014 menich_a
** Last update Fri May 30 19:38:25 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "mysh.h"
#include "my.h"

/*                                                                                                                  
**              Returns new PWD by executing pwd.                                                                    
*/
int	check_error(int fd[2])
{
  if (close(fd[0]) < 0)
    return (my_warn(NULL, fd[0]));
  if (close(fd[1]) < 0)
    return (my_warn(NULL, fd[1]));
  return (0);
}

int	get_file_size(int fd)
{
  char	*buff;
  int	i;

  i = 0;
  while ((buff = fget_next_line(fd)) != NULL)
    {
      free(buff);
      i = i + 1;
    }
  return (i);
}

char	**my_str_to_wordtab(char *str)
{
  char	**tab;
  int	save;
  int	i;
  int	j;

  i = 0;
  j = 0;
  tab = NULL;
  while (str[i])
    {
      while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i = i + 1;
      if (str[i])
        {
          if ((tab = realloc(tab, sizeof(*tab) * (j + 2))) == NULL)
            return (NULL);
          save = i;
          while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            i = i + 1;
          if ((tab[j] = my_strndup(str + save, i - save)) == NULL)
            return (NULL);
          tab[++j] = NULL;
        }
    }
  return (tab);
}

int	hidenp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i])
    {
      if (!my_strncmp(s1 + i, s2, my_strlen(s2) - 1))
        return (i);
      i = i + 1;
    }
  return (-1);
}

int	check_magic_quote(char **cmd)
{
  int	y;

  y = 0;
  while (cmd[y] && (cmd[y][0] != MAGIC_QUOTE || cmd[y][1]))
    y++;
  if (cmd[y])
    return (0);
  return (1);
}
