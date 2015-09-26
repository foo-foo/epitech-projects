/*
** my_mget.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Mar 22 21:01:57 2015 Anatole Menichetti
** Last update Sat Mar 28 17:10:58 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

void		disp_percentage(unsigned int nb)
{
  char		c;

  write(1, "\r", 1);
  if (nb < 10)
    {
      c = nb + 48;
      write(1, &c, 1);
    }
  else if (nb == 100)
    write(1, "100", 3);
  else
    {
      c = nb / 10 + 48;
      write(1, &c, 1);
      c = nb % 10 + 48;
      write(1, &c, 1);
    }
  write(1, "%", 1);
}

int		complete_transfert(int fd, int j, char *cmd[3], size_t cpt[2])
{
  cmd[2] = NULL;
  cmd[0][cpt[0]++] = '\n';
  if (!(cmd[1] = malloc(sizeof(*cmd[1]) * (cpt[0] + 6 - j))))
    return (my_perror(EALLOC, FAILURE, fd, 0));
  if (!strncmp(cmd[0], "MRETR", 5))
    strcpy(cmd[1], "RETR ");
  else
    strcpy(cmd[1], "STOR ");
  strncat(cmd[1], cmd[0] + j, cpt[0] - j);
  return (SUCCESS);
}

int		multi_transfert(int fd, char *cmd[3], size_t cpt[2])
{
  int		j;

  while (cmd[0][cpt[0]] == ' ' || cmd[0][cpt[0]] == '\t')
    cpt[0] += 1;
  j = cpt[0];
  if (cmd[0][cpt[0]] == '\n')
    {
      if (cmd[2] == NULL + 1)
	my_perror(ESYNTAX, SUCCESS, fd, 0);
      return (-1);
    }
  while (cmd[0][cpt[0]] && cmd[0][cpt[0]] != '\n' &&
	 cmd[0][cpt[0]] != '\t' && cmd[0][cpt[0]] != ' ')
    cpt[0] += 1;
  return (complete_transfert(fd, j, cmd, cpt));
}

int		my_mget(int fd, FILE *fp, char *buff, size_t len)
{
  char		*cmd[3];
  size_t	cpt[2];
  int		ret;

  cpt[0] = 4;
  cpt[1] = len;
  cmd[0] = buff;
  cmd[1] = NULL;
  cmd[2] = NULL + 1;
  while (buff[cpt[0]])
    {
      ret = multi_transfert(fd, cmd, cpt);
      if (ret < 0)
	break;
      if (!ret || !my_get(fd, fp, cmd[1], 0))
        return (FAILURE);
    }
  if (cmd[2] != NULL + 1)
    free(cmd[2]);
  free(cmd[0]);
  return (SUCCESS);
}

int		my_mput(int fd, FILE *fp, char *buff, size_t len)
{
  char		*cmd[3];
  size_t	cpt[2];
  int		ret;

  cpt[0] = 4;
  cpt[1] = len;
  cmd[0] = buff;
  cmd[1] = NULL;
  cmd[2] = NULL + 1;
  while (buff[cpt[0]])
    {
      ret = multi_transfert(fd, cmd, cpt);
      if (ret < 0)
	break;
      if (!ret || !my_put(fd, fp, cmd[1], 0))
        return (FAILURE);
    }
  if (cmd[2] != NULL + 1)
    free(cmd[2]);
  free(cmd[0]);
  return (SUCCESS);
}
