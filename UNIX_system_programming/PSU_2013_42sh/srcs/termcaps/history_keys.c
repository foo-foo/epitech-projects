/*
** history_keys.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs/termcaps
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May  8 14:34:13 2014 menich_a
** Last update Sun May 25 22:50:54 2014 menich_a
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my.h"

int	take_history_line(t_line *line, char *buff, int width, int prompt_width)
{
  while (line->i > 0)
    line->i = left_key(line->i, width, prompt_width);
  if ((cut_line_from_cursor(line, NULL + 42)) == NULL)
    return (-1);
  free(line->line);
  line->line = buff;
  if (line->line[my_strlen(line->line) - 1] == '\n')
    line->line[my_strlen(line->line) - 1] = '\0';
  my_putstr(line->line);
  line->i = my_strlen(line->line);
  line->size = my_strlen(line->line) + 1;
  if (line->line == line->save)
    {
      line->history_index = line->history_index - 1;
      line->save = NULL;
    }
  return (0);
}

int	up_key(t_line *line, int width, int prompt_width)
{
  char	**history;
  char	*history_line;

  if (line->history_index == 0)
    if ((line->save = my_strdup(line->line)) == NULL)
      return (-1);
  if ((history = get_history()) == NULL)
    return (-1);
  if (history == NULL + 1)
    return (0);
  if (my_tablen(history) <= line->history_index)
    return (0);
  line->history_index = line->history_index + 1;
  history_line = my_strdup(history[my_tablen(history) - line->history_index]);
  if (!history_line)
    return (-1);
  return (take_history_line(line, history_line, width, prompt_width));
}

int	down_key(t_line *line, int width, int prompt_width)
{
  char	**history;
  char	*history_line;

  if (!line->history_index)
    return (0);
  if (line->history_index == 1)
    return (take_history_line(line, line->save, width, prompt_width));
  history = get_history();
  if (!history)
    return (-1);
  if (history == NULL + 1)
    return (0);
  if (my_tablen(history) <= 0)
    return (my_tablen(history));
  line->history_index = line->history_index - 1;
  history_line = my_strdup(history[my_tablen(history) - line->history_index]);
  if (!history_line)
    return (-1);
  return (take_history_line(line, history_line, width, prompt_width));
}
