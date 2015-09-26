/*
** alloc.c for malloc in /home/menich_a/rendu/PSU_2014_malloc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Feb 13 14:22:17 2015 Anatole Menichetti
** Last update Fri Feb 13 16:08:53 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "malloc.h"

extern pthread_mutex_t	g_mutex;

/*
**		Allocates the correct number of pages to return a block of `size`.
**		If the size asked + the size needed for the block is lighter that
**		the allocated size, the block is cut into two blocks
**		(one of the size needed, the other with the rest of the pagesize).
**		Returns a pointer on the new created block of asked size.
*/
void		*alloc_new_page(t_block **heap, size_t size, size_t pagesize)
{
  void		*addr;
  size_t	s;

  s = pagesize;
  if (size + sizeof(t_block) > pagesize)
    {
      s = size % pagesize;
      s = pagesize - s;
      s += size;
      if (size + sizeof(t_block) > s)
        s += pagesize;
    }
  if ((addr = sbrk(s)) == (void *)-1)
    return (NULL);
  add_block(heap, addr, s - sizeof(t_block));
  regroup_blocks(heap, (*heap)->prev, PREV);
  addr = cut_block(heap, (*heap)->prev, size);
  if (pthread_mutex_unlock(&g_mutex))
    return (NULL);
  return (addr);
}

/*
**		Returns size allocated to the heap.
*/
size_t		get_heap_size(t_block *ptr)
{
  size_t	size;

  size = 0;
  while (ptr->next)
    {
      size += ptr->size + sizeof(t_block);
      ptr = ptr->next;
    }
  return (size);
}

/*
**		It should free the last block of the heap partially or completely
**		according to the entire size of the heap. If the heap size is a pagesize multiple,
**		free all the block. Else, free a bit of the block so that new heap size is a pagesize multiple.
*/
void		process_free(t_block **heap, size_t pagesize)
{
  t_block	*block;
  size_t	size;
  size_t	s;

  block = (*heap)->prev;
  size = block->size + sizeof(t_block);
  if (block == *heap)
    *heap = NULL;
  else
    {
      s = get_heap_size(*heap);
      if (s % pagesize)
	{
	  block->size = (pagesize - (s + pagesize) % pagesize) - sizeof(t_block);
	  size -= (block->size + sizeof(t_block));
	  block = (void *)block + sizeof(t_block) + block->size;
	}
      else
	{
	  block->prev->next = NULL;
	  (*heap)->prev = block->prev;
	}
    }
  clear_block((char *)block, size);
  sbrk(-size);
}

/*
**		Stretch the memory attributed to the block `p`.
**		If `p` is the last block of the heap, extend memory with sbrk().
**		Else, regroup `p` with the following block to create a block of suffisant size.
*/
void		*stretch(t_block **heap, void *ptr, t_block *p, size_t size)
{
  if (!p->next)
    {
      sbrk(size - p->size);
      p->size = size;
    }
  else
    {
      regroup_blocks(heap, p, NEXT);
      ptr = cut_block(heap, p, size);
    }
  pthread_mutex_unlock(&g_mutex);
  return (ptr);
}

/*
**		If `size` if lighter that old size, it splits the block `p` in two blocks of appropriate size.
**		If the block pointed by `p` is the last of the heap
**		or if the block following is FREE and that it's size is suffisiant to store the size needed,
**		then it stretch the memory attributed to ptr.
**		Else, allocates a new block of `size`, copy the ptr memory to the new block and free `p`.
*/
void		*reallocation(t_block **heap, void *ptr, t_block *p, size_t size)
{
  t_block	*new;

  if (size < p->size)
    {
      if (size + sizeof(t_block) < p->size)
        {
          ptr = cut_block(heap, p, size);
          p = ptr - sizeof(t_block);
          regroup_blocks(heap, p->next, NEXT);
        }
      pthread_mutex_unlock(&g_mutex);
      return (ptr);
    }
  if (!p->next || (p->next->state == FREE &&
                   p->next->size + p->size + sizeof(t_block) >= size))
    return (stretch(heap, ptr, p, size));
  pthread_mutex_unlock(&g_mutex);
  new = malloc(size);
  if (pthread_mutex_lock(&g_mutex))
    return (NULL);
  memmove(new, (void *)p + sizeof(t_block), p->size);
  pthread_mutex_unlock(&g_mutex);
  free(p);
  return (new);
}
