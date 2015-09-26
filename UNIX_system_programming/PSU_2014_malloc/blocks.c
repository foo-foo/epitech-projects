/*
** blocks.c for malloc in /home/menich_a/rendu/PSU_2014_malloc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Feb  1 17:39:39 2015 Anatole Menichetti
** Last update Fri Feb 13 16:09:55 2015 Anatole Menichetti
*/

#include "malloc.h"

/*
**		Clears the `block` memory.
*/
void		clear_block(char *block, size_t size)
{
  while (size--)
    *block++ = '\0';
}

/*
**		Adds a block of size `size` in queue of `heap`.
**		The new block is pointing on `addr`.
*/
void		add_block(t_block **heap, void *addr, size_t size)
{
  t_block	*elem;

  elem = addr;
  elem->state = USED;
  elem->size = size;
  elem->next = NULL;
  elem->prev = elem;
  if (!*heap)
    *heap = elem;
  else
    {
      elem->prev = (*heap)->prev;
      (*heap)->prev->next = elem;
      (*heap)->prev = elem;
    }
}

/*
**		Cuts `block` in two blocks (the first of size `size`).
**		Returns a pointer on `block`.
*/
void		*cut_block(t_block **heap, t_block *block, size_t size)
{
  t_block	*elem;

  if (block && block->size > size + sizeof(t_block))
    {
      elem = (void *)block + size + sizeof(t_block);
      elem->size = block->size - (size + sizeof(t_block));
      elem->state = FREE;
      elem->next = block->next;
      elem->prev = block;
      if (block->next)
	block->next->prev = elem;
      else
	(*heap)->prev = elem;
      block->next = elem;
      block->size = size;
    }
  block->state = USED;
  return ((void *)block + sizeof(t_block));
}

/*
**		Regroups `block` with block->prev & block->next (if they are FREE).
*/
void		regroup_blocks(t_block **heap, t_block *block, char which)
{
  t_block	*tmp;

  if (which != NEXT && block != *heap && block->prev->state == FREE)
    {
      if (block->next)
	block->next->prev = block->prev;
      else
	(*heap)->prev = block->prev;
      block->prev->next = block->next;
      block->prev->size += (block->size + sizeof(t_block));
      tmp = block->prev;
      clear_block((char *)block, block->size + sizeof(t_block));
      block = tmp;
    }
  if (which != PREV && block->next && block->next->state == FREE)
    {
      block->size += (block->next->size + sizeof(t_block));
      if (block->next->next)
	block->next->next->prev = block;
      else
	(*heap)->prev = block;
      tmp = block->next->next;
      clear_block((char *)block->next, block->next->size + sizeof(t_block));
      block->next = tmp;
    }
}
