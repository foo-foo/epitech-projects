/*
** my.c for my in /home/menich_a/rendu/PSU_2013_minitalk/my/
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Mon Feb 17 14:47:38 2014 menich_a
** Last update Sun Mar 23 14:08:06 2014 menich_a
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i = i + 1;
  return (i);
}

void	my_putstr(char *str)
{
  if (str)
    write(1, str, my_strlen(str));
}

int	msg_error(char *msg)
{
  if (msg)
    write(2, msg, my_strlen(msg));
  return (-1);
}

void	my_put_nbr(int nb)
{
  int	div;
  char	res;

  div = 1;
  if (nb < 0)
    {
      my_putchar('-');
      nb = -nb;
    }
  while (nb / div > 9)
    div = div * 10;
  while (div != 0)
    {
      res = nb / div + 48;
      nb = nb % div;
      div = div / 10;
      my_putchar(res);
    }
}
