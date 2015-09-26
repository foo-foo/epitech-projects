/*
** main.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:29 2015 Anatole Menichetti
** Last update Wed Jun 17 04:41:40 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "client.h"

/*
**		Try to connect to server at addr, on port.
*/
static int	connect_to_server(char *addr, int const port)
{
  int		fd;
  t_proto	*p;
  t_sin		sin;
  t_slen	len;

  len = sizeof(t_sin);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(addr);
  if (!(p = getprotobyname(PROTONAME)))
    return (-msg_error(EPROTONAME, 0, 1));
  if ((fd = socket(AF_INET, SOCK_STREAM, p->p_proto)) == -1)
    return (-msg_error(ESOCKET, 0, 1));
  if (connect(fd, (const struct sockaddr *)&sin, len) == -1)
    return (-msg_error(ECONNECT, 0, 1));
  if (fd != -1)
    putstr("\033[32mzappy client: connection to server etablished.\n\033[0m");
  return (fd);
}

/*
**		Tabs used to recognize options.
*/
static void	init_options_tabs(char *options[3], char options_ids[3][3])
{
  options[TEAM_NAME] = NULL;
  options[PORT] = NULL;
  options[SERVER_ADDR] = NULL;
  strcpy(options_ids[TEAM_NAME], "-n");
  strcpy(options_ids[PORT], "-p");
  strcpy(options_ids[SERVER_ADDR], "-h");
}

/*
**		Parse parameters to get client options.
*/
static int	getOptions(int const ac, char **av, char *options[3])
{
  int		i;
  int		current;
  char		options_ids[3][3];

  i = 1;
  init_options_tabs(options, options_ids);
  while (i < ac)
    {
      current = 0;
      while (current < 3 && strcmp(av[i], options_ids[current]))
	current += 1;
      if (current == 3)
	return (msg_error(UNKNOWN_OPTION, av[i], 0));
      if (options[current])
	return (msg_error(REDEFINED_OPTION, av[i], 0));
      if ((current == PORT && !str_is_num(av[i + 1])) ||
	  (current == SERVER_ADDR && !str_is_float(av[i + 1])))
	return (msg_error(WRONG_SYNTAX_OPTION, av[i], 0));
      options[current] = av[i + 1];
      i += 2;
    }
  return (EXIT_SUCCESS);
}

/*
**		Get options then connect to server and launch client.
*/
int		main(int ac, char **av)
{
  int		fd;
  int		ret;
  char		*options[3];

  if (ac != 5 && ac != 7)
    return (msg_error(EUSAGE, 0, 0));
  if (getOptions(ac, av, options) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (!options[TEAM_NAME] || !options[PORT])
    return (msg_error(EUSAGE, 0, 1));
  if (!options[SERVER_ADDR])
    options[SERVER_ADDR] = LOCALHOST;
  fd = connect_to_server(options[SERVER_ADDR], atoi(options[PORT]));
  if (fd < 0)
    return (EXIT_FAILURE);
  ret = launch_client(fd, options[TEAM_NAME]);
  if (close(fd) == -1)
    return (msg_error(ECLOSE, 0, 1));
  return (ret);
}
