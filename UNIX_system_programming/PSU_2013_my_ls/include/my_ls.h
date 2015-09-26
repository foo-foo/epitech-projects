/*
** my_ls.h for my_ls in /home/menich_a/rendu/PSU_2013_my_ls
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Nov 25 13:06:20 2013 menich_a
** Last update Sun Dec  1 18:27:00 2013 menich_a
*/

#ifndef		MY_LS_H_
# define	MY_LS_H_

typedef struct	dirent	t_dirent;
typedef struct	stat	t_stat;
typedef struct	passwd	t_passwd;
typedef struct	group	t_grp;

typedef struct	s_list
{
  int		blocks;
  int		type;
  char		*way;
  char		*name;
  char		*date;
  char		*size;
  char		*grp;
  char		*usr;
  char		*link;
  char		*rights;
  struct s_list	*next;
}		t_list;

void	launch_options(t_dirent *, char *, t_list **, char *);

void	long_listing_option(char *, t_list **, int, char *);

void	recursive_option(char *, t_list *);

void	directory_name_option(char *, t_list *);

void	reverse_option(char *, t_list *);

void	time_sort_option(char *, t_list *);

void	my_show_long_list(t_list *, char *, char *);

int	my_list_size(t_list *);

int	my_put_int_list(t_list **, char *);

t_list	*create_list(t_list *, char **, int, int);

char	*my_get_str(int);

char	*my_strdup(char *);

#endif
