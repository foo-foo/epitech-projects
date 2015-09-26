/*
** main.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr 17 12:25:06 2014 menich_a
** Last update Sat May  3 00:58:16 2014 menich_a
*/

#include "lem_in.h"
#include "my.h"

int		main()
{
  t_anthill	hill;

  if (init_anthill(&hill))
    return (1);
  if (lem_in(&hill))
    return (1);
  my_free_tab(hill.save);
  my_free_tab(hill.way);
  remove_ants_list(hill.ants);
  return (0);
}
