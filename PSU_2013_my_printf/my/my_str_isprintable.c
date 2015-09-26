/*
** my_str_isprintable.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_10
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  8 07:49:12 2013 menich_a
** Last update Tue Oct  8 08:47:21 2013 menich_a
*/

int	my_str_isprintable(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      while (str[i] >= ' ' && str[i] <= '~' && str[i] != '\0')
	{
	  i = i + 1;
	}
      if ((str[i] < ' ' || str[i] > '~') && str[i] != '\0')
	{
	  return (0);
	}
    }
  return (1);
}
