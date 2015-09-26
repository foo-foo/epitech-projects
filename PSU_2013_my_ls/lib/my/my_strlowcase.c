/*
** my_strlowcase.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_07
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 18:02:30 2013 menich_a
** Last update Mon Oct  7 18:03:27 2013 menich_a
*/

char	*my_strlowcase(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 65 && str[i] <= 90)
	{
	  str[i] = str[i] + 32;
	}
      i = i + 1;
    }
  return (str);
}
