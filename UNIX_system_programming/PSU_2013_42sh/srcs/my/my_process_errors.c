/*
** my_process_errors.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Wed May 21 13:42:50 2014 menich_a
** Last update Sun May 25 22:12:33 2014 menich_a
*/

#include <sys/wait.h>
#include "my.h"

int	my_process_errors_signal_ret(int status)
{
  if (status == SIGILL)
    msg_error("Illegal Instruction\n");
  if (status == SIGFPE)
    msg_error("Floating point exception\n");
  if (status == SIGSEGV)
    msg_error("Segmentation fault\n");
  if (status == SIGBUS)
    msg_error("Bus error\n");
  if (status == SIGSYS)
    msg_error("Bad argument to routine\n");
  if (status == SIGTRAP)
    msg_error("Trace/breakpoint trap\n");
  if (status == SIGXCPU)
    msg_error("CPU time limit exceeded\n");
  if (status == SIGXFSZ)
    msg_error("File size limit exceeded\n");
  return (1);
}

int	my_process_errors(int status)
{
  if (WIFEXITED(status))
    {
      if (WEXITSTATUS(status) != 0)
	return (1);
      else
	return (0);
    }
  if (WIFSIGNALED(status))
    status = WTERMSIG(status);
  else
    return (0);
  if (status == SIGPIPE)
    return (0);
  return (my_process_errors_signal_ret(status));
}
