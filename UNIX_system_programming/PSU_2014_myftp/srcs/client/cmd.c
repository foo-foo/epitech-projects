/*
** cmd.c for myftp in /home/menich_a/rendu/PSU_2014_myftp/srcs/client
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 28 18:11:11 2015 Anatole Menichetti
** Last update Sun Mar 29 22:15:59 2015 Anatole Menichetti
*/

#include <stdlib.h>
#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

int		launch_specific_cmd(int fd, FILE *fps[2], char *buff, char **pwds)
{
  char		*ret;

  ret = NULL + 1;
  if (!my_cmdcmp(buff, "HELP") || !my_cmdcmp(buff, "help"))
    ret = my_help(buff + 4);
  if (!my_cmdcmp(buff, "LLIST"))
    ret = my_lls(fd, fps[0], buff + 5, pwds);
  if (!my_cmdcmp(buff, "LPWD"))
    ret = my_lpwd(fd, fps[0], buff + 4, pwds);
  if (!my_cmdcmp(buff, "LCWD"))
    ret = my_lcd(fd, fps[0], buff + 4, pwds);
  if ((ret != NULL + 1 && !strcpy(buff, "\n")) ||
      rfputstr(fd, buff) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (ret == NULL + 1)
    {
      if (my_cmdcmp(buff, "USER") || my_free(buff))
        return (SUCCESS);
      if ((fd = my_user(fd, fps[0], fps[1], 0)) == SUCCESS)
        return (-1);
      return (fd);
    }
  if (!ret || !putstr(ret) || my_free(ret))
    return (FAILURE);
  return (SUCCESS);
}

int		handle_cmd(int fd, FILE *fps[2], char *buff, char **pwds)
{
  size_t	len;
  int		ret;

  len = 0;
  if ((ret = launch_specific_cmd(fd, fps, buff, pwds)) <= 0)
    return (ret);
  if (buff[0] && (buff[0] != '\n' || buff[1]))
    {
      buff = my_free(buff);
      while ((ret = getline(&buff, &len, fps[0])) >= 0 && buff[ret - 2] != '\r')
        {
          if (!strncmp(buff, "150 File status okay", 20))
            buff[strlen(buff) - 2] = '\r';
          putcolor(buff);
        }
      putcolor(buff);
      free(buff);
      return (SUCCESS);
    }
  buff = my_free(buff);
  if (getline(&buff, &len, fps[0]) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  free(buff);
  return (SUCCESS);
}

void		init_cmd_tab(t_cmd cmd_tab[6])
{
  cmd_tab[0].name = "STOR";
  cmd_tab[0].fptr = &my_put;
  cmd_tab[1].name = "STOU";
  cmd_tab[1].fptr = &my_put;
  cmd_tab[2].name = "APPE";
  cmd_tab[2].fptr = &my_put;
  cmd_tab[3].name = "RETR";
  cmd_tab[3].fptr = &my_get;
  cmd_tab[4].name = "MSTOR";
  cmd_tab[4].fptr = &my_mput;
  cmd_tab[5].name = "MRETR";
  cmd_tab[5].fptr = &my_mget;
}

int		is_transfert_cmd(t_cmd cmd_tab[6], char **buff)
{
  int		i;
  char		*cmd;
  char		*tmp;

  i = 0;
  cmd = *buff;
  while (cmd[i] == ' ' || cmd[i] == '\t')
    i += 1;
  cmd = strdup(cmd + i);
  if (cmd)
    {
      tmp = *buff;
      free(tmp);
      *buff = cmd;
    }
  i = 0;
  while (i < 6 && (strlen(cmd) <= strlen(cmd_tab[i].name) ||
                   strncmp(cmd_tab[i].name, cmd, strlen(cmd_tab[i].name))))
    i += 1;
  if (i < 6 && strlen(cmd) > strlen(cmd_tab[i].name) &&
      (cmd[strlen(cmd_tab[i].name)] == ' ' ||
       cmd[strlen(cmd_tab[i].name)] == '\t' ||
       cmd[strlen(cmd_tab[i].name)] == '\n'))
    return (i);
  return (-1);
}
