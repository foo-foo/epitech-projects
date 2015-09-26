/*
** malloc.h for malloc in /home/menich_a/rendu/PSU_2014_malloc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Jan 30 17:53:26 2015 Anatole Menichetti
** Last update Sun Feb 15 23:40:03 2015 Anatole Menichetti
*/

#ifndef MALLOC_H_
# define MALLOC_H_

#include <stdio.h>
#include <pthread.h>

/* state */
#define USED		(42)
#define FREE		(21)

/* regroup */
#define PREV		(-1)
#define BOTH		(0)
#define NEXT		(1)

typedef struct		s_block
{
  char			state;
  size_t		size;
  struct s_block	*prev;
  struct s_block	*next;
}			t_block;

void			show_alloc_mem(void);

void			*calloc(size_t, size_t);

void			*malloc(size_t);

void			*alloc_new_page(t_block **, size_t, size_t);

void			free(void *);

void			process_free(t_block **, size_t);

void			*realloc(void *, size_t);

void			*reallocation(t_block **, void *, t_block *, size_t);

void			*stretch(t_block **, void *, t_block *, size_t);

void			clear_block(char *, size_t);

void			add_block(t_block **, void *, size_t);

void			*cut_block(t_block **, t_block *, size_t);

void			regroup_blocks(t_block **, t_block *, char);

#endif /* !MALLOC_H_ */
