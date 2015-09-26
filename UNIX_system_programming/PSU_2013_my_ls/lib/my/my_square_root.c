/*
** my_square_root.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 11:03:11 2013 menich_a
** Last update Wed Oct  9 11:19:03 2013 menich_a
*/

int	my_square_root(int nb)
{
  int	i;

  i = 1;
  if (nb == 1)
    {
      return (1);
    }
  if (nb <= 0)
    {
      return (0);
    }
  while (i <= nb / 2)
    {
      if (i * i == nb)
	{
	  return (i);
	}
      i = i + 1;
    }
  return (0);
}
