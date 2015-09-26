/*
** dynamic_research_mode.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Jan 18 15:47:25 2014 menich_a
** Last update Sun Jan 19 22:48:48 2014 menich_a
*/

#include <stdlib.h>
#include "my_select.h"
#include "my.h"

/*
**		Display the research bar on the last line of the window
*/
void		display_search_bar(t_size *window, t_list *list)
{
  int		width;

  width = 0;
  move_cursor(width, window->height);
  my_putstr("\033[45m\033[1mDynamic research: ");
  if (list->data != NULL)
    my_putstr(list->data);
  while (width < window->width - 18 - my_strlen(list->data))
    {
      my_putchar(' ');
      width = width + 1;
    }
  my_putstr("\033[0m");
  restore_cursor_pos();
}

char		*my_realloc(char *str, int size)
{
  char		*res;
  int		i;

  i = 0;
  res = malloc(sizeof(*res) * size);
  if (res == NULL)
    return (NULL);
  if (size == 0)
    {
      free(str);
      return (str);
    }
  if (str == NULL)
    {
      str = malloc(sizeof(*str) * size);
      if (str == NULL)
	return (NULL);
      return (str);
    }
  while (str[i] != '\0')
    i = i + 1;
  if (i >= size)
    return (str);
  my_strncat(res, str, i);
  return (res);
}

/*
**		Find pos of the first elem which correspond to str.
**		If there is no correspondance => reinit str and pos.
*/
int             find_in_list(t_list *list, char *str)
{
  t_list        *ptr;
  int           i;

  ptr = list->next;
  i = -1;
  while (ptr != list)
    {
      if (ptr->data != NULL &&
	  my_strncmp(ptr->data, str, my_strlen(str) - 1) == 0)
	{
	  if (i == -1)
	    i = ptr->pos;
	}
      ptr = ptr->next;
    }
  if (i == -1)
    {
      list->data = "No such element in list";
      free(str);
    }
  else
    list->data = str;
  return (i);
}

/*
**		Fill str with keys entered by user.
**		Then find_in_list return the pos of the element which \
**		correspond to str.
*/
int             dynamic_research_mode(t_list *list, char *buff, int pos)
{
  int		ret;
  static char   *str;
  static int    i;

  ret = 0;
  if (i == 0)
    {
      if ((str = malloc(sizeof(*str) * 2)) == NULL)
	exit(-1);
    }
  else
    if ((str = my_realloc(str, i + 2)) == NULL)
      exit(-1);
  str[i] = buff[0];
  i = i + 1;
  str[i] = '\0';
  ret = find_in_list(list, str);
  if (ret == -1)
    {
      i = 0;
      return (pos);
    }
  else
    return (ret);
  return (pos);
}
