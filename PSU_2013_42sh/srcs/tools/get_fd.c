/*
** get_fd.c for  in /home/menich_a/rendu/PSU_2013_42sh
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun May 25 23:34:59 2014 menich_a
** Last update Fri May 30 19:05:00 2014 menich_a
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "alias.h"
#include "mysh.h"
#include "my.h"

int		get_fd(int save_in, int save_out, int action)
{
  static int	fd_in = 0;
  static int	fd_out = 1;

  if (action == 0)
    return (fd_in);
  if (action == 1)
    return (fd_out);
  if (save_out >= 0)
    {
      if (fd_out != 1 && close(fd_out) == -1)
        return (my_warn("close error:", fd_out));
      fd_out = save_out;
    }
  if (save_in >= 0)
    {
      if (fd_in != 0 && close(fd_in) == -1)
        return (my_warn("close error:", fd_in));
      fd_in = save_in;
    }
  return (0);
}
