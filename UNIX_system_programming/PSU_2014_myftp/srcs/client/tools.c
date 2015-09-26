/*
** tools.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 28 18:12:14 2015 Anatole Menichetti
** Last update Sat Mar 28 18:29:53 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

int		rfputstr(int fd, char *str)
{
  char		*s;
  int		size;

  if (!str)
    return (-1);
  size = strlen(str);
  s = malloc(sizeof(*s) * (size + 2));
  if (!s)
    return (-1);
  strcpy(s, str);
  s[size - 1] = '\r';
  s[size] = '\n';
  s[size + 1] = '\0';
  size = fputstr(fd, s);
  free(s);
  return (size);
}

int		putcolor(char *str)
{
  if (str[strlen(str) - 2] == '\r')
    {
      remove_ret(str);
      if (str[0] == '4' || str[0] == '5')
        putstr("\033[31m");
      else
        putstr("\033[36m");
      putstr(str);
      putstr("\033[0m");
    }
  else
    putstr(str);
  return (SUCCESS);
}

char		*remove_ret(char *str)
{
  int   s;

  s = strlen(str);
  if (str[s - 2] == '\r')
    {
      str[s - 2] = '\n';
      str[s - 1] = '\0';
    }
  return (str);
}

char		*get_usr_name(int fd, FILE *fp, char *usr, char *usr_name)
{
  char		*buff;
  size_t	len;

  buff = 0;
  len = 0;
  if (fd && fp)
    {
      if (fputstr(fd, "ACCT\r\n") == -1 || getline(&buff, &len, fp) == -1)
        {
          my_perror(EUNAVAILABLE, FAILURE, fd, 0);
          return (NULL);
        }
      if (strncmp(buff, "257", 3))
        usr = strdup("Anonymous");
      else
        usr = strndup(buff + 4, strlen(buff) - 15);
      free(buff);
      return (usr);
    }
  if (!usr_name)
    {
      putstr("Anonymous ~> ");
      return ("done");
    }
  return (strdup(usr_name));
}

int		display_prompt(int fd, FILE *fp)
{

  char		*usr;
  static char	*usr_name = NULL;

  usr = get_usr_name(fd, fp, 0, usr_name);
  if (!usr)
    return (my_perror(EALLOC, FAILURE, fd, 0));
  if (!strcmp(usr, "done"))
    return (SUCCESS);
  putstr("\033[35m");
  putstr(usr);
  putstr(" ~> ");
  putstr("\033[0m");
  if (usr_name && strcmp(usr_name, usr))
    usr_name = my_free(usr_name);
  if (!usr_name)
    usr_name = usr;
  else
    free(usr);
  return (SUCCESS);
}
