/*
** fonction.h for zappy in /home/iddaha_y/rendu/PSU_2014_zappy/server_src/header
**
** Made by Younes Iddahamou
** Login   <iddaha_y@epitech.net>
**
** Started on  Mon Jun 22 15:56:52 2015 Younes Iddahamou
** Last update Sun Jul  5 19:06:46 2015 Younes Iddahamou
*/

#ifndef FONCTION_H_
# define FONCTION_H_

# include "map.h"
# include "client.h"
# include "action.h"
# include "fptr_action.h"

int	init_env(t_env *env, int fd, f_action **fptr_action);
void	delete_env(t_env *env, f_action *fptr_action);
int	server(t_env *env, f_action *fptr_action);
int	check_fd(fd_set *, fd_set *, t_env *);
char	*get_next_line(const int fd);
char	**str_to_wordtab(char *str);
int	my_strcmp(char *, char *);
void	checkPos(t_player *, t_map *);
int	add_output(t_client *client, char *str);
int	error_arg();
int	init_args(int ac, char **av, t_env *env);
int	verif_fd();
int	check_fd_garphic(fd_set *readfds, fd_set *writefds,t_env *env);
int	check_fd(fd_set *readfds, fd_set *writefds, t_env *env);
int	check_fd_player(fd_set *readfds, fd_set *writefds,
				t_env *env, t_client *client);
void	remove_cli(t_env *env, int fd_client);
int	add_client(t_env *);
int	find_action(t_env *env, char *input, int role);
int	server_interpreter(char **input_tab, int fd_client,t_env *env);
int	check_space(char *input);
int	server_reader(fd_set *writefds,
		      int fd_client, t_env *env);
t_client	*search_egg(t_env *env, int team);
int	init_action(t_env *env, f_action  **fptr_action);
int	error_arg();
int	check_arg(t_env *env);

#endif /* FONCTION_H_ */
