/*
** malloc.c for malloc in /home/menich_a/rendu/PSU_2014_malloc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Jan 29 21:10:33 2015 Anatole Menichetti
** Last update Fri Feb 13 16:10:40 2015 Anatole Menichetti
*/

#include <unistd.h>
#include "malloc.h"

static t_block		*g_heap = 0;
static size_t		g_pagesize = 0;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
**		Display the current state of the heap.
*/
void		show_alloc_mem(void)
{
  t_block	*ptr;

  ptr = g_heap;
  printf("break : %p\n", sbrk(0));
  while (ptr)
    {
      if (ptr->state != FREE)
	{
	  if (ptr->next)
	    printf("%p - %p : %lu octets\n",
		   (void *)ptr + sizeof(t_block), (void *)ptr->next, ptr->size);
	  else
	    printf("%p - %p : %lu octets\n",
		   (void *)ptr + sizeof(t_block), sbrk(0), ptr->size);
	}
      ptr = ptr->next;
    }
  printf("end of disp.\n");
}

/*
**		Returns a pointer on a new allocated and empty space of size `nmemb * size`.
*/
void		*calloc(size_t nmemb, size_t size)
{
  t_block	*ptr;

  ptr = malloc(nmemb * size);
  clear_block((char *)ptr, nmemb * size);
  return (ptr);
}

/*
**		Returns a pointer on a new allocated space of `size`.
**		If there isn't any free block of the size required, allocate new page(s).
**		Else, returns a pointer on the first suffisant size block
**		(and split the block into two blocks if the block size is large enough to welcome two blocks).
*/
void		*malloc(size_t size)
{
  t_block	*ptr;
  void		*addr;

  if (!size || size > 2147483647 || pthread_mutex_lock(&g_mutex))
    return (NULL);
  size += sizeof(t_block) - (size % sizeof(t_block));
  ptr = g_heap;
  while (ptr && (ptr->size < size || ptr->state == USED))
    ptr = ptr->next;
  if (ptr)
    {
      addr = cut_block(&g_heap, ptr, size);
      if (pthread_mutex_unlock(&g_mutex))
	return (NULL);
      return (addr);
    }
  if (!g_pagesize)
    g_pagesize = getpagesize();
  return (alloc_new_page(&g_heap, size, g_pagesize));
}

/*
**		Free the block pointed by `ptr`:
**		First, pass the state of the block to FREE.
**		Then, regroup the block with its neighbors (if they arre FREE).
**		Finally, if the last block of the heap is FREE, it may free it (see process_free function).
*/
void		free(void *ptr)
{
  t_block	*p;

  if (ptr && g_heap)
    {
      if (ptr >= (void *)g_heap + sizeof(t_block) &&
	  ptr <= (void *)g_heap->prev + sizeof(t_block))
	{
	  p = ptr - sizeof(t_block);
	  if (!p || (p->state != FREE && p->state != USED) ||
	      pthread_mutex_lock(&g_mutex))
	    return;
	  p->state = FREE;
	  regroup_blocks(&g_heap, p, BOTH);
	  if (g_heap->prev->state == FREE &&
	      g_heap->prev->size + sizeof(t_block) >= g_pagesize)
	    process_free(&g_heap, g_pagesize);
	  pthread_mutex_unlock(&g_mutex);
	}
    }
}

/*
**		Adjusts the size of the block pointed by ptr to `size`.
**		If ptr is pointing on a valid block previously allocated, it process to allocation.
**		Else, it just return a pointer on a new allocated block of `size` (malloc).
*/
void		*realloc(void *ptr, size_t size)
{
  t_block	*p;

  if (!size || size > 2147483647 || pthread_mutex_lock(&g_mutex))
    return (NULL);
  size += sizeof(t_block) - (size % sizeof(t_block));
  if (ptr && ptr >= (void *)g_heap + sizeof(t_block) &&
      ptr <= (void *)g_heap->prev + sizeof(t_block))
    {
      p = ptr - sizeof(t_block);
      if (!p || (p->state != FREE && p->state != USED))
	{
	  pthread_mutex_unlock(&g_mutex);
	  return (malloc(size));
	}
      return (reallocation(&g_heap, ptr, p, size));
    }
  pthread_mutex_unlock(&g_mutex);
  return (malloc(size));
}
