/*
** sockets.h for sockets in /home/rosain_f/projects/myFTP/tp/test/v2
** 
** Made by Francois Rosain
** Login   <rosain_f@epitech.net>
** 
** Started on  Tue Mar 10 15:19:41 2015 Francois Rosain
** Last update Tue Apr  7 13:23:40 2015 Francois Rosain
*/

#ifndef _SOCKETS_H_
# define _SOCKETS_H_

# define QPORT_LEN	255

int	create_socket(int *fd);
int	destroy_socket(int fd);

#endif /* !_SOCKETS_H_ */
