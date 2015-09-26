/*
** read_data.c for  in /home/bencha_a/lem-in/v1.6/leo
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri Apr 25 12:52:52 2014 bencharif
** Last update Sun May  4 19:20:55 2014 menich_a
*/

#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "graph.h"

char		**get_way(char **tab)
{
  static int	i;
  static char	**way;

  if (i == 0)
    {
      way = my_tab_dup(tab);
      i++;
    }
  return (way);
}

int		get_nbr_ants(char *str)
{
  int		i;
  static int	ants;
  static int	check;

  if (str && check == 0)
    {
      i = 0;
      while (str[i] && str[i] >= '0' && str[i] <= '9')
	  i++;
      if (str[i])
	return (ants);
      ants = my_getnbr(str);
      check = 1;
    }
  return (ants);
}

int		get_data_process(char *buff, char ***tab)
{
  static int	i = 0;
  static int	j = 0;

  if (strlen(buff) >= 15 && strncmp(buff, "lem_in: error: ", 15) == 0)
    {
      my_putstr(buff);
      exit(-1);
    }
  if (buff[0] != 'P' && get_nbr_ants(buff) >= 0)
    {
      if ((tab[0][i] = strdup(buff)) == NULL)
	return (-1);
      tab[0][i + 1] = NULL;
      tab[0] = my_realloc(tab[0]);
      i++;
    }
  else
    {
      if ((tab[1][j] = strdup(buff)) == NULL)
	return (-1);
      tab[1][j + 1] = NULL;
      tab[1] = my_realloc(tab[1]);
      j++;
    }
  return (0);
}

char		**get_data(void)
{
  char		***tab;
  char		*buff;

  tab = malloc(3 * sizeof(char**));
  if (tab == NULL)
    return (NULL);
  tab[0] = malloc(2 * sizeof(char*));
  tab[1] = malloc(2 * sizeof(char*));
  tab[2] = NULL;
  if (tab[0] == NULL || tab[1] == NULL)
    return (NULL);
  while ((buff = get_next_line(0)) != NULL)
    if (get_data_process(buff, tab))
      return (NULL);
  get_way(tab[1]);
  return (tab[0]);
}

t_coord		*get_room_coord(char **tab, t_coord *coord, int i)
{
  while (tab[i] != NULL)
    {
      if (strcmp(tab[i], "##start") == 0)
	{
	  if (tab[++i] && check_space(tab[i]) == 1)
	    my_put_in_list(&coord, tab[i], 1);
	}
      else if (strcmp(tab[i], "##end") == 0)
	{
	  if (tab[++i] && check_space(tab[i]) == 1)
	    my_put_in_list(&coord, tab[i], 2);
	}
      else
	if (tab[i] && check_space(tab[i]) == 1)
	  my_put_in_list(&coord, tab[i], 0);
      if (tab[i])
	i++;
    }
  i = 0;
  while (tab[i] != NULL)
    if (check_connection(tab[i++]) == 1)
      my_search_in_list(coord, tab[i - 1], 0, 0);
  return (coord);
}
