/*
** lem_in.h for lem_in in /home/menich_a/rendu/prog_elem/lem_in/includes
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr 17 12:22:17 2014 menich_a
** Last update Sat May  3 19:19:13 2014 menich_a
*/

#ifndef LEM_IN_H_
# define LEM_IN_H_

# define EMPTY		(0)
# define OCCUPED	(1)
# define ARRIVED	(1)

typedef struct	s_way
{
  char		**way;
  unsigned int	wait;
  struct s_way	*next;
}		t_way;

typedef struct	s_ant
{
  int		state;
  unsigned int	i;
  unsigned int	num;
  unsigned int	wait;
  char		**way;
  struct s_ant	*next;
}		t_ant;

typedef struct	s_pipe
{
  struct s_room	*room;
  struct s_pipe	*next;
}		t_pipe;

typedef struct	s_room
{
  int		state;
  char		*name;
  t_pipe	*pipes;
  struct s_room	*next;
}		t_room;

typedef struct	s_anthill
{
  unsigned int	ants_nbr;
  char		**save;
  char		**way;
  t_ant		*ants;
  t_way		*ways;
  t_room	*rooms;
}		t_anthill;

int		init_anthill(t_anthill *);

int		lem_in(t_anthill *);

char		**find_short_way(t_anthill *, t_room *, int);

char		*my_str_ispipe(char *, char *);

int		add_one_pipe(t_room *, t_pipe **, char *, char *);

int		add_one_room(t_room **, char *);

int		add_one_way(t_way **, char **, t_room *);

char		**save_way(t_anthill *);

void		set_rooms_state(t_room *, char **);

int		pipes_nbr(t_pipe *);

int		init_ant_list(t_anthill *);

void		remove_ants_list(t_ant *);

int		display_ant(t_ant *, char *, int);

#endif	/* LEM_IN_H_ */
