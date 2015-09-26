/*
** utils.c for utils in /home/lauret_s/rendu/PSU_2014_zappy/Server
** 
** Made by Sebastien Lauret
** Login   <lauret_s@epitech.net>
** 
** Started on  Sun Jul  5 15:36:03 2015 Sebastien Lauret
** Last update Sun Jul  5 15:36:05 2015 Sebastien Lauret
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header/client.h"
#include "header/map.h"

void	checkPos(t_player *player, t_map *map)
{
  if (player->coor.x < 0)
    player->coor.x = (int)map->width - 1;
  else if (player->coor.x >= (int)map->width)
    player->coor.x = 0;
  else if (player->coor.y < 0)
    player->coor.y = (int)map->height - 1;
  else if (player->coor.y >= (int)map->height)
    player->coor.y = 0;
}
