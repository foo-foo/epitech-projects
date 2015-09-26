/*
** main.c for lemipc in /home/menich_a/rendu/PSU_2014_lemipc/srcs
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Mar  6 10:46:47 2015 Anatole Menichetti
** Last update Sun Mar  8 22:20:48 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include "../includes/lemipc.h"

int		main(int ac, char **av)
{
  t_player	p;

  p.m_size = init_params(ac, av);
  if (!p.m_size)
    return (EXIT_FAILURE);
  p.t_nbr = av[1][0];
  if (!init_game(&p))
    return (EXIT_FAILURE);
  if (!p.pos)
    printf(LAUNCH_MSG, p.t_nbr);
  if (!join_game(&p))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
