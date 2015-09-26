/*
** prefix.c for my_irc in /home/menich_a/rendu/PSU_2014_myirc
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Apr 12 12:21:43 2015 Anatole Menichetti
** Last update Sun Apr 12 12:35:41 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myirc.h"
#include "../../includes/client.h"

static char	*process_clear_prefix(char *buff, int *i, int *j)
{
  char		*prefix;
  char		*tmp;

  *j = *j + 1;
  if (*i != *j)
    {
      if (!(prefix = strndup(buff + *j, *i - *j)))
        return (NULL);
      while (buff[*i] == ' ' || buff[*i] == '\t')
        *i += 1;
      if (!(tmp = malloc(sizeof(*tmp) * (strlen(buff) + 1))))
        return (NULL);
      *j = *i;
      while (buff[*i] != ' ' && buff[*i] != '\t' && buff[*i] != '\n')
        *i += 1;
      strncpy(tmp, buff + *j, *i - *j);
      tmp[*i - *j] = '\0';
      strcat(tmp, " ");
      strcat(tmp, prefix);
      strncat(tmp, buff + *i, strlen(buff) - *i);
      free(buff);
      free(prefix);
      buff = tmp;
    }
  return (buff);
}

static char	*launch_clear_prefix(char *buff, int index, int j, int i)
{
  char		*tmp;

  if (buff[index] != '/')
    {
      if (buff[index] != '\n')
        {
          if (!(tmp = malloc(sizeof(*tmp) * strlen(buff) - j + 1)))
            return (NULL);
          strncpy(tmp, buff + j + 1, index - (j + 1));
          tmp[index - (j + 1)] = ':';
          tmp[index - j] = '\0';
          strcat(tmp, buff + index);
        }
      else
        if (!(tmp = strdup(buff + j + 1)))
          return (NULL);
      free(buff);
      buff = tmp;
    }
  else
    if (!(buff = process_clear_prefix(buff, &i, &j)))
      return (NULL);
  return (buff);
}

char		*clear_prefix(char *buff, int i)
{
  int		j;
  int		index;
  char		*tmp;

  if (buff[i] == ':')
    {
      j = i;
      while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\n')
        i += 1;
      index = i;
      while (buff[index] == ' ' || buff[index] == '\t')
        index += 1;
      return (launch_clear_prefix(buff, index, j, i));
    }
  if (buff[i] == '/')
    return (buff);
  if (!(tmp = malloc(sizeof(*tmp) * (strlen(buff) + 2))))
    return (NULL);
  strcpy(tmp, ":");
  strcat(tmp, buff);
  free(buff);
  return (tmp);
}
