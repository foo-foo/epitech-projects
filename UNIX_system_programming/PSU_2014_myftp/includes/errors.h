/*
** errors.h for errors in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:24:13 2015 Anatole Menichetti
** Last update Sat Mar 28 18:59:35 2015 Anatole Menichetti
*/

#ifndef ERRORS_H_
# define ERRORS_H_

# include <stdio.h>

/*
** RFC959 error codes
*/
# define ESYNTAX	\
  "501 Syntax error in parameters or arguments.\r\n"
# define ENOTTAKEN	\
  "550 Requested action not taken.\r\n"
# define EFNOTTAKEN	\
  "553 Requested action not taken. File name not allowed.\r\n"
# define EBADSEQ	\
  "503 Bad sequence of commands.\r\n"
# define ENOTIMP	\
  "502 Command not inplemented.\r\n"
# define EARGNOTIMP	\
  "504 Command not inplemented for that parameter.\r\n"
# define EPTYPE		\
  "551 Requested action aborted: page type unknown.\r\n"
# define ESTORAGE	\
  "551 Requested file action aborted. \
exceeded storage allocation.\r\n"
# define ERALLOC	\
  "452 Requested action not taken. \
Insufficient storage space in system.\r\n"
# define EABORTED	\
  "426 Connection close; transfert aborted.\r\n"

/*
** Server error messages
*/
# define ESCLOSE	\
  "myftp: server: server closure failed"
# define ECCLOSE	\
  "myftp: server: client closure failed"
# define ESCANDIR	\
  "myftp: server: current directory scan (ls) failed"
# define EALLOC		\
  "myftp: server: memory allocation failed"
# define EWRITE		\
  "myftp: server: failure by writting to client"
# define ERCV		\
  "myftp: server: failure by receiving client msg"
# define EOPEN		\
  "myftp: server: failure by opening client"
# define EACCEPT	\
  "myftp: server: failure by accepting client"
# define EFORK		\
  "myftp: server: fork failed"
# define EUSAGE		\
  "myftp: server: usage: server [LISTENING PORT].\n"
# define EBIND		\
  "myftp: server: binding socket failed"
# define ELISTEN	\
  "myftp: server: failure by listening clients"
# define ENOTFOUND	\
  "myftp: server: cannot found PWD environnement variable.\n"
# define EACCESS	\
  "myftp: server: access to user directory failed"

/*
** errors.c
*/
int	my_perror(char *, int, int, int);

void	*my_perror_gen(char *, void *, int, int);

char	*alloc_err(int, int, FILE *, int);

char	*my_rerror(char *, int, int, FILE *);

#endif /* !ERRORS_H_ */
