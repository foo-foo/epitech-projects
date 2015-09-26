/*
** str_to_cmdtab.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr  9 16:52:41 2015 Anatole Menichetti
** Last update Sat Apr 11 16:33:39 2015 audurier julien
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
  if (cpt > 3)
    cpt = 3;
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

static int	get_one_word(char **cmd, int y, char *str, int i)
{
  int		len;

  if (y < 2)
    {
      len = get_wordlen(str + i);
      if (!(cmd[y] = strndup(str + i, len)))
	return (-1);
      i += len;
      while (str[i] == ' ' || str[i] == '\t')
	i += 1;
    }
  else
    if (!(cmd[y] = strndup(str + i, strlen(str + i))))
      return (-1);
  return (i);
}

char		**str_to_cmdtab(char *str)
{
  char		**cmd;
  int		size;
  int		i;
  int		y;

  i = 0;
  y = 0;
  size = get_words_nbr(str);
  if (!(cmd = malloc(sizeof(*cmd) * (size + 1))))
    return (NULL);
  while (str[i] == ' ' || str[i] == '\t')
    i += 1;
  while (y < size)
    if ((i = get_one_word(cmd, y++, str, i)) == -1)
      return (NULL);
  cmd[y] = NULL;
  return (cmd);
}
