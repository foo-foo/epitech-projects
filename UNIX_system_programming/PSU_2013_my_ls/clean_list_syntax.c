/*
** clean_list_syntax.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Dec  1 15:14:45 2013 menich_a
** Last update Sun Dec  1 21:18:26 2013 menich_a
*/

#include "my_ls.h"
#include <stdlib.h>

void            ajust_size_columns(t_list *list, t_list *ptr, char *tmp, int size)
{
  int           i;

  ptr = list;
  while (ptr != NULL)
    {
      i = 0;
      if (my_strlen(ptr->size) < size)
        {
          if ((tmp = malloc(sizeof(*tmp) * size + 1)) == NULL)
	    exit(-1);
          while (i < size - my_strlen(ptr->size))
            {
              tmp[i] = ' ';
              i = i + 1;
            }
          tmp[i] = '\0';
          my_strcat(tmp, ptr->size);
          free(ptr->size);
          ptr->size = my_strdup(tmp);
          free(tmp);
        }
      ptr = ptr->next;
    }
}

void            ajust_links_columns(t_list *list, t_list *ptr, char *tmp, int links)
{
  int           i;

  ptr = list;
  while (ptr != NULL)
    {
      i = 0;
      if (my_strlen(ptr->link) < links)
        {
          if ((tmp = malloc(sizeof(*tmp) * links + 1)) == NULL)
	    exit(-1);
          while (i < links - my_strlen(ptr->link))
            {
              tmp[i] = ' ';
              i = i + 1;
            }
          tmp[i] = '\0';
          my_strcat(tmp, ptr->link);
          free(ptr->link);
          ptr->link = my_strdup(tmp);
          free(tmp);
        }
      ptr = ptr->next;
    }
}

void            clean_list_syntax(t_list *list)
{
  t_list        *ptr;
  char          *tmp;
  int           size;
  int           links;

  size = 1;
  links = 0;
  ptr = list;
  while (ptr != NULL)
    {
      if (my_strlen(ptr->size) > size)
        size = my_strlen(ptr->size);
      if (my_strlen(ptr->link) > links)
        links = my_strlen(ptr->link);
      ptr = ptr->next;
    }
  ajust_links_columns(list, ptr, tmp, links);
  ajust_size_columns(list, ptr, tmp, size);
}
