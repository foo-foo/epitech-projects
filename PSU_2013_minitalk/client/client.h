/*
** client.h for client in /home/menich_a/rendu/PSU_2013_minitalk/client/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Mar 18 19:17:27 2014 menich_a
** Last update Sat Mar 22 23:22:00 2014 menich_a
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# define SUCCESS	(0)
# define FAILURE	(-1)
# define CHECK		(42)
# define PAUSE		(1)
# define BREAK_PAUSE	(0)
# define SUSPEND	(-1)
# define PAUSE_MAX	(100000)

void	my_putstr(char *);

int	msg_error(char *);

int	my_getnbr(char *);

#endif	/* !CLIENT_H_ */
