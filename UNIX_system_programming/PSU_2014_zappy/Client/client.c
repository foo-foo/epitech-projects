/*
** client.c for  in /home/menich_a/rendu/zappy/client_zappy
** 
** Made by Anatole Menichetti
** Login   <menich_a@epitech.net>
** 
** Started on  Sun Jun 14 23:44:03 2015 Anatole Menichetti
** Last update Wed Jun 24 02:28:11 2015 Anatole Menichetti
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*
**		Get the server message.
**		If it's an extern_action => launch specific action.
**		Else => execute defined action.
*/
static int	update_data(int const fd, t_player *p)
{
  char		*data;
  int		ret;

  if (!(data = get_next_line(fd)))
    return (-msg_error(EALLOC, 0, 1));
  if (data[strlen(data) - 1] == '\n')
    data[strlen(data) - 1] = '\0';
  if (!strcmp(data, "mort"))
    ret = EXIT_SUCCESS;
  else if (strlen(data) > 9 && !strncmp(data, "message ", 8))
    ret = received_msg(p, data);
  else if (strlen(data) > 14 && !strncmp(data, "deplacement: ", 13))
    ret = have_been_expulsed(p, data);
  else if (strlen(data) > 14 && !strncmp(data, "niveau actuel : ", 16))
    ret = elevation_ended(p, data);
  else
    ret = execute_action(fd, p, data);
  free(data);
  return (ret);
}

/*
**		Contact server for basic informations.
**		Init player.
**		Then each time server contact client => update_data.
*/
int		launch_client(int const fd, char *team_name)
{
  size_t	server_size[2];
  t_player	player;
  int		connect_nbr;
  int		ret;

  player.team_name = team_name;
  if (contact_server(fd, team_name,
		     server_size, &connect_nbr) == EXIT_FAILURE ||
      !init_player(fd, &player, connect_nbr))
    return (EXIT_FAILURE);
  while ((ret = update_data(fd, &player)) > 0);
  return (ret);
}
