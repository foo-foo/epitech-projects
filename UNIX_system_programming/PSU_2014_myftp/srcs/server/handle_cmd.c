/*
** handle_cmd.c for handle_cmd in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 17:57:16 2015 Anatole Menichetti
** Last update Sat Mar 28 17:49:08 2015 Anatole Menichetti
*/

#include <string.h>
#include <stdlib.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

int	is_write_cmd(char *buff, char *cmd)
{
  int	s;

  s = strlen(cmd);
  if (strlen(buff) < strlen(cmd))
    return (FAILURE);
  if (strncmp(buff, cmd, s))
    return (FAILURE);
  if ((buff[s] != '\r' || buff[s + 1] != '\n') &&
      buff[s] != ' ' && buff[s] != '\t')
    return (FAILURE);
  s = strlen(buff) - 1;
  buff[s - 1] = '\n';
  buff[s] = '\0';
  return (SUCCESS);
}

void	complete_init_cmd_tab(t_cmd cmd_tab[NBR_CMD])
{
  cmd_tab[10].name = "MKD";
  cmd_tab[10].fptr = &my_mkd;
  cmd_tab[11].name = "NLST";
  cmd_tab[11].fptr = &my_nls;
  cmd_tab[12].name = "NOOP";
  cmd_tab[12].fptr = &my_noop;
  cmd_tab[13].name = "RNFR";
  cmd_tab[13].fptr = &my_rnfr;
  cmd_tab[14].name = "RNTO";
  cmd_tab[14].fptr = &my_rnto;
  cmd_tab[15].name = "STOU";
  cmd_tab[15].fptr = &my_stou;
}

void	init_cmd_tab(t_cmd cmd_tab[NBR_CMD])
{
  cmd_tab[0].name = "LIST";
  cmd_tab[0].fptr = &my_ls;
  cmd_tab[1].name = "PWD";
  cmd_tab[1].fptr = &my_pwd;
  cmd_tab[2].name = "CWD";
  cmd_tab[2].fptr = &my_cd;
  cmd_tab[3].name = "USER";
  cmd_tab[3].fptr = &my_user;
  cmd_tab[4].name = "STOR";
  cmd_tab[4].fptr = &my_put;
  cmd_tab[5].name = "RETR";
  cmd_tab[5].fptr = &my_get;
  cmd_tab[6].name = "ACCT";
  cmd_tab[6].fptr = &my_acct;
  cmd_tab[7].name = "APPE";
  cmd_tab[7].fptr = &my_appe;
  cmd_tab[8].name = "DELE";
  cmd_tab[8].fptr = &my_dele;
  cmd_tab[9].name = "RMD";
  cmd_tab[9].fptr = &my_rmd;
  complete_init_cmd_tab(cmd_tab);
}

char	*launch_cmd(int fd, FILE *fp, char *cmd, char **pwds)
{
  t_cmd	cmd_tab[NBR_CMD];
  char	*ret;
  int	i;

  i = 0;
  ret = NULL;
  if (cmd[0] == '\n')
    return (cmd);
  init_cmd_tab(cmd_tab);
  while (i < NBR_CMD && !is_write_cmd(cmd, cmd_tab[i].name))
    i += 1;
  if (i < NBR_CMD)
    ret = cmd_tab[i].fptr(fd, fp, cmd + strlen(cmd_tab[i].name), pwds);
  else
    if (!(ret = strdup(ENOTIMP)))
      return (alloc_err(0, fd, fp, 0));
  free(cmd);
  return (ret);
}

int	handle_cmd(int fd, FILE *fp, char *cmd, char **pwds)
{
  int	ret;

  cmd = launch_cmd(fd, fp, cmd, pwds);
  if (!cmd)
    return (FAILURE);
  ret = fputstr(fd, cmd);
  free(cmd);
  if (ret == -1)
    return (my_perror(EWRITE, FAILURE, 0, fd));
  return (SUCCESS);
}
