/*
** myirc.h for my_irc in /home/menich_a/rendu/PSU_2014_myirc/includes
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 16:06:59 2015 Anatole Menichetti
** Last update Sat Apr 11 13:59:47 2015 Anatole Menichetti
*/

#ifndef MYIRC_H_
# define MYIRC_H_

# include <sys/socket.h>

# define PROTONAME	"TCP"
# define BUFF_SIZE	512

/*
**	Typedefs
*/
typedef struct protoent		t_proto;

typedef struct sockaddr_in	t_sin;

typedef socklen_t		t_slen;

typedef struct timeval		t_tv;

/*
**	errors.c
*/
int	msg_error(char *, int);

/*
**	put.c
*/
void	putstr(char *);

int	fputstr(int, char *);

/*
**	tab.c
*/
void	free_tab(char **);

int	tablen(char **);

char	**str_to_cmdtab(char *);

/*
**	circular_read.c
*/
int	circular_read(int, char [BUFF_SIZE + 1]);

#endif /* !MYIRC_H_ */
