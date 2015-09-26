/*
** my_jump_inhibitors.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue May 20 13:14:07 2014 menich_a
** Last update Sun May 25 22:17:41 2014 menich_a
*/

#include <unistd.h>
#include "my.h"

int	jump_backslash(char *str, int index, char inhibitor)
{
  if (str[index] == '\\' && str[index + 1] == inhibitor)
    return (index + 2);
  return (index + 1);
}

int	get_citation_size(char *buff, int i)
{
  char	c;
  int	size;

  c = buff[i];
  if (c == '(')
    c = ')';
  else
    i = i + 1;
  size = 0;
  while (buff[i] && buff[i] != c)
    {
      if (buff[i] == '\\' && buff[i + 1] == c)
	i = i + 1;
      i = i + 1;
      size = size + 1;
    }
  if (!buff[i])
    {
      msg_error("mysh: syntax error near unexpected `");
      write(2, &c, 1);
      return (msg_error("' token.\n"));
    }
  if (c == ')' && size++)
    i = i + 1;
  return (size);
}

int	get_citation(char *dest, char *src, int i)
{
  char	c;
  int	cpt;

  cpt = 0;
  c = src[i];
  if (c == '(' && (dest[cpt++] = -c))
    c = ')';
  while (src[++i] && src[i] != c)
    {
      if (src[i] == '\\' && src[i + 1] == c)
	i = i + 1;
      dest[cpt++] = src[i];
    }
  if (!src[i])
    {
      msg_error("mysh: syntax error near unexpected `");
      write(2, &c, 1);
      return (msg_error("' token.\n"));
    }
  if (c == ')')
    dest[cpt++] = -c;
  dest[cpt] = '\0';
  return (i + 1);
}

void	jump_inhibitors_cpy(char *dest, char *src, int *index1, int *index2)
{
  char	c;
  int	i;
  int	cpt;

  i = *index1;
  cpt = *index2;
  if (!src || !dest)
    return;
  if (src[cpt] == '"' || src[cpt] == '\'' || src[cpt] == '`' || src[cpt] == '(')
    {
      if ((c = src[cpt]) == '(')
	c = ')';
      dest[i] = src[cpt];
      while ((dest[++i] = src[++cpt]) != '\0' && src[cpt] != c)
	if (src[cpt] == '\\' && src[cpt + 1] == c)
	  dest[++i] = src[++cpt];
    }
  if (src[cpt] == '\\' && src[cpt + 1] == ';')
    cpt = cpt + 1;
  if (src[cpt])
    dest[i++] = src[cpt++];
  *index1 = i;
  *index2 = cpt;
}

void	jump_inhibitors(char *src, int *index)
{
  int	i;
  char	c;

  i = *index;
  if (!src)
    return;
  if (src[i] == '"' || src[i] == '\'' || src[i] == '`' || src[i] == '(')
    {
      if ((c = src[i]) == '(')
	c = ')';
      while (src[++i] && src[i] != c)
	if (src[i] == '\\' && src[i + 1] == c)
	  i = i + 1;
    }
  if (src[i] == '\\' && src[i + 1] == ';')
    i = i + 1;
  if (src[i])
    i = i + 1;
  *index = i;
}
