/*
** str_to_cmdtab.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr  9 16:50:41 2015 Anatole Menichetti
** Last update Sat Apr 11 11:48:32 2015 Anatole Menichetti
*/

#include <string.h>
#include <stdlib.h>

static int	get_words_nbr(char *str)
{
  int		i;
  int		cpt;

  i = 0;
  cpt = 0;
  while (str[i] == ' ' || str[i] == '\t')
    i += 1;
  while (str[i])
    {
      cpt += 1;
      while (str[i] && str[i] != ' ' && str[i] != '\t')
        i += 1;
      while (str[i] == ' ' || str[i] == '\t')
        i += 1;
    }
  return (cpt);
}

static int	get_wordlen(char *word)
{
  int		i;

  i = 0;
  while (word[i] && word[i] != ' ' && word[i] != '\t')
    i += 1;
  return (i);
}

char	**str_to_cmdtab(char *str)
{
  char	**cmd;
  int	size;
  int	len;
  int	i;
  int	y;

  i = 0;
  y = -1;
  size = get_words_nbr(str);
  if (!(cmd = malloc(sizeof(*cmd) * (size + 1))))
    return (NULL);
  while (str[i] == ' ' || str[i] == '\t')
    i += 1;
  while (++y < size)
    {
      if (str[(len = get_wordlen(str + i)) + i - 1] == '\n')
        len -= 1;
      if (!(cmd[y] = strndup(str + i, len)))
        return (NULL);
      i += len;
      while (str[i] == ' ' || str[i] == '\t')
        i += 1;
    }
  cmd[y] = NULL;
  return (cmd);
}
