/*
** my_termios.h for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue May  6 16:07:39 2014 menich_a
** Last update Wed May 21 16:54:09 2014 menich_a
*/

#ifndef MY_TERMIOS_H_
# define MY_TERMIOS_H_

#include <termios.h>

/*
**	Keys
*/
# define DELETE_KEY	(127)
# define ESCAPE_KEY	(27)
# define UP_KEY		(65)
# define DOWN_KEY	(66)
# define RIGHT_KEY	(67)
# define LEFT_KEY	(68)

/*
** Termcaps names
*/
# define CLEAR          "cl"
# define SAVE_CURSOR    "sc"
# define RESTORE_CURSOR "rc"
# define WINDOW_HEIGHT  "li"
# define WINDOW_WIDTH   "co"
# define BOLD           "md"
# define ENABLE_CURSOR  "ve"
# define ENABLE_INSERT  "im"
# define MOVE_LEFT      "le"
# define MOVE_RIGHT     "nd"
# define MOVE_UP	"up"
# define MOVE_DOWN	"do"
# define DEL_FROM_CURS	"cd"

typedef struct termios	t_termios;

void	launch_termcap(char *);

#endif /* !MY_TERMIOS_H_ */
