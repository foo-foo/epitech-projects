/*
** argument.c for arg in /home/lauret_s/rendu/PSU_2014_zappy/Server
**
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
**
** Started on  Sun Jul  5 15:38:28 2015 Sebastien Lauret
** Last update Sun Jul  5 16:19:18 2015 Bastos-Fix
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header/env.h"
#include "header/fonction.h"

static void	default_value(t_env *env)
{
  env->port = 4242;
  env->map.width = 15;
  env->map.height = 15;
  env->max_nb_team = 1;
  env->nb_team = 0;
  env->time = 100;
}

static int	arg_teamlen(char **av, int i)
{
  int		nb;

  nb = 0;
  ++i;
  while (av[i] && av[i][0] != '-')
    {
      nb++;
      i++;
    }
  return (nb);
}

static int	init_team(char **av, t_env *env, int i)
{
  int		nb;

  env->nb_team = arg_teamlen(av, i);
  if ((env->teams = malloc(sizeof(t_team) * (env->nb_team + 1))) == NULL)
    return (-1);
  nb = 0;
  while (nb <= env->nb_team)
    {
      env->teams[nb].name = (nb == env->nb_team) ? NULL : av[i + nb + 1];
      if (nb < env->nb_team && strcmp(env->teams[nb].name, "GRAPHIC") == 0)
	return (-1);
      env->teams[nb].clients.root = 1;
      env->teams[nb].clients.next = &env->teams[nb].clients;
      env->teams[nb].clients.prev = &env->teams[nb].clients;
      ++nb;
    }
  return (0);
}

int	init_args(int ac, char **av, t_env *env)
{
  int	i;

  i = 0;
  default_value(env);
  while (i < ac)
    {
      if (strcmp(av[i], "-p") == 0 && av[i + 1])
	env->port = atoi(av[i + 1]);
      else if (strcmp(av[i], "-x") == 0 && av[i + 1])
	env->map.width = atoi(av[i + 1]);
      else if (strcmp(av[i], "-y") == 0 && av[i + 1])
	env->map.height = atoi(av[i + 1]);
      else if (strcmp(av[i], "-n") == 0 && av[i + 1])
	{
	  if (init_team(av, env, i) == -1)
	    return (-1);
	}
      else if (strcmp(av[i], "-c") == 0 && av[i + 1])
	env->max_nb_team = atoi(av[i + 1]);
      else if (strcmp(av[i], "-t") == 0 && av[i + 1])
	env->time = atoi(av[i + 1]);
      i++;
    }
  return ((ac > 3 &&  check_arg(env)) ? 0 : -1);
}
