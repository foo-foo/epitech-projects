/*
** graphic.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/Server/header
** 
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
** 
** Started on  Sun Jul  5 19:07:18 2015 Younes Iddahamou
** Last update Sun Jul  5 19:07:19 2015 Younes Iddahamou
*/

#ifndef GRAPHIC_H_
# define GRAPHIC_H_

void	msz(t_env *env);
void	bct(t_env *env, int y, int x);
void	mct(t_env *env);
void	tna(t_env *env);
void	pnw(t_env *env, t_client *client);
void	ppo(t_env *env, t_client *client);
void	plv(t_env *env, t_client *client);
void	pin(t_env *env, t_client *client);
void	pex(t_env *env, t_client *client);
void	pbc(t_env *env, t_client *client, char **input);
void	pie(t_env *env, t_client *client, int res);
void	pfk(t_env *env, t_client *client);
void	pdr(t_env *env, t_client *client, int id_ressource);
void	pgt(t_env *env, t_client *client, int id_ressource);
void	pdi(t_env *env, t_client *client);
void	enw(t_env *env, t_client *client, t_client *egg);
void	eth(t_env *env, t_client *client);
void	ebo(t_env *env, t_client *client);
void	edi(t_env *env, t_client *client);
void	sgt(t_env *env);
void	sst(t_env *env, int new_time);
void	seg(t_env *env, int team);
void	smg(t_env *env, char *msg);
void	suc(t_env *env);
void	sbp(t_env *env);

void	enw_init(t_env *env, t_client *egg);
void	fptr_msz(t_env *env, t_action *action);
void	fptr_bct(t_env *env, t_action *action);
void	fptr_mct(t_env *env, t_action *action);
void	fptr_tna(t_env *env, t_action *action);
void	fptr_ppo(t_env *env, t_action *action);
void	fptr_plv(t_env *env, t_action *action);
void	fptr_pin(t_env *env, t_action *action);
void	fptr_sgt(t_env *env, t_action *action);
void	fptr_sst(t_env *env, t_action *action);

#endif /* GRAPHIC_H_ */
