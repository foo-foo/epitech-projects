/*
** my_str_isnum.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_10
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  8 07:29:38 2013 menich_a
** Last update Tue Oct  8 07:42:20 2013 menich_a
*/

int	my_str_isnum(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
	  i = i + 1;
	}
      if ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
	{
	  return (0);
	}
    }
  return (1);
}
