/*
** my_revstr.c for  in /home/menich_a/rendu/Piscine-C-Jour_06/ex_03
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Oct  7 10:15:43 2013 menich_a
** Last update Mon Oct  7 10:28:32 2013 menich_a
*/

char	*my_revstr(char *str)
{
  int	i;
  int	j;
  char	tmp;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  i = i - 1;
  while (i > j)
    {
      tmp = str[j];
      str[j] = str[i];
      str[i] = tmp;
      j = j + 1;
      i = i - 1;
    }
  return (str);
}
