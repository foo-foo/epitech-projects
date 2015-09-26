/*
** str_to_wordtab.c for str_to_wordtab in /home/rosain_f/rendu/PSU_2014_myftp
** 
** Made by Francois Rosain
** Login   <rosain_f@epitech.net>
** 
** Started on  Wed Mar 11 08:21:23 2015 Francois Rosain
** Last update Thu Apr  9 14:04:42 2015 Francois Rosain
*/

#include <stdio.h>
#include <stdlib.h>

static int	is_space(char c)
{
  if ((c == ' ') || (c == '\t') || c == '\r')
    return (1);
  return (0);
}

static int	nb_words(char *str)
{
  int		i;
  int		n;

  i = 0;
  n = 0;
  while (str[i] && is_space(str[i]))
    i++;
  while (str[i])
    {
      while (str[i] && !is_space(str[i]))
	i++;
      n++;
      while (str[i] && is_space(str[i]))
	i++;
    }
  return (n);
}

static char	*get_next_word(char *str)
{
  char		*word;
  int		i;
  int		size;

  i = 0;
  size = 0;
  while (str[i] && !is_space(str[i]))
    {
      size++;
      i++;
    }
  i = 0;
  if ((word = malloc(size * sizeof(char) + 1)) == NULL)
    {
      printf("Error : Can\'t perform malloc.\n");
      return (NULL);
    }
  while (str[i] && !is_space(str[i]))
    {
      word[i] = str[i];
      i++;
    }
  word[i] = 0;
  return (word);
}

char	**str_to_wordtab(char *str)
{
  char	**tab;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (nb_words(str) == 0
      || (tab = malloc((nb_words(str) + 1) * sizeof(char*))) == NULL)
    {
      printf("Error : Can\'t perform malloc.\n");
      return (NULL);
    }
  while (str[i] && is_space(str[i]))
    i++;
  while (str[i])
    {
      if ((tab[j++] = get_next_word(str + i)) == NULL)
	return (NULL);
      while (str[i] && !is_space(str[i]))
	i++;
      while (str[i] && is_space(str[i]))
	i++;
    }
  tab[j] = NULL;
  return (tab);
}

void	free_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    free(tab[i++]);
  free(tab);
}
