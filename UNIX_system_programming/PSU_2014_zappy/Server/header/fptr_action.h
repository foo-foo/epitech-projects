/*
** fptr_action.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src/header
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Thu Jun 18 15:25:12 2015 Younes Iddahamou
** Last update Sun Jul  5 19:07:01 2015 Younes Iddahamou
*/

#ifndef FPTR_ACTION_H_
# define FPTR_ACTION_H_

# include "env.h"

# define NB_ACTION	21
# define INIT_PLAY	NB_ACTION
# define DEATH		NB_ACTION + 1
# define ECLOSE		NB_ACTION + 2
# define DELETE_PLAYER	NB_ACTION + 3
# define INCANTATION	NB_ACTION + 4
# define FORK		NB_ACTION + 5
# define INIT_GRAPH	NB_ACTION + 6
# define REGENE		NB_ACTION + 7

# define ABS(a) ((a < 0)? -a : a)
# define MIN(a,b) ((ABS(a) < ABS(b))? a : b)

typedef	void	(*f_action)(t_env *env, t_action *);

void	droite(t_env *env, t_action *action);
void	gauche(t_env *env, t_action *action);
void	avance(t_env *env, t_action *action);
void	pose(t_env *env, t_action *action);
void	prend(t_env *env, t_action *action);
void	inventaire(t_env *env, t_action *action);
void	expulse(t_env *env, t_action *action);
void	player_death(t_env *env, t_action *action);
void	new_player(t_env *env, t_action *action);
void	send_graph_fork(t_env *env, t_action *action);
void	voir(t_env *env, t_action *action);
void	check_incantation(t_env *env, t_action *action);
void	incantation(t_env *env, t_action *action);
void	broadcast(t_env *env, t_action *action);
char	*itoa(int);
int	add_output(t_client *client, char *str);
int	nb_client(t_team *team);
void	init_player(t_env *env, t_action *action);
void	init_graphique(t_env *env, t_action *action);
t_client	*alloc_client(t_env *env,char *msg);
int	nb_client(t_team *team);
void	init_var_player(t_env *env, t_client *client, int team);
void	init_player(t_env *env, t_action *action);
void	eclose(t_env *env, t_action *action);
void	delete_player(t_env *env, t_action *action);
void	send_graph_check(t_env *, t_client **clients, t_client *caster);
void	send_graph_incant(t_env *, t_client *caster, int fail, t_map *map);
void	add_output_incantation(t_client **clients, t_client *caster, char *str);
int	free_slot(t_env *env, int team);
void	nb_connect(t_env *env, t_action *action);
void	regen_food(t_env *env, t_action *action);
t_client	*find_by_id(t_env *env, int id);
void	pin_msg(t_env *env, t_client *client);

#endif /*FPTR_ACTION_H_*/
