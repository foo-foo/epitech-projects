/*
** get_next_line.h for get_next_line in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed Apr 30 17:39:43 2014 menich_a
** Last update Thu May 29 17:23:48 2014 menich_a
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUFF_SIZE	(4096)

typedef struct	s_line
{
  char		key[BUFF_SIZE];
  char		*line;
  char		*save;
  int		history_index;
  int		size;
  int		i;
}		t_line;

char		*tc_get_next_line(int, char **);

int		ctrl_y_key(t_line *, char *);

void		ctrl_l_key(t_line *);

char		*ctrl_w_key(t_line *, char *, int, int);

int		check_before_display(char **);

char		*fget_next_line(int);

int		display_prompt(char **, int, int);

char		*cut_line_from_cursor(t_line *, char *);

int		buff_is_specialkey(t_line *, int, int, char **);

int		delete_key(t_line *, int, int);

int		left_key(int, int, int);

int		right_key(int, int, int);

int		up_key(t_line *, int, int);

int		down_key(t_line *, int, int);

int		dynamic_completion(t_line *, char **);

void		treat_simple_rebinding(t_line *, int, int);

int		is_line_half_completed(t_line *, char **);

int		half_complete_line(t_line *, char **);

void		display_choice_tab(char **, t_line *);

int		complete_line(t_line *, char **);

char		**get_history(void);

int		init_termios(char **);

#endif	/* !GET_NEXT_LINE_H_ */
