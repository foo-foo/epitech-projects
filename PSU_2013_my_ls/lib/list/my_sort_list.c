/*
** my_sort_list.c for my_ls in /home/menich_a/rendu/PSU_2013_my_ls/lib/list
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Nov 28 16:07:00 2013 menich_a
** Last update Sun Dec  1 21:07:35 2013 menich_a
*/

#include <stdlib.h>
#include "my_ls.h"
#include "my.h"

void		interchange_other_datas(t_list *ptr, t_list *next, t_list *tmp)
{
  tmp->rights = my_strdup(ptr->rights);
  ptr->rights = my_strdup(next->rights);
  next->rights = my_strdup(tmp->rights);
  free(tmp->rights);
  tmp->link = my_strdup(ptr->link);
  ptr->link = my_strdup(next->link);
  next->link = my_strdup(tmp->link);
  free(tmp->link);
  tmp->usr = my_strdup(ptr->usr);
  ptr->usr = my_strdup(next->usr);
  next->usr = my_strdup(tmp->usr);
  free(tmp->usr);
  tmp->grp = my_strdup(ptr->grp);
  ptr->grp = my_strdup(next->grp);
  next->grp = my_strdup(tmp->grp);
  free(tmp->grp);
  tmp->size = my_strdup(ptr->size);
  ptr->size = my_strdup(next->size);
  next->size = my_strdup(tmp->size);
  free(tmp->size);
  tmp->date = my_strdup(ptr->date);
  ptr->date = my_strdup(next->date);
  next->date = my_strdup(tmp->date);
  free(tmp->date);
}

void		interchange_ptr_datas(t_list *ptr, t_list *next, t_list *tmp, char *options)
{
  tmp->name = my_strdup(ptr->name);
  free(ptr->name);
  ptr->name = my_strdup(next->name);
  free(next->name);
  next->name = my_strdup(tmp->name);
  free(tmp->name);
  if (find_in_tab(options, 'l') == 0)
    {
      tmp->blocks = ptr->blocks;
      ptr->blocks = next->blocks;
      next->blocks = tmp->blocks;
      tmp->type = ptr->type;
      ptr->type = next->type;
      next->type = tmp->type;
      tmp->way = my_strdup(ptr->way);
      ptr->way = my_strdup(next->way);
      next->way = my_strdup(tmp->way);
      free(tmp->way);
      interchange_other_datas(ptr, next, tmp);
    }
}

void		my_alpha_sort(t_list *list, char *options, int is_neg)
{
  t_list        *ptr;
  t_list        *tmp;
  int           i;
  int           n;
  int		debugg;

  i = 0;
  n = my_list_size(list) * my_list_size(list);
  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    exit(-1);
  while (i < n)
    {
      ptr = list;
      while (ptr->next != NULL)
        {
	  if (my_strcmp(ptr->name, ptr->next->name) >= 0 && is_neg == 0)
	    interchange_ptr_datas(ptr, ptr->next, tmp, options);
	  if (my_strcmp(ptr->name, ptr->next->name) < 0 && is_neg == 1)
		interchange_ptr_datas(ptr, ptr->next, tmp, options);
	  ptr = ptr->next;
        }
      i = i + 1;
    }
  free(tmp);
}

void    my_sort_list(t_list *list, char *options)
{
  if (find_in_tab(options, 'r') == 0)
    my_alpha_sort(list, options, 1);
  else
    my_alpha_sort(list, options, 0);
}
