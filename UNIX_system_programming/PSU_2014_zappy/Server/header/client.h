/*
** client.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src/header
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:17:20 2015 Younes Iddahamou
** Last update Sun Jul  5 19:06:20 2015 Younes Iddahamou
*/

#ifndef CLIENT_H_
# define CLIENT_H_

enum	e_inv
  {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    JOUEUR
  };

enum	e_dir
  {
    RIGHT,
    UP,
    LEFT,
    DOWN
  };

# define DEFAULT_FOOD	10
# define DEFAULT_LVL	1

typedef struct	s_coor
{
  int		y;
  int		x;
}		t_coor;

typedef	struct	s_player
{
  int		id;
  int		lvl;
  t_coor	coor;
  enum e_dir	dir;
  int		inventaire[7];
}		t_player;

# define FD_FREE	NULL

enum e_role
  {
    AUCUN,
    IA,
    GRAPHIQUE,
    EGG
  };

typedef struct	s_client
{
  int			fd;
  t_player		player;
  char			*output;
  enum e_role		role;
  int			team;
  int			egg;
  int			id_egg;
  int			graphic_init;
  int			root;
  struct s_client	*next;
  struct s_client	*prev;
}		t_client;

#endif /*CLIENT_H_*/
