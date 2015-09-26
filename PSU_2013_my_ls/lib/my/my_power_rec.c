/*
** my_power_it.c for  in /home/menich_a/rendu/Piscine-C-Jour_05
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Oct  4 14:29:16 2013 menich_a
** Last update Mon Oct  7 20:23:47 2013 menich_a
*/

int	my_power_rec(int nb, int power)
{
  if (power < 0)
    {
      return (0);
    }
  if (power > 0)
    {
      return (my_power_rec(nb, power - 1) * nb);
    }
  return (1);
}
