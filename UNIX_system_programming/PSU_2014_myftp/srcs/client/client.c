/*
** client.c for client in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 18:21:23 2015 Anatole Menichetti
** Last update Sat Mar 28 18:20:24 2015 Anatole Menichetti
*/

#include <string.h>
#include "../../includes/myftp.h"
#include "../../includes/client.h"
#include "../../includes/my.h"

int		init_client(int fd, FILE *fps[2], t_cmd cmd_tab[6])
{
  char		*buff;
  size_t	len;

  buff = 0;
  len = 0;
  if (!(fps[0] = fdopen(fd, "r+")) || !(fps[1] = fdopen(0, "r")))
    return (my_perror(EOPEN, FAILURE, fd, 0));
  init_cmd_tab(cmd_tab);
  if (getline(&buff, &len, fps[0]) == -1)
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  putcolor(buff);
  return (SUCCESS);
}

int		launch_client(int fd, char *buff, size_t len, char **pwds)
{
  FILE		*fps[2];
  t_cmd		cmd_tab[6];
  int		i;

  if (!init_client(fd, fps, cmd_tab))
    return (FAILURE);
  while (display_prompt(fd, fps[0]) &&
	 getline(&buff, &len, fps[1]) >= 0 && strcmp(buff, "quit\n"))
    {
      if ((i = is_transfert_cmd(cmd_tab, &buff)) == -1)
	if (!handle_cmd(fd, fps, buff, pwds))
	  return (FAILURE);
      if (i >= 0)
	if (!cmd_tab[i].fptr(fd, fps[0], buff, 0))
	  return (FAILURE);
      buff = NULL;
    }
  if (fputstr(fd, "quit\r\n") == -1 || !buff ||
      strcmp(buff, "quit\n") || my_free(buff))
    return (my_perror(EUNAVAILABLE, FAILURE, fd, 0));
  if (fclose(fps[0]) == -1 || fclose(fps[1]) == -1)
    return (my_perror(ECLOSE, FAILURE, fd, 0));
  return (SUCCESS);
}
