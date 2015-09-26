/*
** my_tools.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 15 15:12:16 2014 menich_a
** Last update Sun Jan 19 17:40:52 2014 menich_a
*/

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <ncurses/curses.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_select.h"
#include "my.h"

/*
**		Used for tputs's fct ptr.
*/
int		display(int nb)
{
  int		ret;

  if (g_fd != -1)
    ret = write(g_fd, &nb, 1);
  return (ret);
}

/*
**		Used to ignore SIGTSTP (ctrl + Z).
*/
void		my_ignore_signal(int signal)
{

}

/*
**		Used to exit my_select if receved kill signal.
*/
void		my_kill(int signal)
{
  t_termios	t;

  if (signal == SIGTERM || signal == SIGKILL || signal == SIGINT)
    {
      reinit_then_exit(t, NULL, 0);
    }
}

/*
**		Element position is determined by i.
**		Select element (my_select will now display it in reverse video)
*/
int		select_elem(t_list *list, int pos)
{
  t_list	*ptr;

  ptr = list->next;
  while (ptr != list && ptr->pos != pos)
    ptr = ptr->next;
  if (ptr == list)
    return (1);
  if (ptr->rv == 0)
    ptr->rv = 1;
  else
    ptr->rv = 0;
  return (0);
}

/*
**		Element position is determined by i.
**		Remove element from the list.
**		Then, it adjusts elements positions.
*/
int		delete_elem(t_termios t, t_list *list, int pos, int posmax)
{
  t_list	*ptr;

  ptr = list->next;
  while (ptr != list && ptr->pos != pos)
    ptr = ptr->next;
  if (ptr == list)
    return (-1);
  my_rm_from_list(list, ptr);
  if (my_list_size(list) == 0)
    reinit_then_exit(t, "my_select: list is empty\n", 0);
  ptr = list->next;
  while (ptr != list && ptr->pos != pos + 1)
    ptr = ptr->next;
  while (ptr != list)
    {
      ptr->pos = ptr->pos - 1;
      ptr = ptr->next;
    }
  if (pos == posmax)
    pos = pos - 1;
  return (pos);
}
