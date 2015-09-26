/*
** my_getnbr.c for my in /home/menich_a/rendu/PSU_2013_minitalk/my/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Sat Mar 22 22:41:04 2014 menich_a
** Last update Sat Mar 22 23:22:45 2014 menich_a
*/

int	my_getnbr(char *str)
{
  int	res;
  int	i;

  i = 0;
  res = 0;
  if (!str)
    return (0);
  while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
      res = (res * 10) + (str[i] - 48);
      i = i + 1;
    }
  if (str[i])
    return (0);
  return (res);
}
