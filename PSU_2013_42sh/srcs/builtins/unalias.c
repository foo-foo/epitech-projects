/*
** unalias.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May 15 14:24:39 2014 menich_a
** Last update Sat May 24 21:33:08 2014 menich_a
*/

#include <stdlib.h>
#include "alias.h"
#include "my.h"

char		**unalias(char **cmd, char **env)
{
  t_alias	*list;
  t_alias	*ptr;

  list = get_alias(NULL, NULL, 0, env);
  if (list == NULL + 1)
    return (NULL);
  ptr = list;
  if (cmd[1] == NULL)
    {
      msg_error("mysh: unalias: usage: unalias [-a] name [name ...]\n");
      return (NULL + 1);
    }
  while (ptr && my_strcmp(cmd[1], ptr->alias))
    ptr = ptr->next;
  if (ptr == NULL)
    {
      msg_error("mysh: unalias: ");
      msg_error(cmd[1]);
      msg_error(": not found\n");
      return (NULL + 1);
    }
  if (get_alias(ptr->alias, NULL, 1, env) == NULL + 1)
    return (NULL);
  return (env);
}
