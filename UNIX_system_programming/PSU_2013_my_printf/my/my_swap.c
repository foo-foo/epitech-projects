/*
** my_swap.c for  in /home/menich_a/rendu/Piscine-C-Jour_04
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu Oct  3 11:43:45 2013 menich_a
** Last update Wed Oct  9 14:05:20 2013 menich_a
*/

int	my_swap(int *a, int *b)
{
  int c;

  c = *a;
  a = b;
  b = &c;
  return (0);
}
