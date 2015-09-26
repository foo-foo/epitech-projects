/*
** my_str_isalpha.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_10
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 19:49:39 2013 menich_a
** Last update Wed Oct  9 11:11:59 2013 menich_a
*/

int	my_str_isalpha(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      while ((str[i] >= 'a' && str[i] <= 'z')
	     || (str[i] >= 'A' && str[i] <= 'Z') && str[i] != '\0')
	i = i + 1;
      if ((str[i] < 'a' || str[i] > 'z')
	  && (str[i] < 'A' ||  str[i] > 'Z') && str[i] != '\0')
	return (0);
    }
  return (1);
}
