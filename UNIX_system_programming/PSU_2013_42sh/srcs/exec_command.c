/*
** commands.c for minishell in /home/menich_a/rendu/PSU_2013_minishell1/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Dec 17 18:05:42 2013 menich_a
** Last update Sun Jun  1 20:18:29 2014 menich_a
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

/*
**		add the --color option to ls / grep.
*/
char		**add_color_option(char **cmd)
{
  int		i;
  char		**new_cmd;

  i = 1;
  if (check_if_color_cmd(cmd))
    return (cmd);
  new_cmd = malloc(sizeof(*new_cmd) * (my_tablen(cmd) + 2));
  if (!new_cmd)
    exit(msg_error("mysh: error: malloc failed.\n"));
  new_cmd[0] = cmd[0];
  if ((new_cmd[1] = my_strdup("--color")) == NULL)
    exit(-1);
  while (cmd[i])
    {
      new_cmd[i + 1] = cmd[i];
      i = i + 1;
    }
  new_cmd[i + 1] = NULL;
  free(cmd);
  return (new_cmd);
}

/*
**		Used by son process to close pipe fd[0] when not needed.
*/
int		save_fd(int fd)
{
  static int	save = -1;

  if (fd != -42)
    save = fd;
  return (save);
}

/*
**		Creates a pipe. Mark the redirection on the pipe output.
**		Then launch next pipe cmd (launch_appropriate_cmd).
**		Mark the redirection on the pipe input (it will affect next cmd).
*/
char		**exec_pipe_cmd(char **cmd, char **env)
{
  int		fd[2];

  if (pipe(fd) == -1)
    return (my_warn_ret("pipe error"));
  save_fd(fd[0]);
  get_fd(-1, fd[1], 2);
  env = launch_appropriate_cmd(cmd, env);
  get_fd(fd[0], -1, 2);
  return (env);
}

/*
**		Son process created to execute the current cmd.
**		Init duplications depending to pipes / redirection previsously checked.
**		If cmd is ls or grep, add the color.
**		execute cmd if valid.
*/
void		execute_son_process(char **cmd, char **env, char *cmd_path, int p_fd)
{
  int		fd_in;
  int		fd_out;


  if ((fd_in = get_fd(0, 0, 0)) != 0)
    {
      if (dup2(fd_in, 0) == FAILURE)
	exit(my_warn("duplication error:", fd_in));
      if (close(fd_in) == FAILURE)
	exit(my_warn("close error:", fd_in));
    }
  if ((fd_out = get_fd(1, 1, 1)) != 1)
    {
      if (dup2(fd_out, 1) == FAILURE)
	exit(my_warn("duplication error:", fd_out));
      if (close(fd_out) == FAILURE)
	exit(my_warn("close error:", fd_out));
      if (p_fd >= 0 && close(p_fd) == FAILURE)
	exit(my_warn("close error:", p_fd));
    }
  else
    cmd = add_color_option(cmd);
  exit(execve(cmd_path, cmd, env));
}

/*
**		Gets the path from the env.
**		If the cmd is found in the path:
**			=> Creates a son process which will execute cmd.
**		Saves the son pid for job control.
**		Restores input fd and output fd.
**		Waits for son process end (depending on pipes).
**		Removes son pid from save.
**		Returns son return value, or defined value for signals.
*/
int		launch_exec_cmd(char **cmd, char **env)
{
  char		**path;
  char		*cmd_path;
  int		status;
  pid_t		pid;

  path = my_path_to_tab(my_find_in_env(env, "PATH"));
  if ((cmd_path = get_cmd_path(cmd[0], path)) == NULL)
    if (!get_fd(0, 1, 2) && !get_pipes(-42, -42) &&
	!my_free_tab(cmd) && !my_free_tab(path))
      return (1);
  if ((pid = fork()) == FAILURE)
    return (msg_error("mysh: fork error.\n"));
  if (pid == CHILD_PID || save_fd(-1) == -42)
    execute_son_process(cmd, env, cmd_path, save_fd(-42));
  save_pid(pid, 0);
  get_fd(0, 1, 2);
  while (pid != FAILURE && (pid = get_pipes(-1, pid)) >= 0)
    if (waitpid(pid, &status, WUNTRACED) == FAILURE || !(pid = -42))
      return (msg_error("mysh: wait error.\n"));
  if (pid == FAILURE)
    return (FAILURE);
  save_pid(-1, 0);
  if (!my_free(cmd_path) && !my_free_tab(path) && !my_free_tab(cmd))
    return (my_process_errors(status));
  return (-1);
}
