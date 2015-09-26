/*
** alias.c for  in /home/bencha_a/42sh
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Wed May  7 16:08:51 2014 bencharif
** Last update Sat May 31 16:26:23 2014 menich_a
*/

#include <stdlib.h>
#include "alias.h"
#include "my.h"

int			add_one_alias(t_alias **begun, char **cmd_av, char *alias)
{
  t_alias		*elem;
  t_alias		*ptr;

  ptr = *begun;
  while (ptr && my_strcmp(alias, ptr->alias))
    ptr = ptr->next;
  if (ptr)
    {
      if (ptr->cmd)
	free(ptr->cmd);
      ptr->cmd = cmd_av;
      return (0);
    }
  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (msg_error("mysh: error: malloc failed.\n"));
  elem->alias = alias;
  elem->cmd = cmd_av;
  elem->next = *begun;
  *begun = elem;
  return (0);
}    

int			remove_alias(t_alias **list, char *alias)
{
  t_alias		*ptr;
  t_alias		*to_rm;

  ptr = *list;
  to_rm = *list;
  if (my_strcmp(ptr->alias, alias) == 0)
    {
      ptr = ptr->next;
      *list = ptr;
      free(to_rm);
      return (0);
    }
  while (my_strcmp(to_rm->next->alias, alias) && to_rm)
    to_rm = to_rm->next;
  if (to_rm == NULL)
    return (1);
  ptr = to_rm;
  to_rm = to_rm->next;
  ptr->next = to_rm->next;
  free(to_rm);
  return (0);
}

char			*cut_alias(char *data)
{
  int			j;
  int			i;
  char			*alias;

  if ((alias = malloc(my_strlen(data) * sizeof(char))) == NULL)
    {
      msg_error("mysh: error: malloc failed.\n");
      return (NULL + 1);
    }
  i = 0;
  j = 0;
  while (data[i] && data[i] != '=')
    alias[j++] = data[i++];
  alias[j] = '\0';
  return (alias);
}

t_alias			*get_alias(char *data, char *data2, int check, char **env)
{
  char			*alias;
  char			**cmd_av;
  static t_alias	*list = NULL;
  if (check)
    {
      if (remove_alias(&list, data))
	return (NULL + 1);
      return (list);
    }
  if (data == NULL || data2 == NULL)
    return (list);
  if ((alias = cut_alias(data)) == NULL + 1)
    return (NULL + 1);
  cmd_av = buff_to_cmdtab(data2, env);
  if (cmd_av == NULL)
    return (NULL + 1);
  if (cmd_av == NULL + 1)
    return (NULL);
  if (cmd_av[0])
    if (add_one_alias(&list, cmd_av, alias))
      return (NULL + 1);
  return (list);
}
