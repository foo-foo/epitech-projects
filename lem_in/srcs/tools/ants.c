/*
** ants.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Apr 26 18:53:33 2014 menich_a
** Last update Sat May  3 18:59:49 2014 menich_a
*/

#include <stdlib.h>
#include "lem_in.h"
#include "my.h"

/*
**	Check if ant is the last to move for this turn.
**	If it's true then display_ant should display '\n'.
*/
int     last_ant_to_move(t_ant *ant)
{
  t_ant *ptr;

  if (!ant->next)
    return (0);
  if (ant->way && ant->way[0] && ant->way[1] == NULL)
    return (1);
  ptr = ant->next;
  while (ptr)
    {
      if (ptr->wait == 0)
        return (1);
      ptr = ptr->next;
    }
  return (0);
}

/*
**	Diplay the current room where is the ant.
*/
int    display_ant(t_ant *ant, char *last_room, int n)
{
  if (!ant->way[ant->i] || my_strcmp(ant->way[ant->i], ant->way[0]))
    {
      my_putchar('P');
      my_put_nbr(ant->num);
      my_putchar('-');
      if (ant->way[ant->i])
        my_putstr(ant->way[ant->i]);
      else
        my_putstr(last_room);
      if (last_ant_to_move(ant))
        my_putchar(' ');
      else
        my_putchar('\n');
      if (!ant->way[ant->i])
        {
          ant->state = ARRIVED;
	  return (n - 1);
        }
    }
  return (n);
}

int		add_one_ant(t_ant **ants, int num)
{
  t_ant		*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  new->num = num;
  new->i = 0;
  new->state = 0;
  new->next = *ants;
  *ants = new;
  return (0);
}

/*
**		Init an ant list with hill->ants_nbr ants.
*/
int		init_ant_list(t_anthill *hill)
{
  int		n;

  n = hill->ants_nbr;
  hill->ants = NULL;
  while (n)
    {
      if (add_one_ant(&hill->ants, n))
        return (1);
      n = n - 1;
    }
  return (0);
}

/*
**		Free ants list.
*/
void		remove_ants_list(t_ant *list)
{
  t_ant		*ptr;
  t_ant		*to_rm;

  if (list)
    {
      ptr = list->next;
      to_rm = list;
      while (ptr)
        {
          list = ptr;
          my_free_tab(to_rm->way);
          free(to_rm);
          to_rm = ptr;
          ptr = ptr->next;
        }
      my_free_tab(to_rm->way);
      free(to_rm);
    }
}
