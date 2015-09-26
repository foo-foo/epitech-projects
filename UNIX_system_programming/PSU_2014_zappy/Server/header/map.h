/*
** map.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src/header
** 
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
** 
** Started on  Thu Jun 18 15:25:33 2015 Younes Iddahamou
** Last update Sun Jul  5 16:03:40 2015 Ivan Toma
*/

#ifndef MAP_H_
# define MAP_H_

# define	REGEN_FOOD 100

typedef struct	s_map
{
  int		***map;
  size_t	height;
  size_t	width;
}		t_map;

#endif /* MAP_H_ */
