/*
** redirections.c for mysh in /home/menich_a/rendu/PSU_2013_minishell2/sources
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Feb 21 12:49:07 2014 menich_a
** Last update Fri May 30 19:03:40 2014 menich_a
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

/*
**	Init "<<" redirection.
*/
int	double_stdin_redirection(char *delimitor, char **env)
{
  char	*str;
  int	fd[2];

  if (pipe(fd) == FAILURE)
    return (msg_error("mysh: pipe error.\n"));
  my_putstr("> ");
  while ((str = get_next_line(0, env)) && my_strcmp(str, delimitor))
    {
      write(fd[1], str, my_strlen(str));
      write(fd[1], "\n", 1);
      free(str);
      my_putstr("> ");
    }
  if (close(fd[1]) == FAILURE)
    return (my_warn(NULL, fd[1]));
  return (fd[0]);
}

/*
**	Init redirections. If "<<" => double_stdin_red
*/
int	launch_redirection(char *redirection, char *file, char **env)
{
  int	fd;

  fd = FAILURE;
  if (redirection[0] == SUP)
    {
      if (redirection[1] == '\0')
        fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
      if (redirection[1] == SUP && !redirection[2])
        fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
    }
  else
    {
      if (redirection[1] == '\0')
        fd = open(file, O_RDONLY);
      if (redirection[1] == INF && !redirection[2])
        if ((fd = double_stdin_redirection(file, env)) == FAILURE)
	  return (FAILURE);
    }
  if (fd == FAILURE)
    my_warn(NULL, fd);
  return (fd);
}

/*
**	Launch init of appropriate redirection.
*/
int	init_redirection(char **cmd, char **env, int old_fd, int new_fd)
{
  if (cmd[1] == NULL)
    return (my_perror(NULL, 1));
  if (cmd[0][0] == INF && !cmd[0][1] && access(cmd[1], F_OK) == FAILURE)
    return (my_warn(cmd[1], -42));
  if (cmd[0][0] == SUP)
    new_fd = STDOUT_FILENO;
  else
    new_fd = STDIN_FILENO;
  old_fd = launch_redirection(cmd[0], cmd[1], env);
  if (old_fd == FAILURE)
    return (FAILURE);
  if (new_fd == 0)
    get_fd(old_fd, -1, 2);
  else
    get_fd(-1, old_fd, 2);
  return (SUCCESS);
}

/*
**	Creates à new cmd with no redirections.
*/
char	**clean_redirected_cmd(char **cmd, int size)
{
  int	i;
  int	j;
  char	**clean_cmd;

  i = 0;
  j = 0;
  clean_cmd = malloc(sizeof(*clean_cmd) * (size + 1));
  if (clean_cmd == NULL)
    return (NULL);
  while (cmd[i] != NULL)
    {
      if (cmd[i][0] == INF || cmd[i][0] == SUP)
        i = i + 2;
      else
        {
          clean_cmd[j] = my_strdup(cmd[i]);
	  if (clean_cmd[j] == NULL)
	    return (NULL);
          i = i + 1;
          j = j + 1;
        }
    }
  my_free_tab(cmd);
  clean_cmd[j] = NULL;
  return (clean_cmd);
}

/*
**	Checks cmd redirections. For each redirection:
**	=> init redirection + remove redirection from cmd.
*/
char	**check_redirections(char **cmd, char **env)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (cmd[i] != NULL)
    {
      if (cmd[i][0] != INF && cmd[i][0] != SUP)
        j = j + 1;
      else
	{
	  if (init_redirection(cmd + i, env, 0, STDOUT_FILENO) == FAILURE)
	    return (NULL + 1);
          i = i + 1;
        }
      i = i + 1;
    }
  if (i != j)
    return (clean_redirected_cmd(cmd, j));
  return (cmd);
}
