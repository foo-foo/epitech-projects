/*
** my_sort_int_tab.c for  in /home/menich_a/rendu/Piscine-C-Jour_04
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Fri Oct  4 07:41:07 2013 menich_a
** Last update Sun Nov 17 18:44:10 2013 menich_a
*/

void	my_sort_int_tab(int *tab, int size)
{
  int	i;
  int	j;
  int	save;

  i = 0;
  j = size;
  while (j > 0)
    {
      while (i < size)
	{
	  while (tab[i] > tab[i + 1])
	    {
	      save = tab[i];
	      tab[i] = tab[i + 1];
	      tab[i + 1] = save;
	      if (tab[i] < tab[i - 1])
		{
		  i = i - 1;
		}
	    }
	  i = i + 1;
	}
      j = j - 1;
    }
}
