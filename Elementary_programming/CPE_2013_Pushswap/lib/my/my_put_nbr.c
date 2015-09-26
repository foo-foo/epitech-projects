/*
** my_put_nbr.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 10:36:45 2013 menich_a
** Last update Tue Oct  8 13:41:46 2013 menich_a
*/

int	my_put_nbr(int nb)
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
    {
      div = div * 10;
    }
  while (div != 0)
    {
      res = nb / div + 48;
      nb = nb % div;
      div = div / 10;
      my_putchar(res);
    }
  return (0);
}
