/*
** parentheses.c for  in /home/bencha_a/40two/PSU_2013_minishell2/srcs/builtins
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Sat May 10 13:56:56 2014 bencharif
** Last update Sun May 25 21:46:47 2014 menich_a
*/

#include <stdlib.h>
#include "mysh.h"
#include "my.h"

char	*get_correct_path(void)
{
  char	*tmp;
  char	*path;
  char	*tmp2;

  tmp2 = get_history_path(NULL);
  tmp = my_strndup(tmp2, my_strlen(tmp2) - 11);
  if (tmp == NULL)
    return (NULL);
  path = malloc(sizeof(*path) * (my_strlen(tmp) + 5));
  if (path == NULL)
    return (NULL);
  my_strcpy(path, tmp);
  my_strcat(path, "mysh");
  free(tmp);
  return (path);
}

int	check_brackets(char **cmd)
{
  int	i;
  int	x;
  int	check;

  check = 0;
  x = 0;
  i = 0;
  while (cmd[i] != NULL)
    {
      if (cmd[i][0] == O_BRACKET)
	{
	  if (cmd[i][1] == C_BRACKET)
	    return (-1);
	  while (cmd[i][x])
	    x++;
	  if (cmd[i][x - 1] == C_BRACKET)
	    check = check + 1;
	  else
	    return (-1);
	}
      i++;
    }
  return (check);
}

char	**substitute_brackets(char **tmp, int *y, char *brackets)
{
  int	j;

  j = *y;
  tmp = realloc(tmp, (my_tablen(tmp) + 8) * sizeof(char*));
  if (tmp == NULL)
    return (NULL);
  tmp[j] = my_strdup("touch");
  tmp[j + 1] = my_strdup(".mysh_conf");
  if (!tmp[j] || !tmp[j + 1] || !(tmp[j + 2] = malloc(sizeof(*tmp[j + 2]) * 2)))
    return (NULL);
  tmp[j + 2][0] = PIPE;
  tmp[j + 2][1] = '\0';
  tmp[j + 3] = my_strdup("echo");
  tmp[j + 4] = my_strndup(brackets + 1, my_strlen(brackets) - 2);
  free(brackets);
  if (!tmp[j + 3] || !tmp[j + 4] ||
      !(tmp[j + 5] = malloc(sizeof(*tmp[j + 5]) * 2)))
    return (NULL);
  tmp[j + 5][0] = PIPE;
  tmp[j + 5][1] = '\0';
  if ((tmp[j + 6] = get_correct_path()) == NULL)
    return (NULL);
  *y = j + 6;
  return (tmp);
}

char	**exec_brackets(char **cmd)
{
  char	**tmp;
  int	j;
  int	y;

  y = 0;
  j = 0;
  tmp = NULL;
  while (cmd[y] != NULL)
    {
      if (cmd[y][0] == O_BRACKET)
	tmp = substitute_brackets(tmp, &j, cmd[y]);
      else
	if ((tmp = realloc(tmp, (my_tablen(tmp) + 2) * sizeof(char*))))
	  tmp[j] = cmd[y];
      if (tmp == NULL)
	return (NULL);
      j++;
      y++;
      tmp[j] = NULL;
    }
  free(cmd);
  return (tmp);
}
