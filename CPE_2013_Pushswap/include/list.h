/*
** list.h for liblist.a in /home/menich_a/rendu/CPE_2013_Pushswap/include
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Jan  6 17:36:46 2014 menich_a
** Last update Mon Jan  6 23:14:44 2014 menich_a
*/

#ifndef LIST_H_
# define LIST_H_
#include "push_swap.h"

void	my_rm_list(t_list *);

t_list	*my_create_list(void);

int	my_is_sorted(t_list *);

int	my_list_size(t_list *);

void	my_put_in_list(t_list *, int);

void	my_put_end_list(t_list *, int);

void	my_rm_from_list(t_list *, t_list *);

void	my_show_list(t_list *);

#endif	/* LIST_H_ */
