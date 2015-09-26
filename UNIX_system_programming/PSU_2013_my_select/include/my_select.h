/*
** my_select.h for my_select in /home/menich_a/rendu/PSU_2013_my_select
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan 10 12:56:15 2014 menich_a
** Last update Sun Jan 19 19:25:16 2014 menich_a
*/

#ifndef MY_SELECT_H_
# define MY_SELECT_H_
# define BUFF_SIZE	(3)
# define ESC		(27)
# define SPACE		(32)
# define DELETE		(127)
# define BACKSPACE	(8)

#include "list.h"

typedef struct termios	t_termios;

typedef struct winsize	t_winsize;

typedef struct	s_size
{
  int		height;
  int		width;
  int		pos;
  t_list	*list;
}		t_size;

int	g_fd;

/*
**	Init functions.
*/
void	reinit_then_exit(t_termios, char *, int);

int	reinit_termios(t_termios *);

int	init_termios(t_termios *);

/*
**	Usefull functions.
*/
int	dynamic_research_mode(t_list *, char *, int);

void	display_search_bar(t_size *, t_list *);

int	my_select(t_termios, t_list *, int);

int	msg_error(char *, int);

int	check_env(char **);

/*
**	Termcaps functions.
*/
void	my_putstr_underline(char *);

void	disable_reverse_video(void);

void	enable_reverse_video(void);

void	restore_cursor_pos(void);

void	save_cursor_pos(void);

void	move_cursor(int, int);

void	my_clear_screen(void);

void	display_cursor(void);

void	remove_cursor(void);

int	display(int);

/*
**	Keypressed functions.
*/
int	delete_elem(t_termios, t_list *, int, int);

int	display_list(t_list *, int, t_size *);

int	select_elem(t_list *, int);

/*
**	Signal functions.
*/
void	my_ignore_signal(int);

void	my_kill(int);

#endif	/* !MY_SELECT_H_ */
