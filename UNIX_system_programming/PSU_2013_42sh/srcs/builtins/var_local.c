/*
** var_local.c for  in /home/bencha_a/42sh/PSU_2013_minishell2/srcs
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Thu May  8 20:40:58 2014 bencharif
** Last update Sun Jun  1 15:13:31 2014 menich_a
*/

#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "my.h"

int		check_valid_local_var(char *buff)
{
  int		pos;
  int		i;

  i = 0;
  while (buff[i] == ' ')
    i = i + 1;
  while (buff[i] && buff[i] != ' ' && buff[i] != '=')
    i = i + 1;
  if (buff[i] != '=')
    return (1);
  pos = buff[i];
  while (buff[i] && buff[i] != ' ')
    {
      if (buff[i] == '"')
	while (buff[++i] && buff[i] != '"')
	  if (buff[i] == '\\' && buff[i + 1] == '"')
	    i = i + 1;
      if (!buff[i])
	return (-1);
      i = i + 1;
    }
  if (!buff[i] || i > pos + 1)
    return (0);
  return (-1);
}

int		add_one_var(t_local **begun, char *var_name, char *var_value)
{
  t_local	*elem;
  t_local	*ptr;

  ptr = *begun;
  while (ptr && my_strcmp(ptr->var_name, var_name))
    ptr = ptr->next;
  if (ptr)
    {
      free(ptr->var_value);
      ptr->var_value = var_value;
      return (0);
    }
  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (msg_error("mysh: error: malloc failed.\n"));
  elem->var_name = var_name;
  elem->var_value = var_value;
  elem->next = *begun;
  *begun = elem;
  return (0);
}

char		*get_var_value(char *buff, int size, int i)
{
  char		*var_value;
  int		x;

  x = 0;
  while (buff[size] && buff[size] != ' ')
    {
      if (buff[size] == '"')
	while (buff[++size] && buff[size] != '"')
	  if (buff[size] == '\\' && buff[size + 1] == '"')
	    size = size + 1;
      if (!buff[size++])
	return (NULL);
    }
  if ((var_value = malloc(sizeof(*var_value) * (size + 1))) == NULL)
    return (NULL);
  while (i < size)
    {
      while (buff[i] == '"')
	i = i + 1;
      if (buff[i] == '\\' && buff[i + 1] == '"')
	i = i + 1;
      var_value[x++] = buff[i++];
    }
  var_value[x] = '\0';
  return (var_value);
}

t_local		*get_local_var(char *buff)
{
  int		i;
  int		j;
  char		*var_name;
  char		*var_value;
  static	t_local	*list = NULL;

  i = 0;
  j = 0;
  if (buff == NULL)
    return (list);
  while (buff[i] == ' ')
    i = i + 1;
  j = i;
  while (buff[i] && buff[i] != ' ' && buff[i] != '=')
    i = i + 1;
  if (buff[i] != '=')
    return (NULL);
  if ((var_name = my_strndup(buff + j, i - j)) == NULL)
    return (NULL);
  if ((var_value = get_var_value(buff + i + 1, 0, 0)) == NULL)
    return (NULL);
  if (add_one_var(&list, var_name, var_value))
    return (NULL);
  return (list);
}

int		set_local(char **cmd, char **env, t_local *list)
{
  int		i;
  char		*tmp;
  t_local	*ptr;

  i = 0;
  while (cmd[i] != NULL)
    {
      tmp = my_find_in_env(env, cmd[i] + 1);
      if (tmp == NULL)
	{
	  ptr = list;
	  while (ptr && my_strcmp(cmd[i] + 1, ptr->var_name))
	    ptr = ptr->next;
	  if (ptr)
	    tmp = ptr->var_value;
	}
      if (tmp)
	{
	  free(cmd[i]);
	  if ((cmd[i] = my_strdup(tmp)) == NULL)
	    return (-1);
	}
      i++;
    }
  return (0);
}
