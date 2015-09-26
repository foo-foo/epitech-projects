/*
** alias.h for libmy in /home/menich_a/rendu/Piscine-C-include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Oct 10 16:46:02 2013 menich_a
** Last update Sat May 31 14:33:25 2014 menich_a
*/

#ifndef ALIAS_H_
# define ALIAS_H_

typedef struct		s_alias
{
  char			*alias;
  char			**cmd;
  struct s_alias	*next;
}			t_alias;

typedef struct		s_local
{
  char			*var_name;
  char			*var_value;
  struct s_local	*next;
}			t_local;

int			set_local(char **, char**, t_local *);

t_local			*get_local_var(char *);

int			check_valid_local_var(char *);

void			get_data_local(char **);

char			**get_data_alias(char **, char **);

t_alias			*get_alias(char *, char *, int, char **);

char			**set_alias(char **, t_alias *);

t_local			*get_local_var(char *);

int			set_local(char **, char **, t_local *);

#endif	/* !ALIAS_H_ */
