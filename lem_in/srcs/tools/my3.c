/*
** my3.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Apr 20 15:38:59 2014 menich_a
** Last update Sun May  4 20:08:16 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"

/*
**	Return a tab copy with one more pointer allocated.
*/
char	**my_realloc(char **tab)
{
  char	**new;
  int	i;

  i = 0;
  if (!tab)
    return (NULL);
  while (tab[i])
    i = i + 1;
  new = malloc(sizeof(*new) * (i + 2));
  if (!new)
    return (NULL);
  i = 0;
  while (tab[i])
    {
      new[i] = tab[i];
      i = i + 1;
    }
  free(tab);
  new[i] = NULL;
  return (new);
}

int	my_str_isprintable(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    {
      if (str[i] < 32 || str[i] > 126)
	return (1);
      i = i + 1;
    }
  return (0);
}

int	check_line_syntax(char *line)
{
  int	i;
  int	j;

  i = 0;
  while (line[i] == ' ')
    i = i + 1;
  if (!line[i])
    return (msg_error("lem_in: error: empty line: end of acquisition.\n"));
  while (line[i] && line[i] != ' ' && line[i] != '-')
    i = i + 1;
  j = i;
  if (line[i])
    i = i + 1;
  while (line[i] && line[i] != ' ' && line[i] != '-')
    i = i + 1;
  if (line[j] == '-' && line[i])
    return (msg_error("lem_in: error: invalid line: end of acquisition.\n"));
  if (line[i])
    i = i + 1;
  while (line[i] && line[i] != ' ')
    i = i + 1;
  if (line[i])
    return (msg_error("lem_in: error: invalid line: end of acquisition.\n"));
  return (0);
}

/*
**	Check if line syntax is conform.
**	Anthill acquisition is stopped after first non conform line.
*/
int	my_line_isvalid(char *line)
{
  if (my_str_isprintable(line))
    return (msg_error("lem_in: error: invalid line: end of acquisition.\n"));
  if (line[0] == '#')
    {
      if (my_strcmp(line, "##start") && my_strcmp(line, "##end") &&
	  line[1] == '#')
        {
          msg_error("lem_in: error: unknown command `");
          msg_error(line);
          return (msg_error("`: end of anthill acquisition.\n"));
        }
      return (0);
    }
  return (check_line_syntax(line));
}
