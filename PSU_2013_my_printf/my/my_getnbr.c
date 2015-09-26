/*
** my_getnbr.c for  in /home/menich_a/rendu/Piscine-C-Jour_04
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Oct  3 16:28:06 2013 menich_a
** Last update Sat Nov  2 11:07:04 2013 menich_a
*/

int	my_getnbr(char *str)
{
  int	i;
  int	j;
  int	res;

  i = 0;
  res = 0;
  while ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
    {
      i = i + 1;
    }
  j = i - 1;
  while (str[i] >= '0' && str[i] <= '9')
    {
      res = (res * 10) + (str[i] - 48);
      i = i + 1;
    }
  if (res > 2147483647 || res < -2147483648)
    {
      return (0);
    }
  if (str[j] == '-')
    {
      return (-res);
    }
  return (res);
}
