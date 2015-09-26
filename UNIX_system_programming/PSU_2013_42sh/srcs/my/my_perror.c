/*
** my_perror.c for mysh in /home/menich_a/rendu/PSU_2013_minishell2/srcs/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Mar  7 20:12:42 2014 menich_a
** Last update Sat May 24 00:45:08 2014 menich_a
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

/*
**	Used by `cd' to verify permissions on an invalid given path.
*/
int	my_perror(char *path, int red_error)
{
  my_putstr("mysh: ");
  if (red_error == 1)
    msg_error("syntax error near unexpected token `newline'\n");
  if (red_error == -1)
    msg_error("open error: last command failed\n");
  if (red_error > 2)
    msg_error("close error: last command failed\n");
  if (red_error == -2)
    msg_error("redirection error: last command failed\n");
  if (path == NULL && red_error == 0)
    msg_error("invalid path\n");
  if (red_error != 0 || path == NULL)
    return (-1);
  msg_error(path);
  if (access(path, F_OK) == -1)
    msg_error(": No such file or directory\n");
  else if (access(path, R_OK) == -1)
    msg_error(": Read permission denied\n");
  else if (access(path, W_OK) == -1)
    msg_error(": Write permission denied\n");
  else if (access(path, X_OK) == -1)
    msg_error(": Execute permission denied\n");
  else
    msg_error(": Permission denied\n");
  return (-1);
}
