/*
** my_get.c for $ in /home/menich_a/rendu/PSU_2013_42sh/srcs/my
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sun May 25 23:33:03 2014 menich_a
** Last update Sun Jun  1 20:13:29 2014 menich_a
*/

#include <unistd.h>
#include <stdlib.h>
#include "alias.h"
#include "mysh.h"
#include "my.h"

/*
**		Returns a cmd tab containing only next pipe cmd.
*/
int		get_next_pipe_cmd(char **cmd, char **res, int *index1, int *index2)
{
  int		i;
  int		j;

  i = *index2;
  j = 0;
  while (cmd[i] && (cmd[i][0] != PIPE || cmd[i][1] != '\0'))
    if ((res[j++] = my_strdup(cmd[i++])) == NULL)
      return (-1);
  res[j] = NULL;
  if (cmd[i])
    i = i + 1;
  *index1 = i;
  *index2 = j;
  return (0);
}

/*
**		In res: copy cmd from cmd[i] to cmd[i] = '|'
**		Returns a clean and redirected version of res.
*/
char		**get_next_cmd(char **cmd, char **env, int check)
{
  static int	i = 0;
  int		j;
  char		**res;

  j = 0;
  if (check == -42 && !(i = 0))
    return (NULL);
  while (j < i && cmd[j])
    j = j + 1;
  if (validity_check(cmd, j, i))
    return (NULL);
  if (check == 1)
    return (cmd);
  i = i - 1;
  while (cmd[++i])
    if (cmd[i][0] == PIPE && cmd[i][1] == '\0')
      break;
  if ((res = malloc(sizeof(*res) * (i + 1))) == NULL)
    return (NULL);
  if (get_next_pipe_cmd(cmd, res, &i, &j))
    return (NULL);
  res = check_redirections(res, env);
  if (cmd[i] == NULL)
    i = 0;
  return (res);
}


/*
**		Searchs the cmd in each path directory or in its own path if specified.
**		Returns pointer on new allocated string containing cmd path.
**		If not found => returns NULL.
*/
char		*get_cmd_path(char *cmd, char **path)
{
  int		i;
  int		size;
  char		*cmd_path;

  i = 0;
  size = my_strlen(cmd);
  if (my_find_in_str(cmd, '/') >= 0 && access(cmd, F_OK) >= 0)
    return (my_strdup(cmd));
  if (path != NULL)
    while (path[i] != NULL)
      {
        if (!(cmd_path = malloc(sizeof(*cmd_path) *
				(my_strlen(path[i]) + size + 2))))
          return (msg_error_ret("mysh: error: malloc failed.\n"));
        my_strcpy(cmd_path, path[i]);
        my_strcat(cmd_path, "/");
        my_strcat(cmd_path, cmd);
        if (access(cmd_path, F_OK) != -1)
          return (cmd_path);
        free(cmd_path);
        i = i + 1;
      }
  msg_error(cmd);
  msg_error(": command not found\n");
  return (NULL);
}

int		get_pipes_process(int *pipes_pids, int *nbr_pipes, int pid)
{
  int		i;

  i = 0;
  while (pipes_pids[i] != -1)
    i = i + 1;
  if (pid == -42)
    i = i - 1;
  if (i == *nbr_pipes)
    {
      *nbr_pipes = *nbr_pipes - 1;
      if (pid == -42)
	{
	  pid = pipes_pids[i];
	  pipes_pids[i] = -1;
	}
      return (pid);
    }
  pipes_pids[i] = pid;
  pipes_pids[i + 1] = -1;
  return (-42);
}

/*
**		Creates a pid tab while there is some pipes to execute.
**		When every pipe process pid is stocked:
**			=> Returns one by one each pipe process pid.
**			=> Father process wait for sons in order properly.
*/
int		get_pipes(int pipes, int pid)
{
  static int	nbr_pipes = 0;
  static int	*pipes_pids = NULL;

  if (pipes == -42 && pid == -42)
    {
      get_next_cmd(0, 0, -42);
      if (pipes_pids)
	free(pipes_pids);
      pipes_pids = NULL;
      return (nbr_pipes = 0);
    }
  if (pipes >= 0)
    {
      nbr_pipes = pipes;
      if (pipes_pids)
	free(pipes_pids);
      pipes_pids = malloc(sizeof(*pipes_pids) * (nbr_pipes + 1));
      if (!pipes_pids)
	return (msg_error("mysh: error: malloc failed.\n"));
      pipes_pids[0] = -1;
      return (0);
    }
  if (nbr_pipes < 0)
    return (-2);
  return (get_pipes_process(pipes_pids, &nbr_pipes, pid));
}