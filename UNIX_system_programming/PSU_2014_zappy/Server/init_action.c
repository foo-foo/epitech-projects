/*
** init_action.c for init action in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:39:33 2015 Sebastien Lauret
** Last update Sun Jul  5 15:39:34 2015 Sebastien Lauret
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header/env.h"
#include "header/action.h"
#include "header/graphic.h"
#include "header/fptr_action.h"

int	init_action_msg(t_env *env)
{
  if ((env->msg_action = malloc(sizeof(char*) * (NB_ACTION + 1))) == NULL
      || (env->msg_action[0] = strdup("droite")) == NULL
      || (env->msg_action[1] = strdup("gauche")) == NULL
      || (env->msg_action[2] = strdup("avance")) == NULL
      || (env->msg_action[3] = strdup("inventaire")) == NULL
      || (env->msg_action[4] = strdup("pose")) == NULL
      || (env->msg_action[5] = strdup("prend")) == NULL
      || (env->msg_action[6] = strdup("expulse")) == NULL
      || (env->msg_action[7] = strdup("fork")) == NULL
      || (env->msg_action[8] = strdup("voir")) == NULL
      || (env->msg_action[9] = strdup("broadcast")) == NULL
      || (env->msg_action[10] = strdup("incantation")) == NULL
      || (env->msg_action[11] = strdup("connect_nbr")) == NULL
      || (env->msg_action[12] = strdup("msz")) == NULL
      || (env->msg_action[13] = strdup("bct")) == NULL
      || (env->msg_action[14] = strdup("mct")) == NULL
      || (env->msg_action[15] = strdup("tna")) == NULL
      || (env->msg_action[16] = strdup("ppo")) == NULL
      || (env->msg_action[17] = strdup("plv")) == NULL
      || (env->msg_action[18] = strdup("pin")) == NULL
      || (env->msg_action[19] = strdup("sgt")) == NULL
      || (env->msg_action[20] = strdup("sst")) == NULL)
    return (-1);
  env->msg_action[NB_ACTION] = NULL;
  return (0);
}

int	init_action_player_fptr(f_action  **fptr_action)
{
  (*fptr_action)[0] = &droite;
  (*fptr_action)[1] = &gauche;
  (*fptr_action)[2] = &avance;
  (*fptr_action)[3] = &inventaire;
  (*fptr_action)[4] = &pose;
  (*fptr_action)[5] = &prend;
  (*fptr_action)[6] = &expulse;
  (*fptr_action)[7] = &send_graph_fork;
  (*fptr_action)[8] = &voir;
  (*fptr_action)[9] = &broadcast;
  (*fptr_action)[10] = &check_incantation;
  (*fptr_action)[11] = &nb_connect;
  return (0);
}

int	init_action_graphic_fptr(f_action  **fptr_action)
{
  (*fptr_action)[12] = &fptr_msz;
  (*fptr_action)[13] = &fptr_bct;
  (*fptr_action)[14] = &fptr_mct;
  (*fptr_action)[15] = &fptr_tna;
  (*fptr_action)[16] = &fptr_ppo;
  (*fptr_action)[17] = &fptr_plv;
  (*fptr_action)[18] = &fptr_pin;
  (*fptr_action)[19] = &fptr_sgt;
  (*fptr_action)[20] = &fptr_sst;
  return (0);
}

int	init_action_fptr(f_action  **fptr_action)
{
  if ((*fptr_action = malloc(sizeof(f_action*) * (NB_ACTION + 8))) == NULL)
    return (-1);
  init_action_graphic_fptr(fptr_action);
  init_action_player_fptr(fptr_action);
  (*fptr_action)[INIT_GRAPH] = &init_graphique;
  (*fptr_action)[INIT_PLAY] = &init_player;
  (*fptr_action)[DEATH] = &player_death;
  (*fptr_action)[ECLOSE] = &eclose;
  (*fptr_action)[DELETE_PLAYER] = &delete_player;
  (*fptr_action)[INCANTATION] = &incantation;
  (*fptr_action)[FORK] = &new_player;
  (*fptr_action)[REGENE] = &regen_food;
  return (0);
}

int	init_action(t_env *env, f_action  **fptr_action)
{
  env->action.root = 1;
  env->action.first = &env->action;
  env->action.next = &env->action;
  env->action.prev = &env->action;
  if (init_action_fptr(fptr_action) == -1
      || init_action_msg(env) == -1)
    return (-1);
  return (0);
}
