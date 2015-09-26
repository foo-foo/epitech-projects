/*
** tools.c for  in /home/bencha_a/lem-in/v1.6/interface_graphique
** 
** Made by bencharif
** Login   <bencha_a@epitech.net>
** 
** Started on  Fri May  2 19:58:43 2014 bencharif
** Last update Sun May  4 19:48:37 2014 menich_a
*/

int	check_space(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == ' ')
        return (1);
      i++;
    }
  return (0);
}

int	check_connection(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '-')
        return (1);
      i++;
    }
  return (0);
}
