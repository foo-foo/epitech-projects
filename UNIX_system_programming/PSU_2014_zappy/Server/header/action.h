/*
** action.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/Server/header
** 
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
** 
** Started on  Sun Jul  5 19:06:04 2015 Younes Iddahamou
** Last update Sun Jul  5 19:06:09 2015 Younes Iddahamou
*/

#ifndef ACTION_H_
# define ACTION_H_

# include <time.h>
# include "client.h"

typedef struct		s_action
{
  time_t		time;
  int			action;
  int			id_client;
  t_client		*client;
  char			**input;
  void			*fptr_action;
  int			root;
  struct s_action	*first;
  struct s_action	*next;
  struct s_action	*prev;
}			t_action;

int	create_action(t_action *action, char **input, t_client *client, int id_action);
void	delete_action(t_action *action);
void	delete_action_by_id(t_action *action, int id);

#endif /* ACTION_H_ */
