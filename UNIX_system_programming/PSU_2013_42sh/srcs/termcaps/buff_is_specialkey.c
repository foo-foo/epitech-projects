/*
** buff_is_specialkey.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs/termcaps
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May  8 14:43:56 2014 menich_a
** Last update Fri May 30 19:45:43 2014 menich_a
*/

#include <stdlib.h>
#include "my.h"
#include "my_termios.h"
#include "get_next_line.h"

void		treat_dynamic_rebinding(t_line *line, int width, int prompt_width)
{
  if (line->i > 0 && line->key[5] == LEFT_KEY)
    {
      line->i = left_key(line->i, width, prompt_width);
      while (line->i > 0 && my_char_is_alphanum(line->line[line->i], 0))
	line->i = left_key(line->i, width, prompt_width);
      while (line->i > 0 && my_char_is_alphanum(line->line[line->i], 1))
	line->i = left_key(line->i, width, prompt_width);
      if (line->i > 0 && my_char_is_alphanum(line->line[line->i], 0))
	line->i = right_key(line->i, width, prompt_width);
    }
  if (line->i < line->size - 1 && line->key[5] == RIGHT_KEY)
    {
      line->i = right_key(line->i, width, prompt_width);
      while (line->i < line->size - 1 &&
	     my_char_is_alphanum(line->line[line->i], 0))
	line->i = right_key(line->i, width, prompt_width);
      while (line->i < line->size - 1 &&
	     my_char_is_alphanum(line->line[line->i], 1))
	line->i = right_key(line->i, width, prompt_width);
    }
}

void		treat_simple_rebinding(t_line *line, int width, int prompt_width)
{
  if (line->key[0] == 1)
    while (line->i > 0)
      line->i = left_key(line->i, width, prompt_width);
  else
    while (line->i < line->size && line->line[line->i])
      line->i = right_key(line->i, width, prompt_width);
}

int		treat_special_key_process(t_line *line, int width, int prompt_width)
{
  if (line->key[0] == ESCAPE_KEY && line->key[1] == 91)
    {
      if (line->key[2] == 51 && line->key[3] == 126 && line->i + 1 < line->size)
	{
	  line->i = right_key(line->i, width, prompt_width);
	  if (delete_key(line, width, prompt_width))
	    return (-1);
	}
      if (line->key[2] == 49 && line->key[3] == 59 && line->key[4] == 53)
	treat_dynamic_rebinding(line, width, prompt_width);
      if (line->i + 1 < line->size && line->key[2] == RIGHT_KEY)
	line->i = right_key(line->i, width, prompt_width);
      if (line->i > 0 && line->key[2] == LEFT_KEY)
	line->i = left_key(line->i, width, prompt_width);
      if (line->key[2] == UP_KEY)
	if (up_key(line, width, prompt_width))
	  return (-1);
      if (line->key[2] == DOWN_KEY)
	if (down_key(line, width, prompt_width))
	  return (-1);
    }
  else
    if (line->key[0] != ESCAPE_KEY)
      return (1);
  return (0);
}

int		treat_special_key(t_line *line, int width, int p_width)
{
  static char	*cpy = NULL;

  if (line->key[0] == '\v')
    {
      if ((cpy = cut_line_from_cursor(line, cpy)) == NULL)
	return (-1);
    }
  else if (line->key[0] == 21 && !line->key[1])
    {
      if (!my_free(cpy) && !(cpy = my_strndup(line->line, line->i)))
	return (-1);
      while (line->i > 0)
	if (delete_key(line, width, p_width))
	  return (-1);
    }
  else if ((line->key[0] == 23 || line->key[0] == 25) && !line->key[1])
    {
      if (line->key[0] == 23 && !(cpy = ctrl_w_key(line, cpy, width, p_width)))
	return (-1);
      if (line->key[0] == 25 && ctrl_y_key(line, cpy))
	return (-1);
    }
  else
    return (treat_special_key_process(line, width, p_width));
  return (0);
}

int		buff_is_specialkey(t_line *line, int width, int prompt_width, char **env)
{
  if (line->key[0] < 0 || (line->key[0] >= 127 && line->key[0] != 127))
    return (0);
  if ((line->key[0] == 4 || line->key[0] == DELETE_KEY) && !line->key[1])
    {
      if (line->key[0] != 4 && delete_key(line, width, prompt_width))
	return (-1);
      if (line->key[0] == 4 && line->i == 0)
	{
	  my_putchar('\n');
	  free(line->line);
	  line->line = 0;
	  return (1);
	}
    }
  else if (line->key[0] == '\f' && !line->key[1])
    ctrl_l_key(line);
  else if (line->key[0] == 1 || line->key[0] == 5)
    treat_simple_rebinding(line, width, prompt_width);
  else if (line->key[0] == '\t')
    dynamic_completion(line, env);
  else
    return (treat_special_key(line, width, prompt_width));
  return (0);
}
