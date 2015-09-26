/*
** argument.c for arg in /home/lauret_s/rendu/PSU_2014_zappy/Server
**
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
**
** Started on  Sun Jul  5 15:38:28 2015 Sebastien Lauret
** Last update Sun Jul  5 16:03:13 2015 Bastos-Fix
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header/env.h"

int	error_arg()
{
  printf("An Error occurred when checking arguments: Missing TEAM\n");
  printf("Usage: ./server [[-p [port] -x [width] -y [height]]] ");
  printf("-n [teams names, ..] [[-c [max teammates] -t [actions time]]]\n");
  return (1);
}

int	check_arg(t_env *env)
{
  return (env->port > 0 && env->map.width > 5
	  && env->map.height > 5 && env->max_nb_team >= 1
	  && env->time > 0 && env->nb_team > 1);
}
