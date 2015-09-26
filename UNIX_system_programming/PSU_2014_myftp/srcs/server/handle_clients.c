/*
** handle_clients.c for handle_clients in /Users/amenichetti/Documents/Developpement/Epitech/PSU_2014_myftp/srcs/server
** 
** Made by Anatole Menichetti
** Login   <amenichetti@MacBook-Pro-de-Anatole.local>
** 
** Started on  Thu Mar 19 18:03:09 2015 Anatole Menichetti
** Last update Fri Mar 27 18:57:08 2015 Anatole Menichetti
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "../../includes/myftp.h"
#include "../../includes/server.h"
#include "../../includes/errors.h"
#include "../../includes/my.h"

int		display_prompt(int fd, char **pwds)
{
  char		*prompt;
  int		i;
  int		s;

  if (pwds && pwds[HOME])
    {
      s = strlen(pwds[HOME]);
      i = s - 1;
      while (--i >= 0 && pwds[HOME][i] != '/');
      if (!(prompt = malloc(sizeof(*prompt) * (strlen(EOP) + s - (i + 1)))))
	return (my_perror(EALLOC, FAILURE, 0, fd));
      strncpy(prompt, pwds[HOME] + i + 1, s - (i + 2));
      prompt[s - (i + 2)] = '\0';
      strcat(prompt, EOP);
    }
  else
    if (!(prompt = DEFAULT_PROMPT))
      return (my_perror(EALLOC, FAILURE, 0, fd));
  if (fputstr(fd, prompt) == -1)
    return (my_perror(EWRITE, FAILURE, 0, fd));
  free(prompt);
  return (SUCCESS);
}

int		handle_client(int fd, char **pwds)
{
  char		*buff;
  size_t	len;
  char		*cmd;
  FILE		*fp;

  len = 0;
  if (!(fp = fdopen(fd, "r+")))
    return (my_perror(EOPEN, FAILURE, 0, fd));
  fputstr(fd, "220 Service ready for new user.\r\n");
  if (!(buff = my_user(fd, fp, "Anonymous\n", pwds)))
    return (FAILURE);
  buff = my_free(buff);
  while (getline(&buff, &len, fp) >= 0 &&
	 strcmp(buff, "quit\r\n"))
    {
      if (!(cmd = strdup(buff)))
        return (my_perror(EALLOC, FAILURE, 0, fd));
      if (!handle_cmd(fd, fp, cmd, pwds))
	return (FAILURE);
    }
  if (!buff || strcmp(buff, "quit\n") || my_free(buff))
    return (FAILURE);
  if (fclose(fp) == -1)
    return (my_perror(ECCLOSE, FAILURE, fd, 0));
  return (SUCCESS);
}

int		handle_clients(int fd, char **pwds)
{
  pid_t		pid;
  int		fd_client;

  pid = 1;
  if (pwds && !get_conf(pwds[ROOT], 0))
    return (my_perror(EALLOC, FAILURE, 0, fd));
  while (pid != CHILD)
    {
      if ((fd_client = accept(fd, NULL, NULL)) == -1)
	return (my_perror(EACCEPT, EXIT_FAILURE, fd, 0));
      if ((pid = fork()) == -1)
	return (my_perror(EFORK, FAILURE, fd, fd_client));
      if (pid == CHILD)
	{
	  if (close(fd) == -1)
	    return (my_perror(ESCLOSE, FAILURE, 0, fd_client));
	  if (!handle_client(fd_client, pwds))
	    return (FAILURE);
	}
      else
	if (close(fd_client) == -1)
	  return (my_perror(ECCLOSE, FAILURE, fd, 0));
    }
  return (SUCCESS);
}
