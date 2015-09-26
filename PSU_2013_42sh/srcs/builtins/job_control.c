/*
** job_control.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May  8 14:09:44 2014 menich_a
** Last update Fri May 30 19:34:20 2014 menich_a
*/

#include <sys/wait.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

t_job			*save_pid(int pid, int action)
{
  static int		son_pid = -1;
  static t_job		*first_job = NULL;

  if (pid == -1 && action)
    return (first_job);
  if (action == 0)
    son_pid = pid;
  if (action == 1)
    if (add_one_job(&first_job, son_pid))
      return (NULL + 1);
  if (action == 2)
    if (remove_one_job(&first_job, son_pid = pid))
      return (NULL + 1);
  if (action < 0 || action > 2)
    {
      if (son_pid < 0)
	return (NULL + 2);
      if (kill(son_pid, SIGINT) == -1)
	return (NULL + 1);
      son_pid = -1;
    }
  return (first_job);
}

char			**my_fg(char **cmd, char **env)
{
  int			i;
  int			status;
  int			job_id;
  t_job			*jobs;

  i = 0;
  job_id = 0;
  if (cmd[1] && (job_id = my_getnbr(cmd[1])) <= 0)
    return (msg_error_return("mysh: fg: invalid job id.\n", NULL + 1));
  if ((jobs = save_pid(-1, 1)) == NULL)
    return (msg_error_return("mysh: fg: no current job.\n", NULL + 1));
  if (jobs == NULL + 1)
    return (NULL);
  while (jobs && (job_id || jobs->next) && ++i != job_id)
    jobs = jobs->next;
  if (!jobs)
    return (msg_error_return("mysh: fg: no such job.\n", NULL + 1));
  job_id = jobs->pid;
  if (save_pid(job_id, 2) == NULL + 1)
    return (NULL);
  if (kill(job_id, SIGCONT) < 0)
    return (msg_error_return("mysh: kill error.\n", NULL));
  if (waitpid(-1, &status, WUNTRACED) == -1)
    return (msg_error_return("mysh: wait error.\n", NULL));
  return (env);
}
