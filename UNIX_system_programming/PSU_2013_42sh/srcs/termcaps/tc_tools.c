/*
** tc_termcaps.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 15 15:02:58 2014 menich_a
** Last update Sun May 25 17:42:33 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <term.h>
#include "get_next_line.h"
#include "my_termios.h"
#include "my.h"

int	display(int nb)
{
  return (write(1, &nb, 1));
}

void	launch_termcap(char *name)
{
  char	*cap;

  cap = tgetstr(name, NULL);
  if (cap)
    tputs(cap, 1, &display);
}

char	*cut_line_from_cursor(t_line *line, char *copy)
{
  char	*str;

  launch_termcap(DEL_FROM_CURS);
  if ((str = my_strndup(line->line, line->i)) == NULL)
    return (NULL);
  line->size = line->i + 1;
  if (copy != NULL + 42)
    {
      if (copy)
	free(copy);
      if ((copy = my_strdup(line->line + line->i)) == NULL)
	return (NULL);
      free(line->line);
      line->line = str;
      return (copy);
    }
  free(line->line);
  line->line = str;
  return (NULL + 1);
}

char	*get_word(char *line, int i)
{
  char	*word;
  int	save;
  int	j;

  j = 0;
  save = i;
  while (i >= 0 && line[i] != ' ')
    i = i - 1;
  word = malloc(sizeof(*word) * (save - i) + 2);
  if (!word)
    {
      msg_error("mysh: error: malloc failed.\n");
      return (NULL);
    }
  i = i + 1;
  while (i < save)
    {
      word[j] = line[i];
      j = j + 1;
      i = i + 1;
    }
  word[j] = '\0';
  return (word);
}
