/*
** my_str_isprintable.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_10
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  8 07:49:12 2013 menich_a
** Last update Sun Jun  1 12:21:32 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my.h"

int	my_str_isprintable(char *str)
{
  int	i;
  int	cpt;

  i = 0;
  cpt = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '-' && str[i + 1] != '-')
	cpt = cpt + 1;
      if ((str[i] < ' ' || str[i] > '~') && str[i] != '\n')
	return (0);
      i = i + 1;
    }
  if (cpt < 20)
    return (1);
  return (0);
}

int	my_word_iscmd(char *word, int i)
{
  while (i >= 0 && word[i] != ' ' && word[i] != ';' &&
         word[i] != '|' && word[i] != '&' && word[i] != '/')
    i = i - 1;
  if (i < 0 || word[i] == ';' || word[i] == '|' || word[i] == '&')
    return (1);
  if (word[i] == '/')
    return (0);
  while (i >= 0 && word[i] == ' ')
    i = i - 1;
  if (i < 0 || word[i] == ';' || word[i] == '|' || word[i] == '&')
    return (1);
  return (0);
}

int	is_line_half_completed(t_line *line, char **tab)
{
  int	i;
  int	j;
  int	cpt;

  i = 0;
  j = line->i;
  cpt = 0;
  while (j >= 0 && line->line[j] != ' ' && line->line[i] != '/')
    j = j - 1;
  j = j + 1;
  while (tab[0][cpt] && tab[0][cpt] == line->line[j])
    {
      cpt = cpt + 1;
      j = j + 1;
    }
  while (tab[i])
    {
      if (tab[i][cpt] != tab[0][cpt])
        return (0);
      i = i + 1;
    }
  return (1);
}

int	my_char_is_alphanum(char c, int check)
{
  if (check == 0)
    {
      if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9'))
        return (1);
      return (0);
    }
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
      (c >= '0' && c <= '9'))
    return (1);
  return (0);
}

int	check_if_color_cmd(char **cmd)
{
  if (!cmd)
    return (1);
  if (!my_strcmp(cmd[0], "kill"))
    {
      if (setpgrp())
        exit(msg_error("mysh: setpgrp error.\n"));
      return (1);
    }
  if (my_strcmp(cmd[0], "ls") && my_strcmp(cmd[0], "grep"))
    return (1);
  return (0);
}
