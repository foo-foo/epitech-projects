/*
** allum1.h for allum1 in /home/menich_a/rendu/Allum1
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Feb  7 00:22:46 2014 menich_a
** Last update Sun Feb 16 21:44:36 2014 menich_a
*/

#ifndef ALLUM1_H_
# define ALLUM1_H_

/*
** Key words
*/
# define FAILURE		(-1)
# define SUCCESS		(0)
# define BUFF_SIZE		(3)
# define BROKEN_PIPE		'x'
# define BLUE_BROKEN_PIPE	"\033[34mx\033[0m"
# define RED_BROKEN_PIPE	"\033[35mx\033[0m"

/*
** Arrows names
*/
# define UP		(65)
# define DOWN		(66)
# define RIGHT		(67)
# define LEFT		(68)

/*
** Menus returned values
*/
# define EASY		(0)
# define HARD		(1)
# define ONE_PLAYER	(0)
# define MULTIPLAYER	(2)

/*
** Termcaps names
*/
# define CLEAR		"cl"
# define SAVE_CURSOR	"sc"
# define RESTORE_CURSOR	"rc"
# define WINDOW_HEIGHT	"li"
# define WINDOW_WIDTH	"co"
# define BOLD		"md"
# define ENABLE_CURSOR	"ve"
# define MOVE_LEFT	"le"
# define MOVE_RIGHT	"nd"

typedef struct termios	t_termios;

typedef struct winsize	t_winsize;

typedef struct	s_pos
{
  int		x;
  int		y;
  int		width;
  int		height;
}		t_pos;

/*
**	Key pressed functions
*/
int	check_arrows_validity(char **, char, t_pos *);

void	arrows_up_down(char **, t_pos *, char, int);

void	arrows_left_right(char **, t_pos *, char);

int	delete_key(char **, t_pos *, char, int);

/*
**	Main & utilities functions
*/
int	computer_turn(char **, int, t_pos);

int	user_turn(char **, int, t_pos, int);

void	launch_remove(char **, t_pos *, int);

int	launch_new_game(t_pos, int, int);

char	**build_tray(char **, int);

void	display_tray(int, int, int);

int	set_rows(int, int);

int	my_pipelen(char *);

int	get_next_pipe(char *, int);

/*
**	Termcaps functions
*/
void	launch_termcap(char *);

void	move_cursor(int, int);

void	my_putstr_underline(char *);

void	my_putchar_red(char);

#endif /* !ALLUM1_H_ */
