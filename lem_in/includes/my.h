/*
** my.h for my in /home/menich_a/rendu/prog_elem/lem_in/includes
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr 17 12:22:17 2014 menich_a
** Last update Sat May  3 19:18:00 2014 menich_a
*/

#ifndef MY_H_
# define MY_H_

int	my_str_isprintable(char *);

int	my_tabcmp(char **, char **);

int	tab_len(char **);

char	**my_tab_dup(char **);

char	**my_free_tab(char **);

int	my_strcmp(char *, char *);

void	my_put_nbr(int);

int	msg_error(char *);

int	my_str_isnum(char *);

int	my_getnbr(char *);

char	*get_next_line(int);

char	*my_strdup(char *);

char	**my_realloc(char **);

void	my_putchar(char);

void	my_putstr(char *);

int	my_strlen(char *);

char	*my_strcatdup(char *, char *);

int	my_line_isvalid(char *);

#endif	/* MY_H_ */
