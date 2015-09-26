/*
** display_list.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan 17 18:22:49 2014 menich_a
** Last update Sun Jan 19 18:39:02 2014 menich_a
*/

#include <ncurses/curses.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_select.h"
#include "my.h"

/*
**		Display the element ptr with good propertys.
**		It can display it in uderline / reverse video modes.
*/
void		my_putptr(t_list *ptr, int current_pos)
{
  if (ptr->rv == 1)
    enable_reverse_video();
  if (ptr->pos == current_pos)
    {
      save_cursor_pos();
      my_putstr("\033[31m");
      my_putstr_underline(ptr->data);
      my_putstr("\033[0m");
    }
  else
    my_putstr(ptr->data);
  if (ptr->rv == 1)
    disable_reverse_video();
}

/*
**		If "display_little_column" is usefull to init ptr / pos, \
**		it's "little_display" which display elements / resize_msg.
*/
int		little_display(t_size *w, t_size *p, t_list *list, t_list *ptr)
{
  int		center_height;
  int		center_width;
  int		little_pos;

  little_pos = 0;
  while (little_pos < w->height - 1)
    {
      if (ptr == list)
	ptr = ptr->next;
      if (my_strlen(ptr->data) > w->width)
	{
	  center_height = w->height / 2;
	  center_width = w->width / 2;
	  my_clear_screen();
	  move_cursor(center_width - 2, center_height - 1);
	  my_putstr("Term");
	  move_cursor(center_width - 4, center_height);
	  my_putstr("too small");
	  return (1);
	}
      move_cursor(0, little_pos++);
      my_putptr(ptr, p->pos);
      ptr = ptr->next;
    }
  return (0);
}

/*
**		Display just one column instead of the all list. If term width is
**		smaller than elements width, display a msg to user.
*/
int		display_little_column(t_list *list, t_size *window, t_size *parse)
{
  t_list	*ptr;
  int		little_pos;

  ptr = list->next;
  while (ptr->pos != parse->pos && ptr != list)
    ptr = ptr->next;
  my_clear_screen();
  little_pos = ptr->pos;
  while (little_pos - window->height >= 0)
    little_pos = little_pos - (window->height - 1);
  while (little_pos > 1)
    {
      ptr = ptr->prev;
      little_pos = little_pos - 1;
    }
  little_display(window, parse, list, ptr);
  display_search_bar(window, list);
  return (1);
}

/*
**		This function is used to parse the list.
**		It controls the size which has been write.
**		If size which has been write is biggest than window size:
**		=> display only a column (display_little_column)
*/
int		parse_list(t_list *list, t_list *ptr, t_size *parse, t_size *w)
{
  static int	sizemax;

  if (parse->width + my_strlen(ptr->data) + 2 >= w->width)
    return (display_little_column(list, w, parse));
  if (my_strlen(ptr->data) > sizemax)
    sizemax = my_strlen(ptr->data);
  my_putptr(ptr, parse->pos);
  if (ptr->next != list)
    {
      if (parse->height + 2 < w->height)
	parse->height = parse->height + 1;
      else
        {
	  list->pos = list->pos + 1;
          parse->width = parse->width + sizemax + 3;
          sizemax = 0;
          parse->height = 0;
        }
    }
  move_cursor(parse->width, parse->height);
  return (0);
}

/*                           
**              Reinit cursor then delete the list previously displayed.
**              The element which have same pos that i is underlined.
**              Elements which have been selected (rv == 1) are displayed \
**              in reverse video.
**              Save the position of the cursor before display underlined elem.
**		Restore this position after displayed all the list.
**              Display a message if terminal size is too small for the list.
*/
int		display_list(t_list *list, int current_pos, t_size *window)
{
  t_size	parse;
  t_list	*ptr;

  parse.height = 0;
  parse.width = 0;
  parse.pos = current_pos;
  my_clear_screen();
  move_cursor(0, 0);
  list->pos = 1;
  ptr = list->next;
  while (ptr != list)
    {
      my_putstr("\033[31m . \033[0m");
      if (parse_list(list, ptr, &parse, window) == 1)
        return (1);
      ptr = ptr->next;
    }
  display_search_bar(window, list);
  return (0);
}
