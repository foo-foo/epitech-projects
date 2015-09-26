/*
** push_swap.h for push_swap in /home/menich_a/rendu/CPE_2013_push_swap
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Dec  9 15:18:26 2013 menich_a
** Last update Mon Jan  6 17:35:38 2014 menich_a
*/

#ifndef		PUSH_SWAP_H_
# define	PUSH_SWAP_H_

typedef struct	s_list
{
  int		value;
  struct s_list	*next;
  struct s_list	*prev;
}		t_list;

int	sa(t_list *);

int	pa(t_list *, t_list *);

int	ra(t_list *);

int	rra(t_list *);

int	sb(t_list *);

int	pb(t_list *, t_list *);

int	rb(t_list *);

int	rrb(t_list *);

int	ss(t_list *, t_list *);

int	rr(t_list *, t_list *);

int	rrr(t_list *, t_list *);

#endif
