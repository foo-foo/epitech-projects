/*
** lemipc.h for lemipc in /home/menich_a/rendu/PSU_2014_lemipc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar  3 10:57:06 2015 Anatole Menichetti
** Last update Sun Mar  8 23:01:31 2015 Anatole Menichetti
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# include <stdio.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>

/*
** Return values
*/
# define SUCCESS	(1)
# define FAILURE	(0)

/*
** IPC
*/
# define SHM		(0)
# define SEM		(1)
# define MSG		(2)

/*
** Messages types
*/
# define T_MAP		(42)
# define T_JOIN		(24)
# define T_GUI		(13)
# define T_REFRESH	(17)
# define T_DONE		(48)

/*
** Messages
*/
# define LAUNCH_MSG	\
"lemipc: a player from tead %d joined the game. \
Use launch.sh to quick launch an entire battle.\n"

# define USAGE_MSG	\
"lemipc: usage: \
./lemipc [TEAM NUMBER = 1 | 2 | 3 | 4 | 5 | 6] \
[MAP SIZE = 20] [DIRECTORY PATH = \"/\".\n"

# define M_SIZE_MSG	\
"lemipc: error: invalid argument for map size. \
Please use a number between 10 and 120.\n"

# define T_NBR_MSG	\
"lemipc: error: invalid argument for team number. \
Please use a number between 1 and 6.\n"

# define NO_PLACE_MSG	\
"lemipc: not enough place on the map to welcome player.\n"

typedef struct	s_msg
{
  long		mtype;
  char		*msg;
  int		data;
}		t_msg;

typedef struct	s_player
{
  short		pos;
  char		t_nbr;
  char		m_size;
  char		*map;
  int		ids[3];
}		t_player;

/*
**	init.c
*/
int	init_params(int, char **);

char	init_game(t_player *);

/*
**	lemipc.c
*/
int	join_game(t_player *);

/*
**	move.c
*/
int	move(char *, short, char, char);

/*
**	pos.c
*/
int	get_free_pos(char *, int, char);

int	get_target_pos(char *, short, char, char);

int	starting_block_pos(char *, char);

/*
**	map.c
*/
void	create_map(char *, char);

int	display_map(t_player *, char, char);

/*
**	ipc.c
*/
int	ipc_rm(int [3]);

int	msg_get(int [3], key_t, int);

int	send_msg(int, int, int);

int	receive_msg(int, int, int);

int	my_sem_op(int, struct sembuf *, int);

/*
**	tools.c
*/
int	my_perror(void);

int	check_params(char *, char *);

int	get_nbr_team(char *, char);

int	is_surrounded(char *, short, char, char);

#endif /* !LEMIPC_H_ */
