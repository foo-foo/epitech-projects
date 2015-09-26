/*
** my_str_islower.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_10
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  8 07:32:13 2013 menich_a
** Last update Tue Oct  8 07:58:25 2013 menich_a
*/

int	my_str_islower(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      while (str[i] >= 'a' && str[i] <= 'z' && str[i] != '\0')
	{
	  i = i + 1;
	}
      if ((str[i] < 'a' || str[i] > 'z') && str[i] != '\0')
	{
	  return (0);
	}
    }
  return (1);
}
