/*
** get_next_line.h for get_next_line in /home/menich_a/rendu/prog_elem/lem_in/includes
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr 17 12:22:17 2014 menich_a
** Last update Sun May  4 18:39:13 2014 menich_a
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUFF_SIZE	(4096)

int		my_strlen(char *str);

int		end_of_line(char *line);

int		msg_error(char *msg);

char            *get_next_line(int fd);

#endif	/* GET_NEXT_LINE_H_ */
