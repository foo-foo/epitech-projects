/*
** buff_to_cmdtab.c for mysh in /home/menich_a/rendu/PSU_2013_minishell2/sources/tools
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Feb 25 10:41:34 2014 menich_a
** Last update Sat May 31 14:06:07 2014 menich_a
*/

#include <stdlib.h>
#include <sys/types.h>
#include "alias.h"
#include "mysh.h"
#include "my.h"

/*
**      Fill av[i] with str (with a word).
*/
int	get_next_word(char *buff, char *str, int i)
{
  char	c;
  int	j;

  j = 0;
  if ((c = buff[i]) != '\0' && (c == '>' || c == '<' || c == '|' || c == '&'))
    while (buff[i] == c)
      {
        str[j] = -buff[i];
        i = i + 1;
        j = j + 1;
      }
  else
    while (buff[i] && buff[i] != ' ' && buff[i] != '<' && buff[i] != '>' &&
           buff[i] != '|' && buff[i] != '&' && buff[i] != '"' &&
           buff[i] != '\'' && buff[i] != '`' && buff[i] != '(')
      {
        if (buff[i] == '\\' && buff[i + 1])
          i = i + 1;
        str[j] = buff[i];
        i = i + 1;
        j = j + 1;
      }
  str[j] = '\0';
  return (i);
}

/*
**	Returns the size of the "ARGUMENT" pointed by `i'.
*/
int	my_argvlen(char *buf, int i)
{
  int	size;

  size = 0;
  if (buf[i] == '`')
    return (1);
  if (buf[i] == '>' || buf[i] == '<' || buf[i] == '|' || buf[i] == '&')
    {
      while (buf[i] == buf[i + 1] && size++ >= 0)
	i = i + 1;
      return (size + 1);
    }
  if (buf[i] == '"' || buf[i] == '\'' || buf[i] == '(')
    return (get_citation_size(buf, i));
  while (buf[i] != ' ' && buf[i] != '"' && buf[i] != '\'' && buf[i] != '\n' &&
	 buf[i] && buf[i] != '|' && buf[i] != '<' && buf[i] != '>' && buf[i] != '`')
    {
      if (buf[i] == '\\' && buf[i + 1])
	i = i + 1;
      if (buf[i] == '(' && i > 0 && buf[i - 1] != ' ')
	return (msg_error("mysh: syntax error near unexpected `(' token.\n"));
      i = i + 1;
      size = size + 1;
    }
  return (size);
}

char	**get_magic_quotes_cmd(char **av, char *buff, int *j, int *i)
{
  int	save;

  if (!(av = realloc(av, sizeof(*av) * (*j + 4))) ||
      !(av[*j] = malloc(sizeof(*av[*j] * 2))))
    return (msg_error_return("mysh: malloc failed.\n", 0));
  av[*j][0] = MAGIC_QUOTE;
  av[*j][1] = '\0';
  save = ++*i;
  while (buff[save] == ' ')
    save = save + 1;
  while (buff[*i] && buff[*i] != '`')
    *i = jump_backslash(buff, *i, '`');
  if (!buff[*i])
    return (msg_error_return(MAGIC_S_ERROR, NULL + 1));
  av[*j + 1] = my_strndup(buff + save, *i - save);
  av[*j + 2] = malloc(sizeof(*av[*j + 2] * 2));
  if (!av[*j] || !av[*j + 2])
    return (msg_error_return("mysh: malloc failed.\n", 0));
  av[*j + 2][0] = MAGIC_QUOTE;
  av[*j + 2][1] = '\0';
  *i = *i + 1;
  *j = *j + 2;
  return (av);
}

char	**my_word_to_tab(char **av, char *buff, int j, int *index)
{
  int	i;
  int	size;

  i = *index;
  size = my_argvlen(buff, i);
  if (size == -1 || i == -1)
    return (NULL + 1);
  if ((av = realloc(av, sizeof(*av) * (j + 2))) == NULL)
    return (msg_error_return("mysh: error: realloc failed.\n", NULL));
  if ((av[j] = malloc(sizeof(**av) * (size + 1))) == NULL)
    return (msg_error_return("mysh: error: malloc failed.\n", NULL));
  if (buff[i] == '"' || buff[i] == '\'' || buff[i] == '(')
    i = get_citation(av[j], buff, i);
  else
    i = get_next_word(buff, av[j], i);
  if (i == -1)
    return (NULL + 1);
  *index = i;
  return (av);
}

/*
**	Fill the tab previously initializated by `buff_to_cmdtab'.
*/
char	**buff_to_cmdtab(char *buff, char **env)
{
  int	i;
  int	j;
  char	**av;
  int	tild;

  i = 0;
  j = 0;
  av = NULL;
  while (buff[i] != '\0')
    {
      jump_some_spaces(buff, &tild, &i, 0);
      if (buff[i] != '`')
	av = my_word_to_tab(av, buff, j, &i);
      else
	av = get_magic_quotes_cmd(av, buff, &j, &i);
      if (av == NULL || av == NULL + 1)
	return (av);
      if (tild)
	if ((av[j] = get_tild(av[j], env)) == NULL)
	  return (NULL);
      jump_some_spaces(buff, &tild, &i, 1);
      j = j + 1;
    }
  av[j] = NULL;
  return (av);
}
