/*
** my.h for libmy in /home/menich_a/rendu/Piscine-C-include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Oct 10 16:46:02 2013 menich_a
** Last update Sun Jun  1 12:22:02 2014 menich_a
*/

#ifndef MY_H_
# define MY_H_

int	check_if_color_cmd(char **);

int	get_open_bracket(char *, int);

int	get_close_bracket(char *, int, int);

void	jump_some_spaces(char *, int *, int *, int);

int	check_error(int [2]);

int	get_file_size(int);

int	hidenp(char *, char *);

char	**my_str_to_wordtab(char *);

char	*msg_error_ret(char *);

int	my_warn(char *, int);

int	validity_check(char **, int, int);

char	**my_warn_ret(char *);

int	get_fd(int, int, int);

char	*my_free(char *);

int	my_remove(char **, char *);

int	my_char_is_alphanum(char, int);

int	get_citation_size(char *, int);

int	get_citation(char *, char *, int);

int	get_next_word(char *, char *, int);

int	jump_backslash(char *, int, char);

char	**get_history(void);

void	jump_inhibitors(char *, int *);

void	jump_inhibitors_cpy(char *, char *, int *, int *);

char	*my_nbr_to_str(int);

char	*my_xstrndup(char *, int);

char	**my_tabdup(char **);

int	my_find_in_tab(char **, char);

char	*my_strcatdup(char *, char *);

char	*get_word(char *, int);

char	**add_one_choice(char **, char *, int);

char	*my_str_catdup(char *, char *);

int	my_word_iscmd(char *, int);

char	**get_path(char **);

int	my_nbrlen(int);

char	*get_history_path(char **);

int	find_delimitor(char *);

int	my_check_syntax(char *, char **);

char	*my_remove_spaces(char *);

int     my_perror(char *, int);

int	my_str_isprintable(char *);

char	*my_find_in_env(char **, char *);

int	my_find_in_str(char *, char);

char	**buff_to_cmdtab(char *, char **);

char	**my_path_to_tab(char *);

char	**my_free_tab(char **);

void	my_putchar(char);

int	my_put_nbr(int);

void	my_putstr(char*);

int	my_strlen(char*);

int	my_strcmp(char*, char*);

int	my_strncmp(char *, char *, int);

char	*my_strcat(char*, char*);

char	*my_strcpy(char*, char*);

void	msg_error_exit(char *);

char	**msg_error_return(char *, char **);

char	*my_strdup(char *);

char	*my_strndup(char *, int);

int	my_getnbr(char *);

int	my_tablen(char **);

char	**my_tabcpy(char **, char **);

int	msg_error(char *);

#endif	/* !MY_H_ */
