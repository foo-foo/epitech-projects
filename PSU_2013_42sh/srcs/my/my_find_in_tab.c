/*
** my_find_in_tab.c for 42sh in /home/menich_a/rendu/PSU_2013_minishell2
** 
** Made by menich_a
** Login   <menich_a@epitech.net>
** 
** Started on  Thu May 15 19:52:23 2014 menich_a
** Last update Sat May 24 17:20:31 2014 menich_a
*/

int	my_find_in_tab(char **tab, char c)
{
  int	x;
  int	y;

  y = 0;
  while (tab[y])
    {
      x = 0;
      while (tab[y][x] && tab[y][x] != c)
	x = x + 1;
      if (tab[y][x])
        return (y);
      y = y + 1;
    }
  return (-1);
}
