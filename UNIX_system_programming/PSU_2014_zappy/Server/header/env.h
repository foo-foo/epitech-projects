/*
** env.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src/header
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:26:17 2015 Younes Iddahamou
** Last update Sun Jul  5 19:06:34 2015 Younes Iddahamou
*/

#ifndef ENV_H_
# define ENV_H_

# include "map.h"
# include "client.h"
# include "action.h"
# include "../../Sockets/sockets.h"

# define MAX_FD	QPORT_LEN + 3

typedef struct	s_team
{
  char		*name;
  int		max;
  t_client	clients;
}		t_team;

typedef struct	s_env
{
  int		fd_server;
  int		port;
  t_map		map;
  int		time;
  int		max_nb_team;
  int		nb_team;
  t_team	*teams;
  t_client	**clients;
  t_client	*graph_client;
  t_action	action;
  char		**msg_action;
  char		**stone_name;
}		t_env;


#endif /* ENV_H_ */
