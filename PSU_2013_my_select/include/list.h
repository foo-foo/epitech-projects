/*
** list.h for my_select in /home/menich_a/rendu/CPE_2013_Pushswap/include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jan  6 17:36:46 2014 menich_a
** Last update Sun Jan 19 19:19:09 2014 menich_a
*/

#ifndef LIST_H_
# define LIST_H_

typedef struct	s_list
{
  int		rv;
  int		pos;
  char		*data;
  struct s_list	*prev;
  struct s_list	*next;
}		t_list;

void	my_put_end_list(t_list *, char *, int);

void	my_rm_from_list(t_list *, t_list *);

int	my_list_size(t_list *);

t_list	*my_create_list(void);

void	my_rm_list(t_list *);

#endif	/* !LIST_H_ */
