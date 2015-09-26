/*
** main.c for my_select in /home/menich_a/rendu/PSU_2013_my_select/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Jan 15 15:07:22 2014 menich_a
** Last update Sun Jan 19 20:02:06 2014 menich_a
*/

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_select.h"
#include "my.h"

/*
**		Used to return selected elements to the shell.
*/
void		my_show_selected_list(t_list *list)
{
  t_list	*ptr;

  my_clear_screen();
  ptr = list->next;
  while (ptr != list)
    {
      if (ptr->rv == 1)
	{
	  write(1, ptr->data, my_strlen(ptr->data));
	  write(1, " ", 1);
	}
      ptr = ptr->next;
    }
}

/*
**		Check_env: check the TERM environnement variable for tgetent.
**		Init_termios: init terminal settings (!raw mode + !Echo mode).
**		Create a list with arguments given by user.
**		After receving selection from my_select: reinit term settings.
**		Return selection to the shell.
*/
int		main(int ac, char **av, char **env)
{
  int		i;
  t_termios	t;
  t_list	*list;

  i = 1;
  if (ac == 1 || ac == 1)
    return (msg_error("error: to few arguments\n", 1));
  if (check_env(env) == 1)
    return (1);
  if (init_termios(&t) == 1)
    return (1);
  if ((list = my_create_list()) == NULL)
    return (reinit_termios(&t));
  while (i < ac)
    {
      my_put_end_list(list, av[i], i);
      i = i + 1;
    }
  if (my_select(t, list, i - 2) == 1)
    return (reinit_termios(&t));
  my_show_selected_list(list);
  if (reinit_termios(&t) == 1)
    return (msg_error("error: cannot reinit terminal settings\n", 1));
  my_rm_list(list);
  return (0);
}
