/*
** my_strupcase.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_07
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 17:42:30 2013 menich_a
** Last update Mon Oct  7 18:01:49 2013 menich_a
*/

char	*my_strupcase(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 97 && str[i] <= 122)
	{
	  str[i] = str[i] - 32;
	}
      i = i + 1;
    }
  return (str);
}
