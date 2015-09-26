/*
** my_strcapitalize.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_07
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 18:02:30 2013 menich_a
** Last update Wed Oct  9 13:42:28 2013 menich_a
*/

char	*my_strcapitalize(char *str)
{
  int	i;

  i = 1;
  if (str[0] >= 'a' && str[i] <= 'z')
    str[0] = str[0] - 32;
  while (str[i] != '\0')
    {
      while ((str[i] < 'a' || str[i] > 'z')
	     && (str[i] < 'A' || str[i] > 'Z') && str[i] != '\0')
	i = i + 1;
      if (str[i] >= 'a' && str[i] <= 'z'
	  && (str[i - 1] == ' ' || str[i - 1] == '-' || str[i - 1] == '+'))
	str[i] = str[i] - 32;
      if (str[i] >= 'A' && str[i] <= 'Z'
	  && (str[i - 1] != ' ' && str[i - 1] != '-' && str[i - 1] != '+'))
	str[i] = str[i] + 32;
      i = i + 1;
    }
  return (str);
}
