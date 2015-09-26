/*
** my.c for lem_in in /home/menich_a/rendu/prog_elem/lem_in/srcs
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Apr 17 12:42:59 2014 menich_a
** Last update Sat Apr 26 18:59:18 2014 menich_a
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

void	my_put_nbr(int nbr)
{
  int	div;
  int	digit;

  div = 1;
  while (nbr / div > 9)
    div = div * 10;
  while (div)
    {
      digit = nbr / div + 48;
      nbr = nbr % div;
      div = div / 10;
      my_putchar(digit);
    }
}
