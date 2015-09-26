/*
** server.h for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 12 12:56:10 2015 Anatole Menichetti
** Last update Sat Mar 28 18:47:49 2015 Anatole Menichetti
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdio.h>
# include <dirent.h>

# define NBR_CMD	(16)
# define CHILD		(0)

/*
** Configuration
*/
# define DEFAULT_PROMPT	"Anonymous ~> \n"
# define PWD_CONTAINER	"/.pwd"
# define USER_DIRECTORY	"/Users"
# define EOP		" ~> \n"

/*
** RFC959 codes
*/
# define CMDOK		\
  "200 Command okay.\r\n"
# define FSTATOK	\
  "150 File status okay; about to open data connection.\r\n"
# define FSUCCESS	\
  "226 Closing data connection. \
Requested file action successful.\r\n"
# define NEEDPWD	\
  "331 User name okay, need password.\r\n"
# define NEEDACCOUNT	\
  "332 Need account for login.\r\n"
# define LOGGEDIN	\
  "230 User logged in, proceed.\r\n"

typedef struct	dirent	t_dir;

typedef struct	s_cmd
{
  char		*name;
  char		*(*fptr)(int, FILE *, char *, char **);
}		t_cmd;


/*
**		Process
*/
int		handle_clients(int, char **);

int		handle_cmd(int, FILE *, char *, char **);

char		*get_conf(char *, char *);

/*
**		Commands
*/
char		*my_ls(int, FILE *, char *, char **);

char		*get_scan_path(t_dir ***, int, char *, int *);

char		*my_pwd(int, FILE *, char *, char **);

char		*my_cd(int, FILE *, char *, char **);

char		*my_user(int, FILE *, char *, char **);

char		*connect_user(int, FILE *, char *, char *);

char		*my_put(int, FILE *, char *, char **);

char		*put_transfert(int [2], FILE *, char *, size_t);

char		*my_get(int, FILE *, char *, char **);

char		*my_mkd(int, FILE *, char *, char **);

char		*my_noop(int, FILE *, char *, char **);

char		*my_appe(int, FILE *, char *, char **);

char		*my_stou(int, FILE *, char *, char **);

char		*my_acct(int, FILE *, char *, char **);

char		*my_nls(int, FILE *, char *, char **);

char		*my_rnfr(int, FILE *, char *, char **);

char		*my_rnto(int, FILE *, char *, char **);

char		*my_dele(int, FILE *, char *, char **);

char		*my_rmd(int, FILE *, char *, char **);

#endif /* !SERVER_H_ */
