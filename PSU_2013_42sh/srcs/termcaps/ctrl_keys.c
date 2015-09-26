/*
** ctrl_keys.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue May 20 21:40:44 2014 menich_a
** Last update Sun May 25 17:07:48 2014 menich_a
*/

#include <stdlib.h>
#include "my_termios.h"
#include "get_next_line.h"
#include "my.h"

void	ctrl_l_key(t_line *line)
{
  int	i;

  launch_termcap(CLEAR);
  display_prompt(0, 0, 0);
  my_putstr(line->line);
  i = my_strlen(line->line);
  while (i-- > line->i)
    launch_termcap(MOVE_LEFT);
}

char	*ctrl_w_key(t_line *line, char *copy, int width, int prompt_width)
{
  int	i;

  i = line->i;
  while (i > 0 && line->line[i - 1] == ' ')
    i = i - 1;
  while (i > 0 && line->line[i - 1] != ' ')
    i = i - 1;
  if (copy)
    free(copy);
  copy = my_strndup(line->line + i, line->i - i);
  if (!copy)
    return (NULL);
  while (line->i > 0 && line->line[line->i - 1] == ' ')
    if (delete_key(line, width, prompt_width))
      return (NULL);
  while (line->i > 0 && line->line[line->i - 1] != ' ')
    if (delete_key(line, width, prompt_width))
      return (NULL);
  return (copy);
}

int	ctrl_y_key(t_line *line, char *copy)
{
  int	i;
  char	*tmp1;
  char	*tmp2;

  my_putstr(copy);
  my_putstr(line->line + line->i);
  if ((tmp1 = my_strndup(line->line, line->i)) == NULL)
    return (1);
  if ((tmp2 = my_str_catdup(tmp1, copy)) == NULL)
    return (1);
  free(tmp1);
  if ((tmp1 = my_str_catdup(tmp2, line->line + line->i)) == NULL)
    return (1);
  free(tmp2);
  i = line->i + my_strlen(copy) + 1;
  line->i = line->size + my_strlen(copy);
  while (line->i-- > i)
    launch_termcap(MOVE_LEFT);
  line->size = line->size + my_strlen(copy);
  free(line->line);
  line->line = tmp1;
  return (0);
}
