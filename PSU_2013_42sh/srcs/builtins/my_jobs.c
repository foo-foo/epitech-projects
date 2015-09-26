/*
** my_jobs.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri May 16 01:36:29 2014 menich_a
** Last update Sun May 25 21:41:14 2014 menich_a
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mysh.h"
#include "my.h"

int		add_one_job(t_job **list, int pid)
{
  t_job		*elem;
  t_job		*ptr;
  char		*cmd;

  if ((cmd = get_job_cmd(pid)) == NULL)
    if ((cmd = my_strdup("")) == NULL)
      return (msg_error("mysh: error: malloc failed.\n"));
  ptr = *list;
  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (msg_error("mysh: error: malloc failed.\n"));
  elem->cmd = cmd;
  elem->pid = pid;
  if (ptr == NULL)
    {
      elem->next = *list;
      *list = elem;
      return (0);
    }
  while (ptr->next)
    ptr = ptr->next;
  ptr->next = elem;
  elem->next = NULL;
  return (0);
}

int		remove_one_job(t_job **list, int pid)
{
  t_job		*ptr;
  t_job		*to_rm;

  ptr = *list;
  to_rm = *list;
  if (ptr->pid == pid)
    {
      ptr = ptr->next;
      *list = ptr;
      free(to_rm);
      return (0);
    }
  while (to_rm->next && to_rm->next->pid != pid)
    to_rm = to_rm->next;
  if (to_rm->next == NULL)
    return (1);
  ptr = to_rm;
  to_rm = to_rm->next;
  ptr->next = to_rm->next;
  free(to_rm);
  return (0);
}

char		*get_job_cmd(int pid)
{
  char		*path;
  char		*job_pid;
  int		fd;

  if ((job_pid = my_nbr_to_str(pid)) == NULL)
    return (NULL);
  path = my_str_catdup("/proc/", job_pid);
  if (path == NULL)
    return (NULL);
  free(job_pid);
  job_pid = my_str_catdup(path, "/cmdline");
  free(path);
  if ((path = job_pid) == NULL)
    return (NULL);
  if ((fd = open(path, O_RDONLY)) < 0)
    return (NULL);
  free(path);
  if ((path = fget_next_line(fd)) == NULL)
    return (NULL);
  while ((job_pid = fget_next_line(fd)) != NULL)
    free(job_pid);
  if (close(fd) < 0)
    return (NULL);
  return (path);
}

char		**my_jobs(char **cmd, char **env)
{
  t_job		*jobs;
  int		i;

  i = 1;
  (void)cmd;
  jobs = save_pid(-1, 1);
  if (jobs == NULL + 1)
    return (NULL);
  while (jobs)
    {
      my_putstr("[");
      my_put_nbr(i);
      my_putstr("]\tStopped\t\t");
      my_putstr(jobs->cmd);
      my_putstr("\n");
      jobs = jobs->next;
      i = i + 1;
    }
  return (env);
}
