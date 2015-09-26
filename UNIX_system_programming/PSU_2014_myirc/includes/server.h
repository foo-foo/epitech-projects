/*
** server.h for my_irc in /home/menich_a/rendu/PSU_2014_myirc/includes
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 14:14:15 2015 Anatole Menichetti
** Last update Sat Apr 11 13:59:12 2015 Anatole Menichetti
*/

#ifndef SERVER_H_
# define SERVER_H_

# define NBR_CMDS	(7)

/*
**	Files descriptors states
*/
# define ACTIVE		(1)
# define DOWN		(0)

/*
**	Files descriptors types.
*/
# define FD_FREE	(0)
# define FD_CLIENT	(1)
# define FD_SERVER	(2)

/*
**	Error messages.
*/
# define EUSAGE		\
  "server: usage: server [PORT]\n"
# define EALLOC		\
  "server: memory allocation error"
# define ECLOSE		\
  "server: close error"
# define EWRITE		\
  "server: write error"
# define EACCEPT	\
  "server: accept error"
# define EPROTONAME	\
  "server: getting protocol name errror"
# define ESOCKET	\
  "server: socket error"
# define EBINDING	\
  "server: bind error"
# define ELISTEN	\
  "server: listen error"
# define ESIGNAL	\
  "server: signal error"
# define ESELECT	\
  "server: select error"
# define ESIGINT	\
  "\nserver: received SIGINT: aborting.\n"

/*
**	File descriptor linked list.
*/
typedef struct	s_fd
{
  int		fd;
  char		type;
  char		state;
  char		*nick;
  char		**channels;
  int		(*handler_fptr)(struct s_fd *, struct s_fd *);
  struct s_fd	*next;
}		t_fd;

typedef	int	(*handler_fptr)(t_fd *, t_fd *);

/*
**	Command function pointer tab.
*/
typedef struct	s_cmd
{
  char		*name;
  char		*(*cmd)(t_fd *, t_fd *, char **);
}		t_cmd;

/*
**	handler.c
*/
int	handle_server(t_fd *, t_fd *);

int	handle_selection(t_fd *, fd_set *);

/*
**	fd_list.c
*/
int	push_fd(t_fd **, int, int, handler_fptr);

int	pop_fd(t_fd **, t_fd *);

/*
**	nickname.c
*/
char	*my_nickname(t_fd *, t_fd *, char **);

/*
**	channels.c
*/
char	*my_list(t_fd *, t_fd *, char **);

char	*my_join(t_fd *, t_fd *, char **);

char	*my_part(t_fd *, t_fd *, char **);

/*
**	check_channel_name.c
*/
int	check_channel_name(char *);

/*
**	messages.c
*/
char	*my_msg(t_fd *, t_fd *, char **);

/*
**	quit.c
*/
char	*my_quit(t_fd *, t_fd *, char **);

/*
**	err_serv.c
*/
char	*err_serv(char *, char *, char *, char *);

/*
**	dest_tab.c
*/
char	**dest_tab(char *);

/*
**	names.c
*/
char	*my_names(t_fd *, t_fd *, char **);

/*
**	char_check.c
*/
int	char_is_num(char);

int	char_is_alpha(char);

int	char_is_spe(char);

#endif /* !SERVER_H_ */
