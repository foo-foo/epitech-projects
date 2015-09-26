/*
** client.h for  in /home/menich_a/rendu/zappy/client_zappy
**
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
**
** Started on  Sun Jun 14 23:44:10 2015 Anatole Menichetti
** Last update Sun Jul  5 16:05:49 2015 Bastos-Fix
*/

#ifndef CLIENT_H_
# define CLIENT_H_

/*
**	Player
*/
# define DEFAULT_LVL		(1)

# define MIN_FOOD		(8)

# define MAX_FOOD		(100)

# define NBR_ACTIONS		(5)

# define NBR_WR_ACTIONS		(9)

# define NBR_OBJS		(7)

# define UPDATE_STUFF_TIME	(5)

# define WAIT_BEFORE_BROADCAST	(10)

# define NB_MAX_WITHOUT_RECRUIT	(20)

# define WAIT_MAX		(10)

/*
**	Rise requirements
*/
# define FIND_PEOPLE	(2)

# define WAIT_PEOPLE	(3)

# define CALL_PEOPLE	(4)

/*
**	Broadcasts types
*/
# define NEED_PEOPLE	(3)

# define CAN_I_JOIN	(2)

# define U_CAN_JOIN	(4)

# define CALL		(1)

/*
**	Broadcasts parts
*/
# define DIR		(0)

# define TYPE		(1)

# define TEAM		(2)

# define PID		(3)

# define LVL		(4)

# define EXTERN_PID	(5)

/*
**	Broadcasts settings
*/
# define BROADCAST_FREQ	(25)

# define BROADCAST_TURN	(4)

/*
**	Priorities
*/
# define MIN_PRIORITY		(5)

# define FOOD_PRIORITY		(5)

# define STONE_PRIORITY		(2)

# define PLAYER_PRIORITY	(42)

typedef enum	e_obj
  {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    PLAYER
  }		e_obj;

typedef enum	e_dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  }		e_dir;

typedef enum	e_action
  {
    LOOK,
    STUFF,
    MOVE,
    TURN_LEFT,
    TURN_RIGHT,
    FORK,
    ELEVATION,
    EXPULSION,
    BROADCAST,
    PUT = 10
  }		e_action;

typedef struct	s_player
{
  char		*team_name;
  size_t	lvl;
  e_action	last_move;
  int		look_for_target;
  int		target_dir;
  pid_t		target_pid;
  int		people_needed;
  size_t	look_around;
  int		waiting_answer;
  int		waiting_time;
  int		preparing_to_rise;
  int		wait_before_broadcast;
  int		nbr_broadcasts;
  int		nbr_broadcast_emitted;
  int		need_to_kick;
  size_t	rising;
  size_t	stuff[7];
  char		*objects[8];
  int		need_to_look_stuff;
  int		need_to_broadcast;
  int		broadcasts[10][6];
  size_t	requirements[7][7];
  short		actions[10];
  pid_t		pid;
}		t_player;

typedef struct	s_action
{
  char		*name;
  char		*ret[2];
  int		(*fptr)(t_player *, char *);
}		t_action;

typedef struct	s_view
{
  char		***vision;
  int		**priorities;
}		t_view;

/*
**	Typedefs
*/
typedef struct protoent		t_proto;

typedef struct sockaddr_in	t_sin;

typedef socklen_t		t_slen;

typedef struct timeval		t_tv;

/*
**	Core
*/
# define PROTONAME	"TCP"

# define LOCALHOST	"127.0.0.1"

# define BUFF_SIZE	(3)

/*
**	Indexs
*/
# define PEOPLE		(0)

# define X		(0)

# define Y		(1)

# define I		(2)

# define J		(3)

# define D		(4)

# define ACTIONS	(2)

# define PRIORITY	(3)

/*
**	Options
*/
# define TEAM_NAME	(0)

# define PORT		(1)

# define SERVER_ADDR	(2)

/*
**	Server size
*/
# define WIDTH	(0)

# define HEIGHT	(1)

/*
**	Error messages
*/
# define EUSAGE			\
  "usage: client [-n] [team number] [-p] [port] [-h] [server addr]"

# define UNKNOWN_OPTION		\
  "unknown option "

# define UNDEFINED_OPTION	\
  "undefined option "

# define REDEFINED_OPTION	\
  "redefined option "

# define WRONG_SYNTAX_OPTION	\
  "invalid syntax for option "

# define EPROTONAME		\
  "getting protocol name error"

# define ESOCKET		\
  "socket error"

# define ECONNECT		\
  "cannot join server"

# define EREAD			\
  "read error"

# define EWRITE			\
  "write error"

# define ESELECT		\
  "selection errror"

# define ECLOSE			\
  "close error"

# define EALLOC			\
  "memory allocation error"

# define ELOST			\
  "lost connection with server: aborting"

/*
**	client.c
*/
int	launch_client(int const, char *);

/*
**	init_player.c
*/
int	init_player(int const, t_player *, int const);

/*
**	contact_server.c
*/
int	contact_server(int const, char *, size_t [2], int *);

/*
**	execute_action.c
*/
int	execute_action(int const, t_player *, char *);

/*
**	broadcast.c
*/
void	kick_if_needed(t_player *p);
int	broadcast_if_needed(int const, t_player *);

/*
**	actions.c
*/
int	stuff(t_player *, char *);

int	turn_left(t_player *, char *);

int	turn_right(t_player *, char *);

int	do_nothing(t_player *, char *);

/*
**	look.c
*/
int	look(t_player *, char *);

int	get_best_way_to_survive(t_view *, int [10][2], int [3]);

/*
**	get_vision.c
*/
char	***get_vision(t_player *, char *);

/*
**	get_vision_priorities.c
*/
int	**get_vision_priorities(char ***, int const);

/*
**	visited_squares.c
*/
void	init_visited_squares(int [10][2]);

void	copy_visited_squares(int [10][2], int [10][2]);

void	get_visited_squares_actions(t_player *, char ***, int [10][2], short [10]);

/*
**	rise.c
*/
void	rise(t_player *, char *);

int	can_i_rise(t_player *, char *, int, int, size_t);

int	get_best_way_to_rise(t_player *, char ***);

int	wait_people(t_player *);

/*
**	clear_vision.c
*/
void	remove_stones(char ***);

int	remove_stones_excess(t_player *, char ***);

/*
**	extern_actions.c
*/
int	received_msg(t_player *, char *);

void	prepare_answer(t_player *, int, int, int);

int	elevation_ended(t_player *, char *);

int	have_been_expulsed(t_player *, char *);

/*
**	tab.c
*/
int	tablen(char ***);

int	free_tab(char ***);

int	free_int_tab(int **);

/*
**	str.c
*/
int	putstr(char *);

int	fputstr(int const, char *);

int	str_is_num(char *);

int	str_is_float(char *);

char	*nbr_to_str(int);

/*
**	get_next_line.c
*/
char	*get_next_line(int);

/*
**	errors.c
*/
int	msg_error(char *, char *, int const);

#endif /* !CLIENT_H_ */
