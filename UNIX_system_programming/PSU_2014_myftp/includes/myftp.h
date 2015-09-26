/*
** myftp.h for myftp in /home/menich_a/rendu/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Mar 12 11:47:51 2015 Anatole Menichetti
** Last update Sat Mar 28 18:51:37 2015 Anatole Menichetti
*/

#ifndef MYFTP_H_
# define MYFTP_H_

# define PROTONAME	"TCP"

/*
** Return values
*/
# define SUCCESS	(1)
# define FAILURE	(0)

/*
** PWDS
*/
# define HOME           (0)
# define ROOT           (1)
# define CURRENT        (2)
# define OLD            (3)

/*
** Error messages
*/
# define ETCP			\
  "myftp: failure by getting the TCP protocol"
# define ESOCKET		\
  "myftp: socket creation failed"
# define ESIGNAL		\
  "myftp: signal reception failed"

typedef struct dirent		t_dir;
typedef struct protoent		t_proto;
typedef struct sockaddr_in	t_sockin;

/*
** get_pwd.c
*/
void				free_pwds(char **);

char				**get_pwd(char *, char *);

#endif /* !MYFTP_H_ */
