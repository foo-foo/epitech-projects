/*
** client.h for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 12 15:22:28 2015 Anatole Menichetti
** Last update Sat Mar 28 18:57:36 2015 Anatole Menichetti
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdio.h>

/*
** Help messages
*/
# define HELP_MSG	\
  "\033[32mWelcome in FatchZilla.\033[0m\n\n\
Commands are:\n\n\
CWD	LCWD	LIST	LLIST\n\n\
PWD	LPWD	USER	HELP\n\n\
RETR	MRETR	STOR	MSTOR\n\n\
STOU	APPE	MKD	ACCT\n\n\
NLST	RNFR	RNTO	NOOP\n\n\
RMD	DELE\n"

# define CD_HELP	\
  "CWD		change remote working directory\n"
# define LCD_HELP	\
  "LCWD		change local working directory\n"
# define LS_HELP	\
  "LIST		list contents of remote path\n"
# define LLS_HELP	\
  "LLIST	list contents of local path\n"
# define PWD_HELP	\
  "PWD		print working directory on remote machine\n"
# define LPWD_HELP	\
  "LPWD		print local working directory\n"
# define USER_HELP	\
  "USER		send new user information\n"
# define GET_HELP	\
  "RETR		receive file\n"
# define MGET_HELP	\
  "MRETR	get multiple files\n"
# define PUT_HELP	\
  "STOR		send one file\n"
# define MPUT_HELP	\
  "MSTOR	send multiple files\n"
# define HELP_HELP	\
  "HELP		print local help information\n"
# define STOU_HELP	\
  "STOU		send one file with an unique name\n"
# define APPE_HELP	\
  "APPE		append one file\n"
# define MKD_HELP	\
  "MKD		create a directory\n"
# define ACCT_HELP	\
  "ACCT		print account information\n"
# define NLST_HELP	\
  "NLST		list file names from a directory\n"
# define RNFR_HELP	\
  "RNFR		rename a file from...\n"
# define RNTO_HELP	\
  "RNTO		rename a file to...\n"
# define NOOP_HELP	\
  "NOOP		no effective command; used for test connection\n"
# define RMD_HELP	\
  "RMD		remove a directory\n"
# define DELE_HELP	\
  "DELE		delete one file\n"

/*
** RFC959 codes
*/
# define FSTATOK	\
  "\033[36m150 File status okay; about to open data connection.\033[0m\n"
# define CMDOK          \
  "\033[36m200 Command okay.\033[0m\n"
# define FSUCCESS	\
  "\033[36m226 Closing data connection. \
Requested file action successful.\033[0m\n"

/*
** Error messages
*/
# define ECLOSE		\
  "myftp: client: closure failed"
# define ECONNECT	\
  "myftp: client: connection to server failed"
# define EOPEN		\
  "myftp: client: failure by opening server"
# define EPROMPT	\
  "myftp: client: prompt reception failed"
# define EWRITE		\
  "myftp: client: failure by writting to server"
# define EGETLINE	\
  "myftp: client: failure by receiving message"
# define EUNAVAILABLE	\
  "\033[31m421 Service not available, closing control connection.\n"
# define EUSAGE		\
  "myftp: client: usage: client [SERVER IP ADDRESS] [SERVER PORT].\n"
# define EALLOC		\
  "\033[31m452 Requested action not taken. \
Insufficient storage space in system.\033[0m\n"
# define ESYNTAX	\
  "\033[31m501 Syntax error in parameters or arguments.\033[0m\n"
# define ENOTTAKEN	\
  "\033[31m550 Requested action not taken.\033[0m\n"
# define EPTYPE		\
  "\033[31m551 Requested action aborted: page type unknown.\033[0m\n"
# define ESTORAGE	\
  "\033[31m551 Requested file action aborted. \
exceeded storage allocation.\033[0m\n"
# define EARGNOTIMP	\
  "\033[31m504 Command not inplemented for that parameter.\033[0m\n"
# define EABORTED	\
  "\033[31m426 Connection close; transfert aborted.\033[0m\n"
# define EBADSEQ	\
  "\033[31m503 Bad sequence of commands.\033[0m\n"
# define ESCANDIR	\
  "myftp: server: current directory scan (ls) failed"

typedef struct	s_cmd
{
  char		*name;
  int		(*fptr)(int, FILE *, char *, size_t);
}		t_cmd;

/*
** Process
*/
int		launch_client(int, char *, size_t, char **);

void		init_cmd_tab(t_cmd [6]);

int		is_transfert_cmd(t_cmd [6], char **);

int		handle_cmd(int, FILE *[2], char *, char **);

/*
** Commands
*/
int		my_user(int, FILE *, FILE *, size_t);

char		*my_lls(int, FILE *, char *, char **);

char		*my_lpwd(int, FILE *, char *, char **);

char		*my_lcd(int, FILE *, char *, char **);

int		my_put(int, FILE *, char *, size_t);

int		my_get(int, FILE *, char *, size_t);

int		my_mput(int, FILE *, char *, size_t);

int		my_mget(int, FILE *, char *, size_t);

char		*my_help(char *);

/*
** Tools
*/
char		*remove_ret(char *);

int		display_prompt(int, FILE *);

int		rfputstr(int, char *);

int		putcolor(char *);

void		disp_percentage(unsigned int);

/*
** Errors
*/
int		my_perror(char *, int, int, int);

int		my_perror(char *, int, int, int);

char		*alloc_err(int, FILE *, int);

char		*my_rerror(char *, int, FILE *);

#endif /* !CLIENT_H_ */
