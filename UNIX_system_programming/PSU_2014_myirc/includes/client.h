/*
** client.h for my_irc in /home/menich_a/rendu/PSU_2014_myirc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Apr  7 16:49:10 2015 Anatole Menichetti
** Last update Sun Apr 12 12:23:56 2015 Anatole Menichetti
*/

#ifndef CLIENT_H_
# define CLIENT_H_

/*
**	Error messages
*/
# define EUSAGE		\
  "client: usage: client [] | client [IP ADDRESS] [PORT]\n"
# define EPROTONAME	\
  "client: getting protocol name error"
# define ESOCKET	\
  "client: socket error"
# define ECONNECT	\
  "402 :No such server"
# define EREAD		\
  "client: read error"
# define EWRITE		\
  "client: write error"
# define ESELECT	\
  "client: selection errror"
# define ECLOSE		\
  "client: close error"
# define EALLOC		\
  "client: memory allocation error"
# define ELOST		\
  "\033[31mclient: lost connection with server: aborting.\033[0m\n"
# define ENOTCONNECTED	\
  "Please connect to a server before using any IRC command.\n"

/*
**	client.c
*/
int	launch_client(int);

/*
**	handle_connection.c
*/
int	handle_connection(char *);

int	connect_to_server(const char *, int);

int	process_server_cmd(char *, int *, int);

/*
**	handle_stdin.c
*/
int	handle_stdin(int *, int *);

/*
**	prefix.c
*/
char	*clear_prefix(char *, int);

/*
**	err_serv.c
*/
char    *err_serv(char *, char *, char *, char *);

#endif /* !CLIENT_H_ */
