/*
** check_channel_name.c for  in /home/auduri_a/rendu/PSU_2014_myirc/srcs/server
** 
** Made by audurier julien
** Login   <auduri_a@epitech.net>
** 
** Started on  Wed Apr  8 14:16:08 2015 audurier julien
** Last update Fri Apr 10 14:49:19 2015 audurier julien
*/

int	check_channel_name(char *str)
{
  int	i;

  i = 1;
  if (str[0] != '#' && str[0] != '&')
    return (-1);
  while (str && str[i])
    {
      if (str[i] == 0 || str[i] == 7 || str[i] == 32
	  || str[i] == 13 || str[i] == 10 || str[i] == ',')
	return (-1);
      ++i;
    }
  if (i >= 200)
    return (-1);
  return (0);
}
