/*
** tc_get_next_line.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue May  6 15:42:10 2014 menich_a
** Last update Fri May 30 19:51:04 2014 menich_a
*/

#include <ncurses/curses.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my_termios.h"
#include "my.h"

void		add_one_char_process(t_line *line, int width, int prompt_width)
{
  int		tmp;

  line->line[line->size] = '\0';
  tmp = line->i;
  launch_termcap(SAVE_CURSOR);
  while (line->line[tmp])
    {
      my_putchar(line->line[tmp]);
      tmp = tmp + 1;
    }
  launch_termcap(RESTORE_CURSOR);
  if (line->i % width + prompt_width == width - 1)
    {
      tmp = width;
      while (tmp)
	{
	  launch_termcap(MOVE_LEFT);
	  tmp = tmp - 1;
	}
      launch_termcap(MOVE_DOWN);
    }
  else
    launch_termcap(MOVE_RIGHT);
  line->i = line->i + 1;
  line->size = line->size + 1;
}


void		my_add_char(t_line *line, int *index, char *index1, char *index2)
{
  int		tmp;
  char		tmp1;
  char		tmp2;

  tmp = *index;
  tmp1 = *index1;
  tmp2 = *index2;
  while (line->line[tmp])
    {
      tmp2 = line->line[tmp];
      line->line[tmp] = tmp1;
      tmp = tmp + 1;
      tmp1 = tmp2;
    }
  *index = tmp;
  *index1 = tmp1;
  *index2 = tmp2;
}

int		add_one_char(t_line *line, int width, int prompt_width)
{
  int		tmp;
  char		tmp1;
  char		tmp2;
  int		i;

  i = 0;
  while (line->key[i])
    {
      if ((line->line = realloc(line->line, line->size + 2)) == NULL)
	return (msg_error("mysh: error: realloc failed.\n"));
      if (line->line[line->i] == '\0')
	line->line[line->i] = line->key[i];
      else
	{
	  tmp = line->i;
	  tmp1 = line->line[tmp];
	  line->line[tmp] = line->key[i];
	  tmp = tmp + 1;
	  my_add_char(line, &tmp, &tmp1, &tmp2);
	  line->line[tmp] = tmp1;
	}
      add_one_char_process(line, width, prompt_width);
      i = i + 1;
    }
  return (0);
}

int		init_line(t_line *line)
{
  line->i = 0;
  line->history_index = 0;
  if ((line->line = malloc(sizeof(char) * 1)) == NULL)
    return (msg_error("mysh: error: malloc failed.\n"));
  line->line[0] = '\0';
  line->key[0] = '\0';
  line->size = 1;
  line->save = NULL;
  return (0);
}

char		*tc_get_next_line(int fd, char **env)
{
  t_line	line;
  int		window_width;
  int		prompt_width;
  int		ret;

  prompt_width = display_prompt(NULL, 0, 2);
  if ((window_width = tgetnum(WINDOW_WIDTH)) == -1 || init_line(&line))
    return (NULL);
  while ((ret = read(fd, line.key, BUFF_SIZE)) > 0 &&
	 line.key[0] != '\n' && line.key[0] != '\r')
    {
      line.key[ret] = '\0';
      if ((ret = buff_is_specialkey(&line, window_width, prompt_width, env)))
	if (ret < 0 || !line.line || add_one_char(&line, window_width, prompt_width))
	  return (NULL);
    }
  if (ret <= 0)
    {
      if (ret < 0)
	msg_error("mysh: read error: exiting.\n");
      return (NULL);
    }
  treat_simple_rebinding(&line, window_width, prompt_width);
  return (line.line);
}
