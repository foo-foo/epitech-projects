/*
** alias_tools.c for  in /home/menich_a/rendu/PSU_2013_42sh/srcs/builtins
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun May 25 23:29:09 2014 menich_a
** Last update Fri May 30 19:27:31 2014 menich_a
*/

#include <stdlib.h>
#include "alias.h"
#include "my.h"

char		**get_data_alias(char **tab, char **env)
{
  int		i;

  i = 0;
  while (tab[i] && tab[i + 1] && tab[i + 2])
    {
      if (my_strcmp(tab[i] , "alias") == 0)
        {
          if (get_alias(tab[i + 1], tab[i + 2], 0, env) == NULL + 1)
            return (NULL);
        }
      i = i + 3;
    }
  return (env);
}

char		**set_alias(char **t, t_alias *list)
{
  t_alias	*ptr;
  char		**t2;
  int		i;
  int		j;

  j = 1;
  i = -1;
  if ((ptr = list) == NULL + 1)
    return (NULL);
  while (ptr && my_strcmp(t[0], ptr->alias))
    ptr = ptr->next;
  if (ptr)
    {
      if (!(t2 = malloc((my_tablen(t) + my_tablen(ptr->cmd) + 1) * sizeof(*t))))
	return (msg_error_return("mysh: error: malloc failed.\n", NULL));
      while (ptr->cmd && ptr->cmd[++i])
        if ((t2[i] = my_strdup(ptr->cmd[i])) == NULL)
          return (NULL);
      while (t && t[j] != NULL)
        if ((t2[i++] = my_strdup(t[j++])) == NULL)
          return (NULL);
      t2[i] = NULL;
      return (t2);
    }
  return (t);
}
