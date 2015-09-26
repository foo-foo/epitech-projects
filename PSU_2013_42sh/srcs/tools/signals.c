/*
** signals.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May 15 19:53:47 2014 menich_a
** Last update Sat May 31 18:41:08 2014 menich_a
*/

#include <signal.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

/*
**		If a SIGTSTP is received (CTRL+Z)
**		=> send the signal to current process.
**		=> add process to suspend jobs list.
*/
void		my_sigstop(int signal)
{
  t_job		*jobs;
  int		i;

  i = 1;
  if (signal == SIGTSTP)
    {
      if ((jobs = save_pid(0, 1)) && jobs != NULL + 1 && jobs != NULL + 2)
	  {
	    while (jobs->next && i++)
	      jobs = jobs->next;
	    if (jobs->pid >= 0)
	      {
		if (kill(jobs->pid, SIGTSTP) == -1)
		  msg_error("mysh: kill error.\n");
		my_putstr("\n[");
		my_put_nbr(i);
		my_putstr("]\tStopped\t\t");
		my_putstr(jobs->cmd);
		my_putstr("\n");
		save_pid(-1, 0);
	      }
	  }
    }
}

/*
**		Used to restore SIGINT by default.
*/
int		launch_exiting(int exit)
{
  static int	status = 0;

  if (exit)
    status = exit;
  return (status);
}

/*
**		If a SIGINT is received, it will kill current process.
**		If no current process is executing, it will re-display prompt.
*/
void		my_sigint(int signal)
{
  if (signal == SIGINT)
    if (save_pid(0, 3) == NULL + 2)
      {
	my_putstr("^C\n");
	display_prompt(0, 0, 0);
      }
}

/*
**		Restore default SIGINT comportment.
*/
void		disable_sigint(int signal)
{
  if (signal == SIGINT)
    launch_exiting(1);
}
