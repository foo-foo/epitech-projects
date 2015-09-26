/*
** my_find_prime_sup.c for  in /home/menich_a/rendu/Piscine-C-lib
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Tue Oct  8 13:46:55 2013 menich_a
** Last update Tue Oct  8 14:25:00 2013 menich_a
*/

int	my_check_prime(int nb)
{
  int	i;

  i = 2;
  if (nb <= 0 || nb == 1)
    {
      return (0);
    }
  while (i < nb)
    {
      if (nb % i == 0)
	{
	  return (0);
	}
      i = i + 1;
    }
  return (1);
}

int	my_find_prime_sup(int nb)
{
  while (my_check_prime(nb) == 0)
    {
      nb = nb + 1;
    }
  return (nb);
}
